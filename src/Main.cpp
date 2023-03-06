#include "fmt/core.h"

#include "Lexer/Lexer.hpp"

int main()
{
    Lunasm::Lexer l("lda r1, $05\ncmp r1, $05");

    auto tokens = l.Tokenizer();

    for (const auto& t : tokens)
        t.print();

    return EXIT_SUCCESS;
}
