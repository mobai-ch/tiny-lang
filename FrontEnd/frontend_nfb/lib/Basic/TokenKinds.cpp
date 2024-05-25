#include "Basic/TokenKinds.h"

using namespace tinylang;
using namespace tok;

static const char * const TokNames[] = {
    #define TOK(ID) #ID,
    #define KEYWORD(ID, FLAG) #ID,
    #include "Basic/TokenKinds.def"
        nullptr
};

const char *tok::getTokenName(TokenKind Kind) {
    return TokNames[Kind];
}

const char *tokLLgetPunctuatorSpelling(TokenKind Kind) {
    switch (Kind) {
#define PUNCTUATOR(ID, SP) case ID: return SP;
#include "Basic/TokenKinds.def"
        default: break;
    }
    return nullptr;
}

const char *tok::getKeywordSpelling(TokenKind Kind) {
    switch(Kind) {
#define KEYWORD(ID, FLAG) case kw_ ## ID: return #ID;
#include "Basic/TokenKinds.def"
        default: break;
    }
    return nullptr;
}