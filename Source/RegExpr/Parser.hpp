#ifndef PARSER_HPP
#define PARSER_HPP

#include <cstring>

#include "../Node/Empty.hpp"
#include "../Node/Lambda.hpp"
#include "../Node/Letter.hpp"
#include "../Node/BinOp/Closure.hpp"
#include "../Node/BinOp/Concatenation.hpp"
#include "../Node/BinOp/Union.hpp"

class Parser {
   private:
    istream* input;
    int ch;
    char sym[20];
    int ks;

    void initsym(void);
    void getch(void);
    void putch(char c);
    void endsym(void);

    void error(const char* msg);
    int test(const char* str);
    int testg(const char* str, const char* mesg = NULL);

    void GetSym(void);

    Node* Primary(void);
    Node* Factor(void);
    Node* Term(void);
    Node* Expr(void);

   public:
    Parser(istream& is);
    Node* RExp(void);
};

#endif /* PARSER_HPP */