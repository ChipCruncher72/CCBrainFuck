#include <array>
#include <cstdio>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <string>
#define CCBF_MAJOR 0
#define CCBF_MINOR 3
#define CCBF_PATCH 0

void FAIL(const char *msg) {
    fmt::println(stderr, "{}", msg);
    std::exit(1);
}

void WARN(const char *msg) {
    fmt::println(stderr, "WARNING: {}", msg);
}

void interpret(std::string text, std::array<char, 30000>& tape, int& ptr) {
    for (int i = 0; i < text.length(); i++) {
        switch (text[i]) {
            case '[': {
                int j = 0;
                std::string loop;
                i++;

                const int start = i;
                for (int k = 0; k < text.length(); k++, i++) {
                    char current = text[i];
                    if (current == '[')
                        j++;
                    if (current == ']') {
                        if (j == 0) {
                            loop = text.substr(start, k);
                            break;
                        } else j--;
                    }

                    if (k == text.length() - 1) {
                        std::string error = fmt::format("In file: Loop missing ']'\nAt: {}", i+1);
                        FAIL(error.c_str());
                    }
                }

                while (tape[ptr] != 0)
                    interpret(loop, tape, ptr);
            } break;
            case ']': {
                std::string error = fmt::format("In file: Rogue ']'\nAt: {}", i+1);
                FAIL(error.c_str());
            } break;
            case '>':
                ptr++;
                break;
            case '<':
                if (ptr == 0) {
                    std::string error = fmt::format("In file: Trying to decrement pointer while it's at 0\nAt: {}", i+1);
                    FAIL(error.c_str());
                }
                ptr--;
                break;
            case '+':
                tape[ptr]++;
                break;
            case '-':
                tape[ptr]--;
                break;
            case '.':
                fmt::print("{}", tape[ptr]);
                break;
            case ',': {
                char inp = std::getchar();
                tape[ptr] = inp;
            } break;
            default:
                break;
        }
    }
}

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
