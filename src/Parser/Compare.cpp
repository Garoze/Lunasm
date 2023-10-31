#include "Parser/Compare.hpp"
#include "fmt/core.h"

namespace Parser {

CompareImmediate::CompareImmediate(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::CompareImmediate }
    , m_dst(dst)
    , m_src(src)
{}

std::string CompareImmediate::as_string() const
{
    return fmt::format("( CompareImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

CompareAddress::CompareAddress(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::CompareAddress }
    , m_dst(dst)
    , m_src(src)
{}

std::string CompareAddress::as_string() const
{
    return fmt::format("( CompareAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

CompareRegister::CompareRegister(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::CompareRegister }
    , m_dst(dst)
    , m_src(src)
{}

std::string CompareRegister::as_string() const
{
    return fmt::format("( CompareRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

} // namespace Parser
