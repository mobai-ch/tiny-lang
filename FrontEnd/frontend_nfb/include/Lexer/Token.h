#ifndef _TINYLANG_LEXER_TOKEN_H
#define _TINYLANG_LEXER_TOKEN_H

#include "Basic/TokenKinds.h"
#include <string>
#include <cassert>

namespace tinylang {
    class Token {
        friend class Lexer;

        const char *Ptr;
        size_t Length;
        tok::TokenKind Kind;
        int lineNum;

    public:
        tok::TokenKind getKind() const { return Kind; }
        size_t getLength() const { return Length; } 

        bool is(tok::TokenKind K) const { return Kind == K; }
        bool isNot(tok::TokenKind K) const { return Kind != K; }
        bool isOneOf(tok::TokenKind K1, tok::TokenKind K2) const {
            return is(K1) || is(K2);
        }
        template <typename... Ts>
        bool isOneOf(tok::TokenKind K1, tok::TokenKind K2, Ts... Ks) const {
            return is(K1) || isOneOf(K2, Ks...);
        }

        std::string getTokTypeStr() {
            switch(Kind) {
                case tok::plus:
                    return "PLUS";
                case tok::minus:
                    return "MINUS";
                case tok::star:
                    return "STAR";
                case tok::slash:
                    return "SLASH";
                case tok::l_paren:
                    return "LPAREN";
                case tok::r_paren:
                    return "RPAREN";
                case tok::colon:
                    return "COLON";
                case tok::comma:
                    return "COMMA";
                case tok::semicolon:
                    return "SEMICOLON";
                case tok::equal:
                    return "EQUAL";
                case tok::assign:
                    return "ASSIGN";
                case tok::notequal:
                    return "NOTEQUAL";
            }
            return "UNKNOW";
        }

        std::string getIdentifier() {
            assert(is(tok::identifier) &&
                    "Cannot get identifier of non-identifier");
            return std::string(Ptr, Length);
        }

        std::string getLiteralData() {
            assert(isOneOf(tok::integer_literal,
                        tok::string_literal) &&
                "Cannot get literal data of non-literal");
            return std::string(Ptr, Length);
        }

        std::string getNumber() {
            assert(is(tok::number) && 
                    "Cannot get the number");
            return std::string(Ptr, Length);
        }

        int getLine() {
            return lineNum;
        }
    };
}

#endif