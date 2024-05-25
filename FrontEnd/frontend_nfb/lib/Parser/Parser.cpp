#include "Parser/Parser.h"
#include <vector>
#include <string>

AST *Parser::parse() {
    AST *Res = parseCalc();
    expect(tok::eof);
    return Res;
}

AST *Parser::parseCalc() {
    Expr *E;
    std::vector<std::string> Vars;

    if(Tok.is(tok::kw_with)) {
        advance();

        if(expect(tok::identifier))
            goto _error;
        Vars.push_back(Tok.getText());
        advance();

        while(Tok.is(tok::comma)) {
            advance();
            if(expect(tok::identifier))
                goto _error;
            Vars.push_back(Tok.getText());
            advance();
        }

        if(consume(tok::colon))
            goto _error;
    }
    E = parseExpr();
    if(Vars.empty()) return E;
    else return new WithDecl(Vars, E);

_error:
    while(!Tok.is(tok::eof))
        advance();
    return nullptr;    
}

Expr *Parser::parseExpr() {
    Expr *Left = ParseTerm();
    while (Tok.isOneOf(tok::plus, tok::minus)) {
        BinaryOp::Operator Op = 
            Tok.is(tok::plus) ? BinaryOp::Plus:
                                BinaryOp::Minus;
        advance();
        Expr *Right = parseFactor();
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;
}

Expr *Parser::parseTerm() {
    Expr *Left = parseFactor();
    while (Tok.isOneOf(tok::star, tok::slash)) {
        BinaryOp::Operator Op = 
            Tok.is(tok::star) ? BinaryOp::Mul:
                                BinaryOp::Div;
        advance();
        Expr *Right = parseFactor();
        Left = new BinaryOp(Op, Left, Right);
    }
    return Left;
}

Expr *Parser::parseFactor() {
    Expr *Res = nullptr;
    switch(Tok.getKind()) {
    case tok::number:
        Res = new Factor(Factor::Number, Tok.getText());
        advance();
        break;
    case tok::identifier:
        Res = new Factor(Factor::Ident, Tok.getText());
        advance();
        break;
    case tok::l_paren:
        advance();
        Res = parseExpr();
        if (!consume(tok::r_paren)) break;
    default:
        if(!Res) error();
        while(!Tok.isOneOf(tok::r_paren, tok::star, tok::plus,
                           tok::minus, tok::slash, tok::eof))
            advance();
    }
    return Res;
}