#include "fmt/core.h"

#include "Parser/Stack.hpp"

namespace Parser {

PushImmediate::PushImmediate(Operand::value_t src)
    : Reference{ kind_t::PushImmediate, src }
{}

std::string PushImmediate::as_string() const
{
    return fmt::format("( PushImmediate src: \"{}\" )", m_src.as_string());
}

PushRegister::PushRegister(Operand::value_t src)
    : Direct{ kind_t::PushRegister, src }
{}

std::string PushRegister::as_string() const
{
    return fmt::format("( PushRegister src: \"{}\" )", m_dst.as_string());
}

PushAddress::PushAddress(Operand::value_t src)
    : Absolute{ kind_t::PushAddress, src }
{}

std::string PushAddress::as_string() const
{
    return fmt::format("( PushAddress src: \"{}\" )", m_src.as_string());
}

Pop::Pop(Operand::value_t dst)
    : Direct{ kind_t::Pop, dst }
{}

std::string Pop::as_string() const
{
    return fmt::format("( Pop dst: \"{}\" )", m_dst.as_string());
}

} // namespace Parser
