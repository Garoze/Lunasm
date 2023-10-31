#include <vector>

#include "fmt/core.h"
#include <argparse/argparse.hpp>

#include "Parser/Parser.hpp"

#include "Assembler/Assembler.hpp"

int main(int argc, char* argv[])
{
    argparse::ArgumentParser program("Lunasm", "Version: 0.0.1");

    program                              //
        .add_argument("-f", "--file")    //
        .help("Specify the input file"); //

    program                             //
        .add_argument("-D", "--debug")  //
        .default_value(false)           //
        .implicit_value(true)           //
        .help("enable the debug mode"); //

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

    bool debug = false;
    if (program["--debug"] == true)
    {
        debug = true;
    }

    if (program.present("--file"))
    {
        auto file = program.get<std::string>("--file");

        Parser::Parser p{};
        auto& i = p.parse_file(file, true);

        std::vector<std::uint8_t> output;
        Assembler::Assembler a{ output };

        a.compile(i);
    }

    return EXIT_SUCCESS;
}
