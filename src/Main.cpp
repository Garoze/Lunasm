#include "fmt/core.h"

#include "Lexer.hpp"

int main()
{
    Lunasm::Lexer l("ldi r1, $05\nldi r2, $00\ncmp r1, r2");

    auto tokens = l.Tokenizer();

    for (const auto& t : tokens)
        t.print();

    return EXIT_SUCCESS;
}
