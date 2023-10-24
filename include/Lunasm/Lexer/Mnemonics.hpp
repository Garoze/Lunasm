#pragma once

#include <unordered_map>

#include "Kind.hpp"

namespace Lexer {

const std::unordered_map<Kind::kind_t, std::string> KIND_TO_STR = {
    { Kind::kind_t::Nop, "Nop" },
    { Kind::kind_t::Mov, "Mov" },
    { Kind::kind_t::ShiftLeft, "ShiftLeft" },
    { Kind::kind_t::ShiftRight, "ShiftRight" },
    { Kind::kind_t::And, "And" },
    { Kind::kind_t::Or, "Or" },
    { Kind::kind_t::Xor, "Xor" },
    { Kind::kind_t::Not, "Not" },
    { Kind::kind_t::Push, "Push" },
    { Kind::kind_t::Pop, "Pop" },
    { Kind::kind_t::Increment, "Increment" },
    { Kind::kind_t::Decrement, "Decrement" },
    { Kind::kind_t::Add, "Add" },
    { Kind::kind_t::Sub, "Sub" },
    { Kind::kind_t::Mul, "Mul" },
    { Kind::kind_t::Div, "Div" },
    { Kind::kind_t::Mod, "Mod" },
    { Kind::kind_t::Compare, "Compare" },
    { Kind::kind_t::Jump, "Jump" },
    { Kind::kind_t::JumpIfEquals, "JumpIfEquals" },
    { Kind::kind_t::JumpIfNotEquals, "JumpIfNotEquals" },
    { Kind::kind_t::Subroutine, "Subroutine" },
    { Kind::kind_t::Return, "Return" },
    { Kind::kind_t::Halt, "Halt" },
    { Kind::kind_t::Register, "Register" },
    { Kind::kind_t::Immediate, "Immediate" },
    { Kind::kind_t::Label, "Label" },
    { Kind::kind_t::Hash, "Hash" },
    { Kind::kind_t::Dollar, "Dollar" },
    { Kind::kind_t::Plus, "Plus" },
    { Kind::kind_t::Minus, "Minus" },
    { Kind::kind_t::Equals, "Equals" },
    { Kind::kind_t::Comma, "Comma" },
    { Kind::kind_t::Colon, "Colon" },
    { Kind::kind_t::SemiColon, "SemiColon" },
    { Kind::kind_t::AtSign, "AtSign" },
    { Kind::kind_t::OpenSquare, "OpenSquare" },
    { Kind::kind_t::CloseSquare, "CloseSquare" },
    { Kind::kind_t::ERROR, "Error" },
    { Kind::kind_t::__EOF, "EOF" },
};

} // namespace Lexer
