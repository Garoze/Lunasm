#include "fmt/core.h"

#include "Parser/Store.hpp"

namespace Parser {

StoreImmediate::StoreImmediate(Operand::value_t dst, Operand::value_t src)
    : Immediate{ kind_t::StoreImmediate, dst, src }
{}

std::string StoreImmediate::as_string() const
{
    return fmt::format("( StoreImmediate: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

StoreAddress::StoreAddress(Operand::value_t dst, Operand::value_t src)
    : Address{ kind_t::StoreAddress, dst, src }
{}

std::string StoreAddress::as_string() const
{
    return fmt::format("( StoreAddress: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

StoreRegister::StoreRegister(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::StoreRegister, dst, src }
{}

std::string StoreRegister::as_string() const
{
    return fmt::format("( StoreRegister: \"{}\" value: \"r{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

}; // namespace Parser
