#pragma once

#include <string>

namespace Lunasm {

enum class L16TokenKind {
    NOP,

    // Load instructions
    LoadImmediate,
    LoadAddress,
    LoadRegister,

    // Store instructions
    StoreImmediate,
    StoreAddress,
    StoreRegister,

    // Bitwise
    ShiftLeft,
    ShiftRight,

    BitwiseAnd,
    BitwiseOr,
    BitwiseXor,
    BitwiseNot,

    // Stack
    PushImmediate,
    PushAddress,
    PushRegister,
    Pop,

    Increment,
    Decrement,

    // Compares
    CmpImmediate,
    CmpAddress,
    CmpRegister,

    // Jumps
    Jump,
    JumpEquals,
    JumpNotEquals,

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
