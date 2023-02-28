#include "fmt/core.h"

#include "Lexer.hpp"

int main()
{
    Lunasm::Lexer l("ldi r1, $05");
    auto t = l.Identifier();
    t.print();

    return EXIT_SUCCESS;
}
