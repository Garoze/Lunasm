#include "fmt/core.h"

#include "Parser/Instructions/Compare.hpp"

namespace Parser {

CompareImmediate::CompareImmediate(Operand::value_t dst, Operand::value_t src)
    : Immediate{ kind_t::CompareImmediate, dst, src }
{}

std::string CompareImmediate::as_string() const
{
    return fmt::format("( CompareImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

CompareAddress::CompareAddress(Operand::value_t dst, Operand::value_t src)
    : Address{ kind_t::CompareAddress, dst, src }
{}

std::string CompareAddress::as_string() const
{
    return fmt::format("( CompareAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

CompareRegister::CompareRegister(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::CompareRegister, dst, src }
{}

std::string CompareRegister::as_string() const
{
    return fmt::format("( CompareRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

} // namespace Parser
