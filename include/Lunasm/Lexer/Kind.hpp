#pragma once

#include <string>

namespace Lunasm {

enum class TokenKind {

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
    Kind(TokenKind);

    std::string as_string() const;

    TokenKind raw() const;

private:
    TokenKind m_kind;
};

}  // namespace Lunasm
