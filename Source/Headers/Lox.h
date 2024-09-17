#ifndef LOX_H
#define LOX_H

#include <string>


class Lox {
public:
    Lox(int argc, char* args[]);

    static void runFile(const std::string& path);
    static void runPrompt();
    static void run(const std::string& source);

    static void error(int line, const std::string& message);

private:
    static void reportError(int line, const std::string& place, const std::string& message);

private:
    static bool errorEncountered;
};



#endif //LOX_H
