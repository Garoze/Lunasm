#pragma once

#include <string>

namespace Lunasm {

enum class TokenKind {
    // CPU Instructions
    NOP,
    MovInstruction,

    ShiftLeft,
    ShiftRight,

    BitAND,
    BitOR,
    BitXOR,
    BitNOT,

    Push,
    Pop,

    Increment,
    Decrement,

    Add,
    Sub,
    Mul,
    Div,
    Mod,

    Compare,

    Jump,
    JumpEquals,
    JumpNotEquals,

    Subroutine,
    Return,

    Halt,

    // Lexer general stuff
    Register,
    Immediate,
    Label,

    // Literals
    OpenBracket,
    CloseBracket,
    Colon,
    Comma,

    // Binary op
    AddOperation,
    SubOperation,

    END,
};

class Kind
{
public:
    Kind(TokenKind);

    TokenKind raw() const;
    std::string as_string() const;

private:
    TokenKind m_value;
};

}  // namespace Lunasm
