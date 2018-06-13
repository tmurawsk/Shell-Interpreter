cmake_minimum_required(VERSION 3.0)
project(Shell-Interpreter)

add_subdirectory(tests)

set(CMAKE_CXX_STANDARD 17)
add_executable(shell src/main.cpp src/Terminal.h src/System.h src/Statements/Statement.h src/Statements/Commands/Cd.h src/Statements/Commands/Ls.h src/Statements/Commands/Exp.h src/Statements/Commands/Pwd.h src/Statements/Commands/Exit.h src/Statements/Commands/Mkfifo.h src/Statements/Commands/Grep.h src/Statements/Commands/Echo.h src/Parser/Parser.cpp src/Parser/Parser.h src/Parser/Token.h src/Exceptions.h src/Statements/Commands/Exec.h src/Parser/Command.h src/Environment.cpp src/Environment.h src/Statements/Commands/SetEnv.h src/Parser/Lexer.cpp src/Parser/Lexer.h)

enable_testing()