#pragma once

#include <string>

namespace Lunasm {

enum class L16TokenKind {
    NOP,

    // Lexer general stuff
    Register,
    Immediate,
    Label,

    // Literals
    OpenBracket,
    CloseBracket,

    AddOperation,
    SubOperation,

    Colon,
    Comma,

    END,
};

class Kind
{
public:
    Kind(L16TokenKind);

    std::string as_string() const;

private:
    L16TokenKind m_kind;
};

}  // namespace Lunasm
