#include "fmt/core.h"

#include "Lexer/Lexer.hpp"

int main()
{
    Lunasm::Lexer l("lda r1, $05\nlda r2, $00\nand r1, r2\nxor r1, r2\nbor r1, $10\nnot r2");

    auto tokens = l.Tokenizer();

    for (const auto& t : tokens)
        t.print();

    return EXIT_SUCCESS;
}
