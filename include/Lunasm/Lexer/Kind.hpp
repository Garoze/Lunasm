#pragma once

#include <string>

namespace Lunasm {

enum class L16TokenKind {

    // CPU Instructions
    NOP,
    LoadInstruction,
    StoreInstruction,

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
    Kind(L16TokenKind);

    std::string as_string() const;

    L16TokenKind raw() const;

private:
    L16TokenKind m_kind;
};

}  // namespace Lunasm
