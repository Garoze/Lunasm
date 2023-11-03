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
                     Arch::Luna16::name);                                      \
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

void Assembler::emit8(Arch::Luna16 op)
{
    emit8(static_cast<std::uint8_t>(op));
}

void Assembler::emit16(std::uint16_t value)
{
    m_output.push_back((value >> 0) & 0xff);
    m_output.push_back((value >> 8) & 0xff);
}

void Assembler::compile_inst(const Parser::Immediate& inst, Arch::Luna16 opcode)
{
    emit8(opcode);
    emit8(inst.dst().as_u16());
    emit16(inst.src().as_u16());
}

void Assembler::compile_inst(const Parser::Address& inst, Arch::Luna16 opcode)
{
    emit8(opcode);
    emit8(inst.dst().as_u16());
    emit16(m_labels.at(inst.src().as_string_view()));
}

void Assembler::compile_inst(const Parser::Register& inst, Arch::Luna16 opcode)
{
    emit8(opcode);
    emit8(inst.dst().as_u16());
    emit8(inst.src().as_u16());
}

void Assembler::compile_inst(const Parser::Nop& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Nop));
}

void Assembler::compile_inst(const Parser::LoadImmediate& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::LoadImmediate));
    emit8(op.dst().as_u16());
    emit16(op.src().as_u16());
}

void Assembler::compile_inst(const Parser::LoadAddress& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::LoadAddress));
    emit8(op.dst().as_u16());
    emit16(m_labels.at(op.src().as_string_view()));
}

void Assembler::compile_inst(const Parser::LoadRegister& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::LoadRegister));
    emit8(op.dst().as_u16());
    emit8(op.src().as_u16());
}

void Assembler::compile_inst(const Parser::StoreImmediate& op,
                             Arch::Luna16 opcode)
{

    emit8(static_cast<std::uint8_t>(Arch::Luna16::StoreImmediate));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit16(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::StoreAddress& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::StoreAddress));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    auto address = m_labels.at(std::get<std::string_view>(op.m_src.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::StoreRegister& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::StoreRegister));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::ShiftLeft& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::ShiftLeft));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::ShiftRight& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::ShiftRight));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::And& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::And));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::Or& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Or));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::Not& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Not));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
}

void Assembler::compile_inst(const Parser::Xor& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Xor));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::PushImmediate& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::PushImmediate));
    emit16(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::PushAddress& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::PushAddress));
    auto address = m_labels.at(std::get<std::string_view>(op.m_src.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::PushRegister& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::PushRegister));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::Pop& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Pop));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
}

void Assembler::compile_inst(const Parser::Increment& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Increment));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
}

void Assembler::compile_inst(const Parser::Decrement& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Decrement));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
}

void Assembler::compile_inst(const Parser::AddImmediate& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::AddImmediate));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit16(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::AddAddress& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::AddAddress));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    auto address = m_labels.at(std::get<std::string_view>(op.m_src.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::AddRegister& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::AddRegister));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::SubImmediate& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::SubImmediate));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit16(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::SubAddress& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::SubAddress));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    auto address = m_labels.at(std::get<std::string_view>(op.m_src.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::SubRegister& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::SubRegister));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::MulImmediate& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::MulImmediate));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit16(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::MulAddress& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::MulAddress));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    auto address = m_labels.at(std::get<std::string_view>(op.m_src.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::MulRegister& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::MulRegister));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::DivImmediate& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::DivImmediate));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit16(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::DivAddress& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::DivAddress));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    auto address = m_labels.at(std::get<std::string_view>(op.m_src.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::DivRegister& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::DivRegister));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::ModImmediate& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::ModImmediate));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit16(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::ModAddress& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::ModAddress));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    auto address = m_labels.at(std::get<std::string_view>(op.m_src.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::ModRegister& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::ModRegister));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::CompareImmediate& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::CompareImmediate));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit16(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::CompareAddress& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::CompareAddress));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    auto address = m_labels.at(std::get<std::string_view>(op.m_src.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::CompareRegister& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::CompareRegister));
    emit8(std::get<std::uint16_t>(op.m_dst.raw()));
    emit8(std::get<std::uint16_t>(op.m_src.raw()));
}

void Assembler::compile_inst(const Parser::Jump& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Jump));
    auto address = m_labels.at(std::get<std::string_view>(op.m_dst.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::JumpIfEquals& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::JumpIfEquals));
    auto address = m_labels.at(std::get<std::string_view>(op.m_dst.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::JumpIfNotEquals& op,
                             Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::JumpIfNotEquals));
    auto address = m_labels.at(std::get<std::string_view>(op.m_dst.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::Subroutine& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Subroutine));
    auto address = m_labels.at(std::get<std::string_view>(op.m_dst.raw()));
    emit16(address);
}

void Assembler::compile_inst(const Parser::Return& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Return));
}

void Assembler::compile_inst(const Parser::Halt& op, Arch::Luna16 opcode)
{
    emit8(static_cast<std::uint8_t>(Arch::Luna16::Halt));
}

void Assembler::compile_inst(const Parser::Label& op, Arch::Luna16 opcode)
{
    m_labels[op.m_label] = m_output.size();
}

} // namespace Assembler
