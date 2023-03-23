#include <fmt/core.h>
#include <cxxopts.hpp>

#include "Lexer/Lexer.hpp"

const std::string VERSION = "Lunasm version 0.0.1";

int main(int argc, char* argv[])
{
    cxxopts::Options options("Lunasm", "\nAssembly language for the Luna16 fantasy console.\n");

    // clang-format off
    options.add_options()
        ("f,file", "File name", cxxopts::value<std::string>())
        ("R,repl", "Enable the REPL mode", cxxopts::value<bool>()->default_value("false"))
        ("v,version", "Show the program version")
        ("h,help", "Show usage menu");
    // clang-format on

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        fmt::print("{}", options.help());
        std::exit(0);
    }

    if (result.count("version"))
    {
        fmt::print("Version: {}", VERSION);
        std::exit(0);
    }

    return EXIT_SUCCESS;
}
