#include "Headers/Scanner.h"

#include "Headers/Lox.h"


// Create scanner from a source
Scanner::Scanner(const std::string &source) : m_source(source) {
    // Store all the possible types
    std::vector<TokenType> types = { CLASS, AND, OR, IF, ELSE, FUNC, SUPER, THIS, FOR, WHILE,
        VAR, TRUE, FALSE, PRINT, RETURN, NILL };

    // Store all words corresponding to the types
    std::vector<std::string> words = { "class", "and", "or", "if", "else",
    "func", "super", "this", "for", "while", "var", "true", "false",
    "print", "return", "nill" };

    // Insert all words and associate them with the token types
    for (int i = 0; i < types.size(); ++i) {
        m_keywords.emplace(words[i], types[i]);
    }
}

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
    m_tokens.emplace_back(ENDOF, "", nullptr, m_line);
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

        // Ignore whitespaces
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':  // Go to the next line
            ++m_line;
            break;

        // Handle the entire string literals
        case '"':
            string();
            break;

        // If character isn't recognized, handle usual cases
        default:
            // Take number literal
            if (std::isdigit(ch))
                number();
            // Take tokens as identifier if current token is a letter
            else if (isAlpha(ch))
                identifier();
            // Otherwise report an error
            else
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

// Is character a letter
bool Scanner::isAlpha(const char target) {
    return (target >= 'a' && target <= 'z') ||
            (target >= 'A' && target <= 'Z') ||
            target == '_';
}

bool Scanner::isAlnum(const char target) {
    return isAlpha(target) || std::isdigit(target);
}

// Peek and return next character from the source file
char Scanner::peekChar() const {
    if (sourceEnd())
        return '\0';
    return m_source.at(m_current);
}

// Peek through the character after the next one in the source file and return it
char Scanner::peekNextChar() const {
    // Check if this isn't the end
    if (m_current + 1 >= m_source.length())
        return '\0';
    return m_source.at(m_current + 1); // Return
}

// Handle number tokens, including decimals
void Scanner::number() {
    // Go through each character token
    while (std::isdigit(peekChar()))
        advanceChar();

    // Handle fractional part of the number, if it exists
    if (peekChar() == '.' && std::isdigit(peekNextChar())) {
        advanceChar();

        while (std::isdigit(peekChar()))
            advanceChar();
    }

    addToken(NUMBER, std::stod(m_source.substr(m_start, m_current)));
}

// Handle string literal tokens
void Scanner::string() {
    // Go through the entire string literal
    while (peekChar() != '"' && !sourceEnd()) {
        // If newline is encountered, apply it
        if (peekChar() == '\n')
            ++m_line;

        advanceChar();
    }

    // Safeguard against unterminated strings
    if (sourceEnd()) {
        Lox::error(m_line, "String literal not ended.");
        return;
    }

    // Advance through the closing character
    advanceChar();

    // Return string literal without quote characters
    std::string val = m_source.substr(m_start + 1, m_current - 1);
    addToken(STRING, val);
}

// Try to interpret characters as identifier
void Scanner::identifier() {
    // Look through each character and number
    while (isAlnum(peekChar()))
        advanceChar();

    // Get text and see if it's a keyword
    std::string text = m_source.substr(m_start, m_current);
    if (!m_keywords.contains(text)) // Add token as an identifier if keyword wasn't found
        addToken(IDENTIFIER);
    else // Otherwise add the correct keyword to the tokens
        addToken(m_keywords.at(text));
}
