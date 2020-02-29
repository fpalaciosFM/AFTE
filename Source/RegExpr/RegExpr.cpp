#include "RegExp.hpp"

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

string RegExpr::printTree() {
    return ptr->printTree();
}

string RegExpr::AfteLatex() {
    return ptr->AfteLatex();
}

AFTE RegExpr::toAFTE() {
    return ptr->toAFTE();
}

AFTEL RegExpr::toAFTEL() {
    return ptr->toAFTEL();
}