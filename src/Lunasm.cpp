#include <fmt/core.h>
#include <argparse/argparse.hpp>

#include "Lexer/Lexer.hpp"

const std::string VERSION = "Lunasm version 0.0.1";

int main(int argc, char* argv[])
{
    argparse::ArgumentParser program("Lunasm", "Version: 0.0.1");

    program  // Input file command
        .add_argument("-f", "--file")
        .default_value(false)
        .implicit_value(true)
        .help("Input file for Lunasm");

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::runtime_error& err)
    {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    return EXIT_SUCCESS;
}
