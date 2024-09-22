#include "Headers/Scanner.h"

#include "Headers/Lox.h"


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
    m_tokens.push_back(Token(ENDOF, "", nullptr, m_line));
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
        // Single character tokens
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
        case ';':
            addToken(SEMICOLON);
            break;

        // Possibly dual character tokens
        case '!':
            addToken(match('=') ? BANG_EQUAL : BANG);
            break;
        case '=':
            addToken(match('=') ? EQUAL_EQUAL : EQUAL);
            break;
        case '<':
            addToken(match('=') ? LESS_EQUAL : LESS);
            break;
        case '>':
            addToken(match('=') ? GREATER_EQUAL : GREATER);
        case '/':
            // If it's a comment, skip all character on this line
            if (match('/')) {
                while (peekChar() != '\n' && !sourceEnd())
                    advanceChar();
            }
            // Otherwise add normal slash
            else
                addToken(SLASH);
            return;

        // If character isn't recognized, report an error
        default:
            Lox::error(m_line, std::string("Unexpected character: ") + ch);
            break;
    }
}

// Advance to the next character
char Scanner::advanceChar() {
    ++m_current;
    return m_source.at(m_current - 1);
}

// Add token without literal to a vector with tokens
void Scanner::addToken(TokenType token) {
    addToken(token, nullptr);
}

// Add token as a null literal
void Scanner::addToken(TokenType token, void* literal) {
    std::string text = m_source.substr(m_start, m_current);
    m_tokens.emplace_back(token, text, literal, m_line);
}

// Add token with literal to the vector with tokens
void Scanner::addToken(TokenType token, const literalType& literal) {
    std::string text = m_source.substr(m_start, m_current);
    m_tokens.emplace_back(token, text, literal, m_line);
}

// Check if target character matches the current one
bool Scanner::match(char target) {
    // If file ended, character can't be a match
    if (sourceEnd())
        return false;
    // If character isn't the same, return
    if (target != m_source.at(m_current))
        return false;

    // Advance to the next character and inform that it matched
    ++m_current;
    return true;
}

// Peek and return next character from the source file
char Scanner::peekChar() const {
    if (sourceEnd())
        return '\0';
    return m_source.at(m_current);
}
