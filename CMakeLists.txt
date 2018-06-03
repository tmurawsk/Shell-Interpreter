cmake_minimum_required(VERSION 3.0)
project(Shell-Interpreter)
set(CMAKE_CXX_STANDARD 11)
add_executable(shell src/main.cpp src/Terminal.h src/Environment.h src/Exceptions/PathReadException.h src/Exceptions/ExitException.h src/Statements/Statement.h src/Parser.cpp src/Parser.h)