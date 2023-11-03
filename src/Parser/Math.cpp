#include "Parser/Math.hpp"
#include "fmt/core.h"

namespace Parser {

Increment::Increment(Operand::value_t dst)
    : Direct{ kind_t::Increment, dst }
{}

std::string Increment::as_string() const
{
    return fmt::format("( Increment dst: \"{}\" )", m_dst.as_string());
}

Decrement::Decrement(Operand::value_t dst)
    : Direct{ kind_t::Decrement, dst }
{}

std::string Decrement::as_string() const
{
    return fmt::format("( Decrement dst: \"{}\" )", m_dst.as_string());
}

AddImmediate::AddImmediate(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::AddImmediate }
    , m_dst(dst)
    , m_src(src)
{}

std::string AddImmediate::as_string() const
{
    return fmt::format("( AddImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

AddAddress::AddAddress(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::AddAddress }
    , m_dst(dst)
    , m_src(src)
{}

std::string AddAddress::as_string() const
{
    return fmt::format("( AddAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

AddRegister::AddRegister(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::AddRegister }
    , m_dst(dst)
    , m_src(src)
{}

std::string AddRegister::as_string() const
{
    return fmt::format("( AddRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

SubImmediate::SubImmediate(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::SubImmediate }
    , m_dst(dst)
    , m_src(src)
{}

std::string SubImmediate::as_string() const
{
    return fmt::format("( SubImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

SubAddress::SubAddress(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::SubAddress }
    , m_dst(dst)
    , m_src(src)
{}

std::string SubAddress::as_string() const
{
    return fmt::format("( SubAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

SubRegister::SubRegister(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::SubRegister }
    , m_dst(dst)
    , m_src(src)
{}

std::string SubRegister::as_string() const
{
    return fmt::format("( SubRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

MulImmediate::MulImmediate(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::MulImmediate }
    , m_dst(dst)
    , m_src(src)
{}

std::string MulImmediate::as_string() const
{
    return fmt::format("( MulImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

MulAddress::MulAddress(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::MulAddress }
    , m_dst(dst)
    , m_src(src)
{}

std::string MulAddress::as_string() const
{
    return fmt::format("( MulAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

MulRegister::MulRegister(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::MulRegister }
    , m_dst(dst)
    , m_src(src)
{}

std::string MulRegister::as_string() const
{
    return fmt::format("( MulRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

DivImmediate::DivImmediate(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::DivImmediate }
    , m_dst(dst)
    , m_src(src)
{}

std::string DivImmediate::as_string() const
{
    return fmt::format("( DivImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

DivAddress::DivAddress(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::DivAddress }
    , m_dst(dst)
    , m_src(src)
{}

std::string DivAddress::as_string() const
{
    return fmt::format("( DivAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

DivRegister::DivRegister(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::DivRegister }
    , m_dst(dst)
    , m_src(src)
{}

std::string DivRegister::as_string() const
{
    return fmt::format("( DivRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

ModImmediate::ModImmediate(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::ModImmediate }
    , m_dst(dst)
    , m_src(src)
{}

std::string ModImmediate::as_string() const
{
    return fmt::format("( ModImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

ModAddress::ModAddress(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::ModAddress }
    , m_dst(dst)
    , m_src(src)
{}

std::string ModAddress::as_string() const
{
    return fmt::format("( ModAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

ModRegister::ModRegister(Operand::value_t dst, Operand::value_t src)
    : Instruction{ kind_t::ModRegister }
    , m_dst(dst)
    , m_src(src)
{}

std::string ModRegister::as_string() const
{
    return fmt::format("( ModRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

} // namespace Parser
