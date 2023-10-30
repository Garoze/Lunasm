#include "fmt/core.h"

#include "Parser/Bitwise.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

ShiftLeft::ShiftLeft(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::ShiftLeft }
    , m_dst(dst)
    , m_src(src)
{}

std::string ShiftLeft::as_string() const
{
    return fmt::format("( ShiftLeft dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

ShiftRight::ShiftRight(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::ShiftRight }
    , m_dst(dst)
    , m_src(src)
{}

std::string ShiftRight::as_string() const
{
    return fmt::format("( ShiftRight dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

BitwiseAnd::BitwiseAnd(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::And }
    , m_dst(dst)
    , m_src(src)
{}

std::string BitwiseAnd::as_string() const
{
    return fmt::format("( And dst: \"{}\" value: \"{}\" )", m_dst.as_string(),
                       m_src.as_string());
}

BitwiseOr::BitwiseOr(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::Or }
    , m_dst(dst)
    , m_src(src)
{}

std::string BitwiseOr::as_string() const
{
    return fmt::format("( Or dst: \"{}\" value: \"{}\" )", m_dst.as_string(),
                       m_src.as_string());
}

BitwiseXor::BitwiseXor(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::Xor }
    , m_dst(dst)
    , m_src(src)
{}

std::string BitwiseXor::as_string() const
{
    return fmt::format("( Xor dst: \"{}\" value: \"{}\" )", m_dst.as_string(),
                       m_src.as_string());
}

BitwiseNot::BitwiseNot(Operand::value_t dst)
    : Instruction{ kind_t::Not }
    , m_dst(dst)
{}

std::string BitwiseNot::as_string() const
{
    return fmt::format("( Not dst: \"{}\" )", m_dst.as_string());
}

} // namespace Parser
