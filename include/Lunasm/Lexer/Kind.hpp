#pragma once

#include <string>

namespace Lexer {

class Kind
{
public:
    enum class kind_t
    {
        Nop,
        Mov,
        ShiftLeft,
        ShiftRight,
        And,
        Or,
        Xor,
        Not,
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
        JumpIfEquals,
        JumpIfNotEquals,
        Subroutine,
        Return,
        Halt,

        Register,
        Immediate,
        Label,

        Hash,
        Dollar,
        Plus,
        Minus,
        Comma,
        Colon,
        SemiColon,
        Equals,
        AtSign,
        OpenSquare,
        CloseSquare,

        __EOF,
    };

    Kind(kind_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] std::string as_string() const;

private:
    kind_t m_kind;
};

} // namespace Lexer
