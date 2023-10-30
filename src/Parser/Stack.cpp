#include "Parser/Stack.hpp"
#include "fmt/core.h"

namespace Parser {

PushImmediate::PushImmediate(Operand::value_t src)
    : Instruction{ kind_t::PushImmediate }
    , m_src(src)
{}

std::string PushRegister::as_string() const
{
    return fmt::format("( PushRegister src: \"{}\" )", m_src.as_string());
}

PushRegister::PushRegister(Operand::value_t src)
    : Instruction{ kind_t::PushRegister }
    , m_src(src)
{}

std::string PushImmediate::as_string() const
{
    return fmt::format("( PushImmediate src: \"{}\" )", m_src.as_string());
}

PushAddress::PushAddress(Operand::value_t src)
    : Instruction{ kind_t::PushAddress }
    , m_src(src)
{}

std::string PushAddress::as_string() const
{
    return fmt::format("( PushAddress src: \"{}\" )", m_src.as_string());
}

Pop::Pop(Operand::value_t dst)
    : Instruction{ kind_t::Pop }
    , m_dst(dst)
{}

std::string Pop::as_string() const
{
    return fmt::format("( Pop dst: \"{}\" )", m_dst.as_string());
}

} // namespace Parser
