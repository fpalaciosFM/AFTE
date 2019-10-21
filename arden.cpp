/*
Arden's Rule

    lambda:= {empty word}
    empty:= empty set
    0:= {'0'}
    1:= {'1'}

    a+b:= union of a and b
    a b:= concatenation of a and b
    a*:=  Kleene's closure of a.

    All regular expressions must end with  "."

We want to solve the system:

	E1= a11 E1 + a12 E1 + ... + a1n En + b1
	E2= a21 E1 + a22 E1 + ... + a2n En + b2
        ...
	En= an1 E1 + an2 E1 + ... + ann En + bn

assuming a_ij does not contain lambda.

Input:
     n
     a11.  a12.  ... a1n.  b1.
     a21.  a22.  ... a2n.  b2.
     ...
     an1.  an2.  ... ann.  bn.

Output:
     Solving values for E1,...,En 


Compile this program with g++ on any system
     g++ Arden.cpp -o Arden
Execute:
     ./Arden

				Eduardo Viruena Silva
				November, 2003
*/

#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

#define debug(x) \
    { cerr << "debug:" << (x) << endl; }
//------------------------------------------------//
// Objects for handling regular expression trees  //
//------------------------------------------------//

using namespace std;

enum { LETTER,
       EMPTY,
       LAMBDA,
       UNION,
       CONCAT,
       CLOSURE };

void tabs(string& s, int k) {
    for (int i = 0; i < k; i++) {
        s += '\t';
    }
}

class Node {
   protected:
    string texStr;

   public:
    virtual ~Node(){};
    virtual int Type(void) const = 0;
    virtual Node* Copy(void) const = 0;
    virtual Node* Simp(void) const = 0;
    virtual ostream& Print(ostream& os) const = 0;
    string getTexStr() { return texStr; };
    virtual string printTree();
    virtual string printTree(int&);
};

string Node::printTree() {
    int k = 0;
    return printTree(k);
}

string Node::printTree(int& k) {
    string s;
    tabs(s, k);
    if (k == 0) {
        s += "\\";
    }
    s += "node{" + texStr + "}\n";
    return s;
}

class Letter : public Node {
   private:
    char ch;

   public:
    Letter(char c) {
        ch = c;
        texStr = "$";
        texStr += c;
        texStr += "$";
    }
    virtual ~Letter(void){};
    virtual int Type(void) const { return LETTER; };
    virtual Node* Copy(void) const { return new Letter(ch); };
    virtual Node* Simp(void) const { return Copy(); };
    virtual ostream& Print(ostream& os) const;
};

ostream& Letter::Print(ostream& os) const {
    return os << ch;
}

class Empty : public Node {
   public:
    Empty() { texStr = "$\\emptyset"; };
    virtual ~Empty(void){};
    virtual int Type(void) const { return EMPTY; };
    virtual Node* Copy(void) const { return new Empty(); };
    virtual Node* Simp(void) const { return Copy(); };
    virtual ostream& Print(ostream& os) const;
};

ostream& Empty::Print(ostream& os) const {
    return os << "empty";
}

class Lambda : public Node {
   public:
    Lambda(void) { texStr = "$\\lambda$"; };
    virtual ~Lambda(void){};
    virtual int Type(void) const { return LAMBDA; };
    virtual Node* Copy(void) const { return new Lambda(); };
    virtual Node* Simp(void) const { return Copy(); };
    virtual ostream& Print(ostream& os) const;
};

ostream& Lambda::Print(ostream& os) const {
    return os << "lambda";
}

class BinOp : public Node {
   protected:
    Node* left;
    Node* right;

   public:
    BinOp(Node* l, Node* r) {
        left = l;
        right = r;
    };
    virtual ~BinOp(void) {
        if (right != NULL) delete right;
        if (left != NULL) delete left;
    }
    virtual int Type(void) const = 0;
    virtual Node* Copy(void) const = 0;
    virtual Node* Simp(void) const = 0;
    virtual ostream& Print(ostream& os) const = 0;
    virtual string printTree();
    virtual string printTree(int&);
};

string BinOp::printTree() {
    int k = 0;
    return printTree(k);
}

string BinOp::printTree(int& k) {
    int n1, n2;
    n1 = n2 = k + 1;
    string s, s1, s2;

    if (left) {
        s1 = left->printTree(n1);
    } else {
        n1--;
    }
    if (right) {
        s2 = right->printTree(n2);
    } else {
        n2--;
    }

    int m = n1 > n2 ? n1 : n2;

    tabs(s, k);
    if (k == 0) {
        s += "\\begin{tikzpicture}[nodes={draw, circle}, ->]\n\\";
    }
    s += "node{";
    s += texStr;
    s += "}\n";

    tabs(s, k);
    s += "child{\n";
    s += s1;
    tabs(s, k);
    s += "}\n";

    int b = 1;
    for (int i = 0; i < m - k - 1; i++) {
        for (int j = 0; j < b; j++) {
            tabs(s, k);
            s += "child[missing]\n";
        }
        b *= 2;
    }

    tabs(s, k);
    s += "child{\n";
    s += s2;
    tabs(s, k);
    s += '}';

    if (k == 0) {
        s += ";\n\\end{tikzpicture}";
    }
    s += '\n';

    k = m;
    return s;
}

class Union : public BinOp {
   public:
    Union(Node* l, Node* r) : BinOp(l, r) { texStr = "$\\cup$"; };
    virtual ~Union(void){};
    virtual int Type(void) const { return UNION; };
    virtual Node* Copy(void) const { return new Union(left->Copy(), right->Copy()); };
    virtual Node* Simp(void) const;
    virtual ostream& Print(ostream& os) const;
};

ostream& Union::Print(ostream& os) const {
    left->Print(os);
    os << " + ";
    right->Print(os);
    return os;
}

Node* Union::Simp(void) const {
    Node* l = left->Simp();
    Node* r = right->Simp();

    int lt = l->Type();
    int rt = r->Type();

    if (lt == EMPTY) {
        delete l;
        return r;
    }
    if (rt == EMPTY) {
        delete r;
        return l;
    }

    if (lt == CLOSURE && rt == LAMBDA) {
        delete r;
        return l;
    }
    if (rt == CLOSURE && lt == LAMBDA) {
        delete l;
        return r;
    }

    return new Union(l, r);
}

class Concatenation : public BinOp {
   public:
    Concatenation(Node* l, Node* r) : BinOp(l, r) { texStr = "$\\cdot$"; };
    ~Concatenation(void){};
    virtual int Type(void) const { return CONCAT; };
    virtual Node* Copy(void) const { return new Concatenation(left->Copy(), right->Copy()); };
    virtual Node* Simp(void) const;
    virtual ostream& Print(ostream& os) const;
};

ostream& Concatenation::Print(ostream& os) const {
    bool p = left->Type() == UNION;
    if (p)
        os << '(';
    left->Print(os);
    if (p)
        os << ')';

    p = right->Type() == UNION;
    if (p)
        os << '(';
    right->Print(os);
    if (p)
        os << ')';
    return os;
}

Node* Concatenation::Simp(void) const {
    Node* l = left->Simp();
    Node* r = right->Simp();

    int lt = l->Type();
    int rt = r->Type();

    if (lt == EMPTY) {
        delete r;
        return l;
    }

    if (rt == EMPTY) {
        delete l;
        return r;
    }

    if (lt == LAMBDA) {
        delete l;
        return r;
    }

    if (rt == LAMBDA) {
        delete r;
        return l;
    }

    return new Concatenation(l, r);
}

class Closure : public BinOp {
   public:
    Closure(Node* l) : BinOp(l, NULL) { texStr = "$*$"; };
    virtual ~Closure(void){};
    virtual int Type(void) const { return CLOSURE; };
    virtual Node* Copy(void) const { return new Closure(left->Copy()); };
    virtual Node* Simp(void) const;
    virtual ostream& Print(ostream& os) const;
};

ostream& Closure::Print(ostream& os) const {
    int t = left->Type();
    if (t == UNION || t == CONCAT) {
        os << '(';
        left->Print(os);
        os << ')';
    } else
        left->Print(os);
    os << "*";
    return os;
}

Node* Closure::Simp(void) const {
    Node* l = left->Simp();
    int tl = l->Type();

    if (tl == EMPTY) {
        delete l;
        return new Lambda();
    }

    if (tl == LAMBDA) {
        delete l;
        return new Lambda();
    }

    if (tl == CLOSURE)
        return l;

    return new Closure(l);
};

//---------------------------//
// Regular Expression parser //
//---------------------------//

class Parser {
   private:
    int ch;
    char sym[20];
    int ks;

    void initsym(void) { ks = 0; }
    void getch(void) {
        ch = input->get();
        if (ch == EOF) ch = '.';
    };
    void putch(char c) { sym[ks++] = c; };
    void endsym(void) { sym[ks] = '\0'; }

    void error(const char* msg);
    int test(const char* str);
    int testg(const char* str, const char* mesg = NULL);

    void GetSym(void);

    Node* Primary(void);
    Node* Factor(void);
    Node* Term(void);
    Node* Expr(void);
    istream* input;

   public:
    Parser(istream& is);
    Node* RExp(void);
};

void Parser::error(const char* msg) {
    cerr << "Error: " << msg << endl;
    exit(1);
}

int Parser::test(const char* str) {
    return strcmp(sym, str) ? 0 : 1;
}

int Parser::testg(const char* str, const char* mesg) {
    if (test(str)) {
        GetSym();
        return 1;
    }
    if (mesg)
        error(mesg);
    return 0;
}

Parser::Parser(istream& is) {
    input = &is;
    ch = ' ';
    strcpy(sym, "");
}

void Parser::GetSym(void) {
    while (isspace(ch))
        getch();
    initsym();
    while (isalpha(ch)) {
        putch(ch);
        getch();
    }
    if (ks) {
        endsym();
        return;
    }
    switch (ch) {
        case '.':
        case ')':
        case '(':
        case '*':
        case '+':
        case '1':
        case '0':
            putch(ch);
        default:
            getch();
            endsym();
            return;
    }
}

Node* Parser::Primary(void) {
    if (testg("empty"))
        return new Empty();

    if (testg("lambda"))
        return new Lambda();

    if (testg("0"))
        return new Letter('0');

    if (testg("1"))
        return new Letter('1');

    if (testg("(", "Missing <primary>")) {
        Node* p = Expr();
        if (testg(")", "Missing ')'"))
            return p;
    }
}

Node* Parser::Factor(void) {
    Node* f = Primary();
    while (testg("*"))
        f = new Closure(f);
    return f;
}

Node* Parser::Term(void) {
    Node* t = Factor();
    while (test("lambda") || test("empty") || test("0") || test("1") || test("("))
        t = new Concatenation(t, Factor());
    return t;
}

Node* Parser::Expr(void) {
    Node* e = Term();
    while (testg("+"))
        e = new Union(e, Term());
    return e;
}

Node* Parser::RExp(void) {
    Node* e;
    Node* s;
    ch = ' ';
    GetSym();
    e = Expr();
    if (test(".")) {
        s = e->Simp();
        delete e;
        return s;
    }

    delete e;
    error("Missing '.'");
}

class RegExpr {
   private:
    Node* ptr;
    RegExpr(Node*);

   public:
    RegExpr(void);
    RegExpr(const RegExpr&);
    RegExpr& operator=(const RegExpr& e);
    ~RegExpr();
    friend ostream& operator<<(ostream& os, const RegExpr& e);
    friend istream& operator>>(istream& is, RegExpr& e);
    friend RegExpr operator+(const RegExpr& a, const RegExpr& b);
    friend RegExpr operator*(const RegExpr& a, const RegExpr& b);
    friend RegExpr operator*(const RegExpr& a);
};

RegExpr::RegExpr(Node* e) {
    ptr = e->Simp();
    delete e;
}

RegExpr::RegExpr(void) {
    ptr = new Empty();
}

RegExpr::RegExpr(const RegExpr& e) {
    ptr = e.ptr->Copy();
}

RegExpr::~RegExpr(void) {
    delete ptr;
}

RegExpr& RegExpr::operator=(const RegExpr& e) {
    delete ptr;
    ptr = e.ptr->Copy();
    return *this;
}

ostream& operator<<(ostream& os, const RegExpr& e) {
    return e.ptr->Print(os);
}

istream& operator>>(istream& is, RegExpr& e) {
    Parser P(is);
    e = RegExpr(P.RExp());
    return is;
}

RegExpr operator+(const RegExpr& a, const RegExpr& b) {
    return RegExpr(new Union(a.ptr->Copy(), b.ptr->Copy()));
}

RegExpr operator*(const RegExpr& a, const RegExpr& b) {
    return RegExpr(new Concatenation(a.ptr->Copy(), b.ptr->Copy()));
}

RegExpr operator*(const RegExpr& a) {
    Node* r = new Closure(a.ptr->Copy());
    return RegExpr(r);
}

void PrintMat(RegExpr** A, int N) {
    cout << N << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j <= N; j++)
            cout << A[i][j] << ".\t";
        cout << endl;
    }
    cout << "--\n";
}

void Arden(RegExpr** A, int N) {
    for (int n = N - 1; n >= 0; n--) {
        RegExpr re = *A[n][n];

        for (int j = 0; j <= N; j++)
            if (j != n)
                A[n][j] = re * A[n][j];  // despejamos la ultima incognita

        for (int r = 0; r < n; r++) {
            for (int j = 0; j <= N; j++)
                if (j != n)  // y hacemos la substitucion
                    A[r][j] = A[r][j] + A[r][n] * A[n][j];
            A[r][n] = RegExpr();
        }

        A[n][n] = RegExpr();
        PrintMat(A, N);
    }

    for (int i = 0; i < N; i++)  // sustitucion hacia adelante
    {
        RegExpr s = A[i][N];
        for (int j = 0; j < i; j++)
            s = s + A[i][j] * A[j][N];
        A[i][N] = s;
    }
}

int main(void) {
    Node* u = new Union(
        new Concatenation(
            new Union(
                new Letter('1'),
                new Letter('0')),
            new Concatenation(
                new Letter('0'),
                new Closure(
                    new Letter('4')))),
        new Union(
            new Letter('1'),
            new Letter('2')));

    cout << u->printTree();

    return 0;
}
