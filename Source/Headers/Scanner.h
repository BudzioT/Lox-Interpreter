#ifndef SCANNER_H
#define SCANNER_H

#include <map>
#include <string>
#include <vector>

#include "Token.h"


// Class to scan source code, extract lexemes
class Scanner {
public:
    explicit Scanner(const std::string &source);

    std::vector<Token> scanTokens();

private:
    [[nodiscard]] bool sourceEnd() const;
    void scanToken();

    void addToken(TokenType token);
    void addToken(TokenType token, const literalType& literal);
    void addToken(TokenType token, void* literal);

    char advanceChar();
    char peekChar() const;
    char peekNextChar() const;
    bool match(char target);

    static bool isAlpha(char target) ;
    static bool isAlnum(char target) ;

    void number();
    void string();
    void identifier();

private:
    std::string m_source;
    std::vector<Token> m_tokens;

    int m_start = 0;
    int m_current = 0;
    int m_line = 1;

    std::map<std::string, TokenType> m_keywords;
};



#endif //SCANNER_H
