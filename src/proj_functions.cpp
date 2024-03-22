#include <fmt/core.h>
#include <array>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#define CCBF_MAJOR 0
#define CCBF_MINOR 6
#define CCBF_PATCH 0
#define LAMBDA(...) [=](__VA_ARGS__)
#define FAIL(...) { fmt::println(stderr, "FATAL: " __VA_ARGS__); std::exit(1); }
#define WARN(...) { fmt::println(stderr, "WARNING: " __VA_ARGS__); }

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
                        FAIL("In file: Loop missing ']'\nAt: {}", i+1);
                    }
                }

                while (tape[ptr] != 0)
                    interpret(loop, tape, ptr);
            } break;
            case ']':
                FAIL("In file: Rogue ']'\nAt: {}", i+1);
                break;
            case '>':
                ptr++;
                break;
            case '<':
                if (ptr == 0)
                    FAIL("In file: Trying to decrement pointer while it's at 0\nAt: {}", i+1);
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
                tape[ptr] = std::getchar();
            } break;
            default:
                break;
        }
    }
}

std::string operator*(std::string self, int times) {
    std::stringstream ss;

    for (int i = 0; i < times; i++)
        ss << self;

    return ss.str();
}

std::string operator""_s(const char *str, size_t) {
    return str;
}

std::string cpp_str(std::string text, int spaces = 2) {
    std::stringstream ss;

    for (int i = 0; i < text.length(); i++) {
        switch (text[i]) {
            case '[': {
                ss << "    "_s * spaces << "while (_Tape[_Pointer] != 0) {\n";

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
                        FAIL("In file: Loop missing ']'\nAt: {}", i+1);
                    }
                }

                ss << cpp_str(loop, spaces+1);

                ss << "    "_s * spaces << "}\n";
            } break;
            case ']':
                FAIL("In file: Rogue ']'\nAt: {}", i+1);
                break;
            case '>':
                ss << "    "_s * spaces << "_Pointer++;\n";
                break;
            case '<':
                ss << "    "_s * spaces << "_Pointer--;\n";
                break;
            case '+':
                ss << "    "_s * spaces << "_Tape[_Pointer]++;\n";
                break;
            case '-':
                ss << "    "_s * spaces << "_Tape[_Pointer]--;\n";
                break;
            case '.':
                ss << "    "_s * spaces << "std::cout << _Tape[_Pointer];\n";
                break;
            case ',':
                ss << "    "_s * spaces << "_Tape[_Pointer] = std::getchar();\n";
                break;
            default:
                break;
        }
    }

    return ss.str();
}

void bf_to_cpp(std::string text, std::ofstream& os) {
    if (text.contains("."))
        os << "#include <iostream>\n";
    if (text.contains(","))
        os << "#include <cstdio>\n";

    os << R"(#include <array>

int main() {
    std::array<char, 30000> _Tape;
    int _Pointer = 0;
)";
    for (int i = 0; i < text.length(); i++) {
        switch (text[i]) {
            case '[': {
                os << "    while (_Tape[_Pointer] != 0) {\n";

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
                        FAIL("In file: Loop missing ']'\nAt: {}", i+1);
                    }
                }

                os << cpp_str(loop);

                os << "    }\n";
            } break;
            case ']':
                FAIL("In file: Rogue ']'\nAt: {}", i+1);
                break;
            case '>':
                os << "    _Pointer++;\n";
                break;
            case '<':
                os << "    _Pointer--;\n";
                break;
            case '+':
                os << "    _Tape[_Pointer]++;\n";
                break;
            case '-':
                os << "    _Tape[_Pointer]--;\n";
                break;
            case '.':
                os << "    std::cout << _Tape[_Pointer];\n";
                break;
            case ',':
                os << "    _Tape[_Pointer] = std::getchar();\n";
                break;
            default:
                break;
        }
    }

    os << R"(
    return 0;
}
)";
}
