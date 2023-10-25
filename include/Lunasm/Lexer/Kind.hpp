#pragma once

#include <string>
#include <unordered_map>

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
        Symbol,

        Hash,
        Dollar,
        Plus,
        Minus,
        Equals,
        Comma,
        Colon,
        SemiColon,
        AtSign,
        OpenSquare,
        CloseSquare,
        OpenBracket,
        CloseBracket,
        LeftParen,
        RightParen,

        Module,
        Macro,
        Org,

        ERROR,
        __EOF,
    };

    Kind(kind_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] std::string as_string() const;

private:
    kind_t m_kind;
};

const std::unordered_map<char, Kind::kind_t> CHAR_TO_KIND = {
    { '#', Kind::kind_t::Hash },         { '$', Kind::kind_t::Dollar },
    { '+', Kind::kind_t::Plus },         { '-', Kind::kind_t::Minus },
    { ',', Kind::kind_t::Comma },        { ':', Kind::kind_t::Colon },
    { ';', Kind::kind_t::SemiColon },    { '=', Kind::kind_t::Equals },
    { '@', Kind::kind_t::AtSign },       { '[', Kind::kind_t::OpenSquare },
    { ']', Kind::kind_t::CloseSquare },  { '(', Kind::kind_t::LeftParen },
    { ')', Kind::kind_t::RightParen },   { '{', Kind::kind_t::OpenBracket },
    { '}', Kind::kind_t::CloseBracket },
};

} // namespace Lexer
