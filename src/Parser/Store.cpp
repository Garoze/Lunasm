#include "fmt/core.h"

#include "Parser/Store.hpp"

namespace Parser {

// StoreImmediate
StoreImmediate::StoreImmediate(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::StoreImmediate }
    , m_dst(dst)
    , m_src(src)
{}

std::string StoreImmediate::as_string() const
{
    return fmt::format("( StoreImmediate: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

// StoreRegister
StoreRegister::StoreRegister(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::StoreRegister }
    , m_dst(dst)
    , m_src(src)
{}

std::string StoreRegister::as_string() const
{
    return fmt::format("( StoreRegister: \"{}\" value: \"r{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

// StoreAddress
StoreAddress::StoreAddress(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::StoreAddress }
    , m_dst(dst)
    , m_src(src)
{}

std::string StoreAddress::as_string() const
{
    return fmt::format("( StoreAddress: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

}; // namespace Parser
