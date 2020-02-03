#include "Parser.hpp"

Parser::Parser(istream& is) {
    input = &is;
    ch = ' ';
    strcpy(sym, "");
}

void Parser::initsym(void) {
    ks = 0;
}

void Parser::getch(void) {
    ch = input->get();
    if (ch == EOF) ch = '.';
}

void Parser::putch(char c) {
    sym[ks++] = c;
}

void Parser::endsym(void) {
    sym[ks] = '\0';
}

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