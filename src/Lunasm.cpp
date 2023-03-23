#include <fmt/core.h>
#include <argparse/argparse.hpp>

#include "Lexer/Lexer.hpp"

int main(int argc, char* argv[])
{
    argparse::ArgumentParser program("Lunasm", "Version: 0.0.1");

    program  // Input file command
        .add_argument("-f", "--file")
        .required()
        .help("Specify the input file");

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

    auto file = program.get<std::string>("--file");

    fmt::print("File: {}\n", file);

    return EXIT_SUCCESS;
}
