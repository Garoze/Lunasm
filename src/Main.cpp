#include "fmt/core.h"

#include "Token.hpp"

int main()
{
    Lunasm::Token t(Lunasm::L16TokenKind::NOP, 1, 3, "NOP");
    t.print();

    return EXIT_SUCCESS;
}
