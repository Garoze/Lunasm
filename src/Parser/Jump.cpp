#include "fmt/core.h"

#include "Parser/Jump.hpp"

namespace Parser {

Jump::Jump(Operand::value_t dst)
    : Absolute{ kind_t::Jump, dst }
{}

std::string Jump::as_string() const
{
    return fmt::format("( Jump dst: \"{}\" )", m_src.as_string());
}

JumpIfEquals::JumpIfEquals(Operand::value_t dst)
    : Absolute{ kind_t::JumpIfEquals, dst }
{}

std::string JumpIfEquals::as_string() const
{
    return fmt::format("( JumpIfEquals dst: \"{}\" )", m_src.as_string());
}

JumpIfNotEquals::JumpIfNotEquals(Operand::value_t dst)
    : Absolute{ kind_t::JumpIfNotEquals, dst }
{}

std::string JumpIfNotEquals::as_string() const
{
    return fmt::format("( JumpIfNotEquals dst: \"{}\" )", m_src.as_string());
}

} // namespace Parser
