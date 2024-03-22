#include <array>
#include <fmt/core.h>
#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include "proj_functions.cpp"

int main() {
    FAIL("While the REPL does work, It's being blocked for the time being because of io issues.\nSee issue #3");

    fmt::println("Brainfuck REPL v{}.{}.{} by ChipCruncher72 (https://www.github.com/ChipCruncher72)",
        CCBF_MAJOR,
        CCBF_MINOR,
        CCBF_PATCH
    );
    fmt::println("INFO: Type \"~EOF\" to exit the REPL\n");

    std::array<char, 30000> tape;
    int pointer = 0;

    std::string inp;
    fmt::print(">>> ");
    std::getline(std::cin, inp);

    while (inp != "~EOF") {
        interpret(inp, tape, pointer);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        fmt::println("");
        fmt::print(">>> ");
        std::getline(std::cin, inp);
    }

    return 0;
}
