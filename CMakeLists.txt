cmake_minimum_required(VERSION 3.28.1)
project(Lox)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lox Source/main.cpp
        Source/Lox.cpp
        Source/Headers/Lox.h
        Source/Headers/TokenType.h
        Source/Token.cpp
        Source/Headers/Token.h
        Source/Scanner.cpp
        Source/Headers/Scanner.h
)
