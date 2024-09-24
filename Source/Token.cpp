#include "Headers/Token.h"


Token::Token(TokenType type, const std::string &lexeme,
    literalType literal, int line) : m_type(type), m_lexeme(lexeme), m_literal(literal),
    m_line(line)
{ }

// Create string from the token
std::string Token::toString() const {
    // Don't show anything if it's end of file
    if (m_type == ENDOF)
        return "";

    std::string result = std::to_string(m_type) + ' ' + m_lexeme + ' ';
    // String type
    if (std::holds_alternative<std::string>(m_literal))
        return result + std::get<std::string>(m_literal);
    // Int
    if (std::holds_alternative<int>(m_literal))
        return result + std::to_string(std::get<int>(m_literal));
    // Double
    if (std::holds_alternative<double>(m_literal))
        return result + std::to_string(std::get<double>(m_literal));
    // Char
    if (std::holds_alternative<char>(m_literal))
        return result + std::to_string(std::get<char>(m_literal));
    // Float
    if (std::holds_alternative<float>(m_literal))
        return result + std::to_string(std::get<float>(m_literal));
    // Long
    if (std::holds_alternative<long>(m_literal))
        return result + std::to_string(std::get<long>(m_literal));


    // Otherwise return just result
    return result;
}
