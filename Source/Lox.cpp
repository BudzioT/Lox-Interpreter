#include "Headers/Lox.h"

#include <process.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>


// Create lox interpreter
Lox::Lox(int argc, char *args[]) {
    // If user gave two arguments, remind him proper usage of program
    if (argc > 2) {
        printf("Usage: lox [script]");
        exit(64);
    }
    // If path was given, run the file
    else if (argc == 2)
        runFile(args[1]);
    // In case of no arguments - use prompt based system
    else
        runPrompt();
}

// Run given file
void Lox::runFile(const std::string& path) {
    // Open it
    std::ifstream file;
    file.open(path);

    // Read it using string stream, save results to a string
    std::stringstream strStream;
    strStream << file.rdbuf();
    std::string result = strStream.str();

    // Run the given code
    run(result);
}

// Run prompts that the user gives
void Lox::runPrompt() {
    while (true) {
        printf("> ");

        std::string argument;
        std::getline(std::cin, argument);
        if (argument.empty())
            break;
        run(argument);
    }
}

void Lox::run(const std::string& source) {
    std::cout << source;
}

