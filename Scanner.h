#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>

#include "Source/Headers/Token.h"


// Class to scan source code, extract lexemes
class Scanner {
public:
    explicit Scanner(const std::string &source);

    std::vector<Token> scanTokens();

private:
    [[nodiscard]] bool sourceEnd() const;
    void scanToken();
    char advanceChar();

    void addToken(TokenType token);
    void addToken(TokenType token, const literalType& literal);

private:
    std::string m_source;
    std::vector<Token> m_tokens;
    int m_start = 0;
    int m_current = 0;
    int m_line = 1;
};



#endif //SCANNER_H
