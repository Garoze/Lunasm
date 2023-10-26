#include "fmt/core.h"

#include "Parser/Load.hpp"

namespace Parser {

// LoadImmediate
LoadImmediate::LoadImmediate(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::LoadImmediate }
    , m_dst(dst)
    , m_src(src)
{}

std::string LoadImmediate::as_string() const
{
    return fmt::format("( LoadImmediate: \"r{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

// LoadRegister
LoadRegister::LoadRegister(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::LoadRegister }
    , m_dst(dst)
    , m_src(src)
{}

std::string LoadRegister::as_string() const
{
    return fmt::format("( LoadRegister: \"r{}\" value: \"r{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

// LoadAddress
LoadAddress::LoadAddress(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::LoadAddress }
    , m_dst(dst)
    , m_src(src)
{}

std::string LoadAddress::as_string() const
{
    return fmt::format("( LoadAddress: \"r{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

}; // namespace Parser
