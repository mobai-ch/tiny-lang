#ifndef TINYLANG_PARSER_H
#define TINYLANG_PARSER_H

#include "AST/AST.h"
#include "Lexer/Lexer.h"
#include <iostream>

using namespace tinylang;

class Parser {
    Lexer &Lex;
    Token Tok;
    bool HasError;

    void error() {
        std::cout << "Unexpected: " << Tok.getLiteralData() << std::endl;
        HasError = true;
    }

    void advance() { Lex.next(Tok); }

    bool expect(tok::TokenKind Kind) {
        if(Tok.getKind() != Kind) {
            error();
            return true;
        }
        return false;
    }

    bool consume(tok::TokenKind Kind) {
        if(expect(Kind))
            return true;
        advance();
        return false;
    }

    AST *parseCalc();
    Expr *parseExpr();
    Expr *parseTerm();
    Expr *parseFactor();

public:
    Parser(Lexer &Lex) : Lex(Lex), HasError(false) {
        advance();
    }

    bool hasError() { return HasError; }

    AST *parse();
};

#endif