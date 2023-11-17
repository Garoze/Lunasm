#include "fmt/core.h"

#include "Parser/Instructions/Math.hpp"

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
    : Immediate{ kind_t::AddImmediate, dst, src }
{}

std::string AddImmediate::as_string() const
{
    return fmt::format("( AddImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

AddAddress::AddAddress(Operand::value_t dst, Operand::value_t src)
    : Address{ kind_t::AddAddress, dst, src }
{}

std::string AddAddress::as_string() const
{
    return fmt::format("( AddAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

AddRegister::AddRegister(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::AddRegister, dst, src }
{}

std::string AddRegister::as_string() const
{
    return fmt::format("( AddRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

SubImmediate::SubImmediate(Operand::value_t dst, Operand::value_t src)
    : Immediate{ kind_t::SubImmediate, dst, src }
{}

std::string SubImmediate::as_string() const
{
    return fmt::format("( SubImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

SubAddress::SubAddress(Operand::value_t dst, Operand::value_t src)
    : Address{ kind_t::SubAddress, dst, src }
{}

std::string SubAddress::as_string() const
{
    return fmt::format("( SubAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

SubRegister::SubRegister(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::SubRegister, dst, src }
{}

std::string SubRegister::as_string() const
{
    return fmt::format("( SubRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

MulImmediate::MulImmediate(Operand::value_t dst, Operand::value_t src)
    : Immediate{ kind_t::MulImmediate, dst, src }
{}

std::string MulImmediate::as_string() const
{
    return fmt::format("( MulImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

MulAddress::MulAddress(Operand::value_t dst, Operand::value_t src)
    : Address{ kind_t::MulAddress, dst, src }
{}

std::string MulAddress::as_string() const
{
    return fmt::format("( MulAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

MulRegister::MulRegister(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::MulRegister, dst, src }
{}

std::string MulRegister::as_string() const
{
    return fmt::format("( MulRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

DivImmediate::DivImmediate(Operand::value_t dst, Operand::value_t src)
    : Immediate{ kind_t::DivImmediate, dst, src }
{}

std::string DivImmediate::as_string() const
{
    return fmt::format("( DivImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

DivAddress::DivAddress(Operand::value_t dst, Operand::value_t src)
    : Address{ kind_t::DivAddress, dst, src }
{}

std::string DivAddress::as_string() const
{
    return fmt::format("( DivAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

DivRegister::DivRegister(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::DivRegister, dst, src }
{}

std::string DivRegister::as_string() const
{
    return fmt::format("( DivRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

ModImmediate::ModImmediate(Operand::value_t dst, Operand::value_t src)
    : Immediate{ kind_t::ModImmediate, dst, src }
{}

std::string ModImmediate::as_string() const
{
    return fmt::format("( ModImmediate dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

ModAddress::ModAddress(Operand::value_t dst, Operand::value_t src)
    : Address{ kind_t::ModAddress, dst, src }
{}

std::string ModAddress::as_string() const
{
    return fmt::format("( ModAddress dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

ModRegister::ModRegister(Operand::value_t dst, Operand::value_t src)
    : Register{ kind_t::ModRegister, dst, src }
{}

std::string ModRegister::as_string() const
{
    return fmt::format("( ModRegister dst: \"{}\" value: \"{}\" )",
                       m_dst.as_string(), m_src.as_string());
}

} // namespace Parser
