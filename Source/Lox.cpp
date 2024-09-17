#include "Headers/Lox.h"

#include <process.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>


// Set errors flag to false at the start
bool Lox::errorEncountered = false;

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

    // Exit with certain error code on an error
    if (errorEncountered)
        exit(65);
}

// Run prompts that the user gives
void Lox::runPrompt() {
    // User interaction loop
    while (true) {
        printf("> ");

        // Get argument from the user
        std::string argument;
        std::getline(std::cin, argument);

        // If it's empty, end the interaction. Otherwise, run the argument
        if (argument.empty())
            break;
        run(argument);

        errorEncountered = false;
    }
}

// Run the given argument line
void Lox::run(const std::string& source) {
    // Create scanner from the source line
    Scanner scanner(source);
    // Get tokens from it
    std::vector<Token> tokens = scanner.scanTokens();

    // Go through each token
    for (const Token& token : tokens) {
        std::cout << token << std::endl;
    }
}

// Handle errors
void Lox::error(int line, const std::string &message) {
    reportError(line, "", message);
}

// Report error to the user
void Lox::reportError(int line, const std::string &place, const std::string &message) {
    printf("[line %d] Error%s: %s\n", line, place.c_str(), message.c_str());
    errorEncountered = true;
}

