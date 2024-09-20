#include "Scanner.h"


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
