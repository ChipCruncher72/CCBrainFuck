#include <fmt/core.h>
#include <array>
#include <cstdlib>
#include <cstdio>
#include <string>
#define CCBF_MAJOR 0
#define CCBF_MINOR 5
#define CCBF_PATCH 0
#define CCBF_LAMBDA(...) [=](__VA_ARGS__)

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
