#include "Lexer/Lexer.h"

using namespace tinylang;

namespace charinfo {
    inline bool isWhitespace(char c) {
        return (c == ' '  ||
                c == '\t' ||
                c == '\f' ||
                c == '\v' ||
                c == '\r'
        );
    }

    inline bool isNextLine(char c) {
        return c == '\n';
    }

    inline bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    inline bool isLetter(char c) {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z');
    }
}

void Lexer::next(Token &token) {
    while (*BufferPtr) {
        if(charinfo::isWhitespace(*BufferPtr)) {
            ++BufferPtr;
        }else if(charinfo::isNextLine(*BufferPtr)) {
            ++BufferPtr;
            ++currentLine;
        }else{
            break;
        }
    }

    if(!*BufferPtr) {
        token.Kind = tok::eof;
        return;
    }

    if (charinfo::isLetter(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while (charinfo::isLetter(*end) || charinfo::isDigit(*end))
            ++end;
        tok::TokenKind kind = tok::identifier;
        formToken(token, end, kind);
        return;
    }
    else if (charinfo::isDigit(*BufferPtr)) {
        const char *end = BufferPtr + 1;
        while (charinfo::isDigit(*end))
            ++end;
        formToken(token, end, tok::number);
        return;
    }
    else {
        switch (*BufferPtr) {
#define CASE(ch, tok) case ch: if(!checkCompoundTokenAndForm(token, BufferPtr)) \
                                 formToken(token, BufferPtr + 1, tok); break
            CASE('+', tok::plus);
            CASE('-', tok::minus);
            CASE('*', tok::star);
            CASE('/', tok::slash);
            CASE('(', tok::l_paren);
            CASE(')', tok::r_paren);
            CASE(':', tok::colon);
            CASE(',', tok::comma);
            CASE(';', tok::semicolon);
            CASE('=', tok::equal);
            CASE('#', tok::notequal);
#undef CASE
            default:
                formToken(token, BufferPtr + 1, tok::unknown);
        }
        return;
    }
}

void Lexer::formToken(Token &Tok, const char *TokEnd,
                      tok::TokenKind Kind) {
    Tok.Kind = Kind;
    Tok.Ptr = BufferPtr;
    Tok.Length = TokEnd - BufferPtr;
    BufferPtr = TokEnd;
    Tok.lineNum = currentLine;
}

bool Lexer::checkCompoundTokenAndForm(Token &Tok, const char *currentPtr) {
    switch(*currentPtr) {
        case ':' : {
            if(*(currentPtr + 1) == '=') {
                formToken(Tok, currentPtr + 2, tok::assign);
                return true;
            }
            return false;
        }
        default:
            return false;
    }
    return false;
}