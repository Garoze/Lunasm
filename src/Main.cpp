#include "fmt/core.h"

#include "Lexer/Lexer.hpp"

int main()
{
    Lunasm::Lexer l("start:\nlda r1, $05\nloop:\nsub r1, $01\ncmp r1, $00\njne [loop]\nhlt");

    auto tokens = l.Tokenizer();

    for (const auto& t : tokens)
        t.print();

    return EXIT_SUCCESS;
}
