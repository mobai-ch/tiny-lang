#ifndef TINYLANG_LEXER_LEXER_H_
#define TINYLANG_LEXER_LEXER_H_

#include <string>
#include "Lexer/Token.h"

namespace tinylang {
    class Lexer {
        const char *BufferStart;
        const char *BufferPtr;
        int currentLine;

    public:
        Lexer(const std::string &buffer) {
            BufferStart = buffer.c_str();
            BufferPtr = BufferStart;
            currentLine = 1;
        }

        void next(Token &token);

    private:
        void formToken(Token &Result, const char *TokEnd,
                    tok::TokenKind Kind);
        
        bool checkCompoundTokenAndForm(Token &Result, const char *currentPtr);
    };
};

#endif
