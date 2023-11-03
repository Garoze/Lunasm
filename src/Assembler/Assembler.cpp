#include <variant>

#include "fmt/core.h"
#include "fmt/ranges.h"

#include "Assembler/Assembler.hpp"

namespace Assembler {

Assembler::Assembler(std::vector<std::uint8_t>& output)
    : m_output(output)
{}

void Assembler::compile(
    std::vector<std::unique_ptr<Parser::Instruction>>& instructions)
{
    for (auto const& i : instructions)
    {
        switch (i->raw())
        {
#define INST(name)                                                             \
    case Parser::Instruction::kind_t::name:                                    \
        compile_inst(static_cast<const Parser::name&>(*i),                     \
                     Luna16::Opcode::name);                                    \
        break;
            LIST_OF_INSTRUCTIONS
#undef INST
            default:
                break;
        }
    }

    fmt::print("Output: {::02X}\n", m_output);
}

void Assembler::emit8(std::uint8_t value)
{
    m_output.push_back(value);
}

void Assembler::emit8(Luna16::Opcode op)
{
    emit8(static_cast<std::uint8_t>(op));
}

void Assembler::emit16(std::uint16_t value)
{
    m_output.push_back((value >> 0) & 0xff);
    m_output.push_back((value >> 8) & 0xff);
}

void Assembler::compile_inst(const Parser::Implicit& inst,
                             Luna16::Opcode opcode)
{
    emit8(opcode);
}

void Assembler::compile_inst(const Parser::Immediate& inst,
                             Luna16::Opcode opcode)
{
    emit8(opcode);
    emit8(inst.dst().as_u16());
    emit16(inst.src().as_u16());
}

void Assembler::compile_inst(const Parser::Address& inst, Luna16::Opcode opcode)
{
    emit8(opcode);
    emit8(inst.dst().as_u16());
    emit16(m_labels.at(inst.src().as_string_view()));
}

void Assembler::compile_inst(const Parser::Register& inst,
                             Luna16::Opcode opcode)
{
    emit8(opcode);
    emit8(inst.dst().as_u16());
    emit8(inst.src().as_u16());
}

void Assembler::compile_inst(const Parser::Label& inst, Luna16::Opcode opcode)
{
    m_labels[inst.m_label] = m_output.size();
}

// Pattern for 8 8
// Pattern for 8 16

} // namespace Assembler
