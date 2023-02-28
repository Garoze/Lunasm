#include "fmt/core.h"

#include "Lexer.hpp"

int main()
{
    Lunasm::Lexer l("ldi r1, $05");

    return EXIT_SUCCESS;
}
