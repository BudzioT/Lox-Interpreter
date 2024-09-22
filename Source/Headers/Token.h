#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>

#include "TokenType.h"


using literalType = std::variant<std::string, int, double, float, char, long, void*>;


// Class that represents single Lox token
class Token {
public:
    Token(TokenType type, const std::string& lexeme, literalType literal, int line);
    //Token(TokenType type, const std::string& lexeme, void* literal, int line);

    std::string toString() const;

private:
    literalType m_literal;
    std::string m_lexeme;
    TokenType m_type;
    int m_line;
};


#endif //TOKEN_H