#include "Scanner.h"

#include "Source/Headers/Lox.h"


// Create scanner from a source
Scanner::Scanner(const std::string &source) : m_source(source)
{ }

// Scan tokens of the source file
std::vector<Token> Scanner::scanTokens() {
    // Go thorough the entire source file
    while (!sourceEnd()) {
        // Set start line to the current one
        m_start = m_current;
        // Scan the token
        scanToken();
    }

    // Represent end of file in the tokens
    m_tokens.push_back(Token(ENDOF, "", NULL, m_line));
    return m_tokens;
}

// Return if source file has ended
bool Scanner::sourceEnd() const {
    return m_current >= m_source.length();
}

// Advance and scan current token
void Scanner::scanToken() {
    // Add exact token based on the character
    switch (char ch = advanceChar()) {
        case '(':
            addToken(LEFT_PAREN);
            break;
        case ')':
            addToken(RIGHT_PAREN);
            break;
        case '{':
            addToken(LEFT_BRACE);
            break;
        case '}':
            addToken(RIGHT_BRACE);
            break;
        case ',':
            addToken(COMMA);
            break;
        case '.':
            addToken(DOT);
            break;
        case '-':
            addToken(MINUS);
            break;
        case '+':
            addToken(PLUS);
            break;
        case '*':
            addToken(ASTERISK);
            break;
        case '/':
            addToken(SLASH);
            break;
        case ';':
            addToken(SEMICOLON);
            break;
        // If character isn't recognized, report an error
        default:
            Lox::error(m_line, "Unexpected character: " + ch);
            break;
    }
}

// Advance to the next character
char Scanner::advanceChar() {
    ++m_current;
    return m_source.at(m_current - 1);
}

void Scanner::addToken(TokenType token) {
    addToken(token, NULL);
}

void Scanner::addToken(TokenType token, const literalType& literal) {
    std::string text = m_source.substr(m_start, m_current);
    m_tokens.emplace_back(token, text, literal, m_line);
}
