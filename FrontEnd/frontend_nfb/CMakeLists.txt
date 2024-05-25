cmake_minimum_required(VERSION 3.10)

project(SimpleLexer)

include_directories(./include)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRE True)

set(SOURCES
    ./tools/LexerNFB.cpp
    ./lib/Basic/TokenKinds.cpp
    ./lib/Lexer/Lexer.cpp
)

add_executable(LexerNFB ${SOURCES})