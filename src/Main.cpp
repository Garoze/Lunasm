#include <iostream>

#include "Kind.hpp"
#include "fmt/core.h"

int main()
{
    Lunasm::Kind k(Lunasm::L16TokenKind::NOP);

    fmt::print("Token: {}\n", k.as_string());

    return EXIT_SUCCESS;
}
