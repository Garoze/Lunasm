#include "fmt/core.h"

#include "Parser/Bitwise.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

ShiftLeft::ShiftLeft(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::ShiftLeft, dst, src }
{}

std::string ShiftLeft::as_string() const
{
    return fmt::format("( ShiftLeft dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

ShiftRight::ShiftRight(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::ShiftLeft, dst, src }
{}

std::string ShiftRight::as_string() const
{
    return fmt::format("( ShiftRight dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

And::And(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::And, dst, src }
{}

std::string And::as_string() const
{
    return fmt::format("( And dst: \"{}\" value: \"{}\" )", m_dst.as_string(),
                       m_src.as_string());
}

Or::Or(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::Or, dst, src }
{}

std::string Or::as_string() const
{
    return fmt::format("( Or dst: \"{}\" value: \"{}\" )", m_dst.as_string(),
                       m_src.as_string());
}

Xor::Xor(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::Xor, dst, src }
{}

std::string Xor::as_string() const
{
    return fmt::format("( Xor dst: \"{}\" value: \"{}\" )", m_dst.as_string(),
                       m_src.as_string());
}

Not::Not(Operand::value_t dst)
    : Direct{ kind_t::Not, dst }
{}

std::string Not::as_string() const
{
    return fmt::format("( Not dst: \"{}\" )", m_dst.as_string());
}

} // namespace Parser
