#include "fmt/core.h"

#include "Parser/Instructions/Load.hpp"

namespace Parser {

LoadImmediate::LoadImmediate(Operand::value_t dst, Operand::value_t src)
    : Immediate{ kind_t::LoadImmediate, dst, src }
{}

std::string LoadImmediate::as_string() const
{
    return fmt::format("( LoadImmediate {} {} )", m_dst.as_string(),
                       m_src.as_string());
}

LoadRegister::LoadRegister(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::LoadRegister, dst, src }
{}

std::string LoadRegister::as_string() const
{
    return fmt::format("( LoadRegister: \"r{}\" value: \"r{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

LoadAddress::LoadAddress(Operand::value_t dst, Operand::value_t src)
    : Address{ kind_t::LoadAddress, dst, src }
{}

std::string LoadAddress::as_string() const
{
    return fmt::format("( LoadAddress: \"r{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

}; // namespace Parser
