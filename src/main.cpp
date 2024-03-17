#include <array>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <string>
#include "proj_functions.cpp"


int main(int argc, char *argv[]) {
    if (argc == 1)
        FAIL("No args provided");

    if (argc > 2)
        WARN("Exccess arguments, provided more than one");

    if (!std::filesystem::is_regular_file(argv[1]))
        FAIL("Invalid file provided");

    if (std::filesystem::path(argv[1]).extension() != ".bf") {
#if CCBF_MAJOR == 0 && CCBF_MINOR < 5
        WARN("File does not end in .bf\nThe code can still run, but this behaviour will be deprecated as of v0.5.0");
#else
        FAIL("File does not end in .bf");
#endif
    }

    fmt::println("Brainfuck Interpreter v{}.{}.{} by ChipCruncher72 (https://www.github.com/ChipCruncher72)\n",
        CCBF_MAJOR,
        CCBF_MINOR,
        CCBF_PATCH
    );
    std::ifstream bf_file(argv[1]);

    std::array<char, 30000> tape;
    int pointer = 0;

    std::string entire_file;

    while (!bf_file.eof()) {
        std::string line;
        std::getline(bf_file, line);

        entire_file += line + "\n";
    }

    interpret(entire_file, tape, pointer);

    bf_file.close();

    return 0;
}
