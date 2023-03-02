#include "fmt/core.h"

#include "Lexer.hpp"

int main()
{
    Lunasm::Lexer l("__start:\nldi r1, $05\nlda r2, [r1 + 10]");

    auto tokens = l.Tokenizer();

    for (const auto& t : tokens)
        t.print();

    return EXIT_SUCCESS;
}
