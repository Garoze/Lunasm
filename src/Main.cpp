#include "fmt/core.h"

#include "Lexer/Lexer.hpp"

int main()
{
    Lunasm::Lexer l("__start:ldi r1, $05\n__loop:\ncmi r1, $00\njnq [loop]");

    auto tokens = l.Tokenizer();

    for (const auto& t : tokens)
        t.print();

    return EXIT_SUCCESS;
}
