#pragma once

#include <string_view>
#include <unordered_map>

#include "Kind.hpp"

namespace Lexer {

const std::unordered_map<std::string_view, Kind::kind_t> INSTRUCTIONS = {
    { "nop", Kind::kind_t::Nop },
    { "mov", Kind::kind_t::Mov },
    { "shl", Kind::kind_t::ShiftLeft },
    { "shr", Kind::kind_t::ShiftRight },
    { "and", Kind::kind_t::And },
    { "bor", Kind::kind_t::Or },
    { "xor", Kind::kind_t::Xor },
    { "not", Kind::kind_t::Not },
    { "psh", Kind::kind_t::Push },
    { "pop", Kind::kind_t::Pop },
    { "inc", Kind::kind_t::Increment },
    { "dec", Kind::kind_t::Decrement },
    { "add", Kind::kind_t::Add },
    { "sub", Kind::kind_t::Sub },
    { "mul", Kind::kind_t::Mul },
    { "div", Kind::kind_t::Div },
    { "mod", Kind::kind_t::Mod },
    { "cmp", Kind::kind_t::Compare },
    { "jmp", Kind::kind_t::Jump },
    { "jeq", Kind::kind_t::JumpIfEquals },
    { "jne", Kind::kind_t::JumpIfNotEquals },
    { "jsr", Kind::kind_t::Subroutine },
    { "ret", Kind::kind_t::Return },
    { "hlt", Kind::kind_t::Halt },
};

static bool is_instruction(std::string_view inst)
{
    return INSTRUCTIONS.find(inst) != INSTRUCTIONS.end();
}

} // namespace Lexer
