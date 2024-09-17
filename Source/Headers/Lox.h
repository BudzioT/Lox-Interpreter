#ifndef LOX_H
#define LOX_H

#include <string>


class Lox {
public:
    Lox(int argc, char* args[]);

    void runFile(const std::string& path);
    void runPrompt();
    void run(const std::string& source);
};



#endif //LOX_H
