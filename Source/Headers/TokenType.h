#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

// ALl token types
enum TokenType {
    // Single-character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, ASTERISK,

    // One, two character tokens
    EQUAL, EQUAL_EQUAL, BANG, BANG_EQUAL,
    GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

    // Literals
    IDENTIFIER, STRING, NUMBER,

    // Keywords
    CLASS, AND, OR, IF, ELSE, FUNC, SUPER, THIS, FOR, WHILE, VAR, TRUE, FALSE,
    PRINT, RETURN, NILL, ENDOF
};

#endif