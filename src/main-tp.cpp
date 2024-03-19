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

    if (std::filesystem::path(argv[1]).extension() != ".bf" && std::filesystem::path(argv[1]).extension() != ".b") {
#if CCBF_MAJOR == 0 && CCBF_MINOR < 5
        WARN("File does not end in .bf or .b\nThe code can still run, but this behaviour will be deprecated as of v0.5.0");
#else
        FAIL("File does not end in .bf or .b");
#endif
    }

    std::ifstream bf_file(argv[1]);

    std::string file_name = argv[1];
    std::ofstream cpp_file(file_name.substr(0, file_name.find_last_of(".")) + ".cpp");

    std::string entire_bf_file;

    while (!bf_file.eof()) {
        std::string line;
        std::getline(bf_file, line);

        entire_bf_file += line + "\n";
    }

    std::array<char, 30000> tape;
    int ptr = 0;
    bf_to_cpp(entire_bf_file, cpp_file, tape, ptr);

    bf_file.close();
    cpp_file.close();

    return 0;
}
