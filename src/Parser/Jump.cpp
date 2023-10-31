#include "fmt/core.h"

#include "Parser/Jump.hpp"

namespace Parser {

Jump::Jump(Operand::value_t dst)
    : Instruction{ kind_t::Jump }
    , m_dst(dst)
{}

std::string Jump::as_string() const
{
    return fmt::format("( Jump dst: \"{}\" )", m_dst.as_string());
}

JumpIfEquals::JumpIfEquals(Operand::value_t dst)
    : Instruction{ kind_t::JumpIfEquals }
    , m_dst(dst)
{}

std::string JumpIfEquals::as_string() const
{
    return fmt::format("( JumpIfEquals dst: \"{}\" )", m_dst.as_string());
}

JumpIfNotEquals::JumpIfNotEquals(Operand::value_t dst)
    : Instruction{ kind_t::JumpIfNotEquals }
    , m_dst(dst)
{}

std::string JumpIfNotEquals::as_string() const
{
    return fmt::format("( JumpIfNotEquals dst: \"{}\" )", m_dst.as_string());
}

} // namespace Parser
