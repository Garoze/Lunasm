#include <argparse/argparse.hpp>
#include <fmt/core.h>

#include "Parser/Parser.hpp"

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

        Lunasm::Parser p{};

        p.parse_file(file, debug);
    }

    return EXIT_SUCCESS;
}
