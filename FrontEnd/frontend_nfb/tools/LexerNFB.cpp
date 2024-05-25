#include "Lexer/Lexer.h"
#include "Lexer/Token.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace tinylang;

std::string readFileToString(const std::string& filePath) {
    std::ifstream fileStream(filePath); // open file
    if (!fileStream) {
        throw std::runtime_error("Could not open file " + filePath);
    }

    std::ostringstream stringStream; // create stream file
    stringStream << fileStream.rdbuf(); // read the file inner text to the string stream

    return stringStream.str(); // return the string in string stream
}

void PrintToken(tinylang::Token token) {
    switch(token.getKind()) {
        default:
            std::cout << "( Line: " << token.getLine()<< " , " << token.getTokTypeStr() << " )" << std::endl;
            break;
        case tok::identifier:
            std::cout << "( Line: " << token.getLine() << " , " << "Identifier: " << token.getIdentifier() << " )" << std::endl;
            break;
        case tok::number:
            std::cout << "( Line: " << token.getLine() << " , "  << "Number: " << token.getNumber() << " )" << std::endl; 
            break;
        case tok::integer_literal:
            std::cout << "( Line: " << token.getLine() << " , "  << "Integer literal: " << token.getLiteralData() << " )" << std::endl;
            break;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Error number of arg";
        exit(-1);
    }
    std::string filePath(argv[1]);
    std::string codeContext = readFileToString(filePath);

    tinylang::Lexer lexer(codeContext);
    tinylang::Token currentTok;

    lexer.next(currentTok);

    while(currentTok.getKind() != tok::eof &&
          currentTok.getKind() != tok::unknown) {
        PrintToken(currentTok);
        lexer.next(currentTok);
    }

    return 0;
}