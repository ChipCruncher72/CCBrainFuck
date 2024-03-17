#include <array>
#include <fmt/core.h>
#include <iostream>
#include <string>
#include "proj_functions.cpp"
#define CCBF_MAJOR 0
#define CCBF_MINOR 4
#define CCBF_PATCH 0

int main() {
    fmt::println("Brainfuck REPL v{}.{}.{} by ChipCruncher72 (https://www.github.com/ChipCruncher72)\n",
        CCBF_MAJOR,
        CCBF_MINOR,
        CCBF_PATCH
    );

    std::array<char, 30000> tape;
    int pointer = 0;

    std::string inp;
    std::getline(std::cin, inp);

    while (inp != "~EOF") {
        interpret(inp, tape, pointer);
        fmt::println("");
        std::getline(std::cin, inp);
    }

    return 0;
}
