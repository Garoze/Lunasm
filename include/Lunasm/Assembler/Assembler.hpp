#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Parser/Foward.hpp"
#include "Parser/Instruction.hpp"

#include "Luna16.hpp"

// #define LIST_OF_INSTRUCTIONS                                                   \
//     INST(Nop)                                                                  \
//     INST(LoadImmediate)                                                        \
//     INST(LoadAddress)                                                          \
//     INST(LoadRegister)                                                         \
//     INST(StoreImmediate)                                                       \
//     INST(StoreAddress)                                                         \
//     INST(StoreRegister)                                                        \
//     INST(ShiftLeft)                                                            \
//     INST(ShiftRight)                                                           \
//     INST(And)                                                                  \
//     INST(Or)                                                                   \
//     INST(Not)                                                                  \
//     INST(Xor)                                                                  \
//     INST(PushImmediate)                                                        \
//     INST(PushAddress)                                                          \
//     INST(PushRegister)                                                         \
//     INST(Pop)                                                                  \
//     INST(Increment)                                                            \
//     INST(Decrement)                                                            \
//     INST(AddImmediate)                                                         \
//     INST(AddAddress)                                                           \
//     INST(AddRegister)                                                          \
//     INST(SubImmediate)                                                         \
//     INST(SubAddress)                                                           \
//     INST(SubRegister)                                                          \
//     INST(MulImmediate)                                                         \
//     INST(MulAddress)                                                           \
//     INST(MulRegister)                                                          \
//     INST(DivImmediate)                                                         \
//     INST(DivAddress)                                                           \
//     INST(DivRegister)                                                          \
//     INST(ModImmediate)                                                         \
//     INST(ModAddress)                                                           \
//     INST(ModRegister)                                                          \
//     INST(CompareImmediate)                                                     \
//     INST(CompareAddress)                                                       \
//     INST(CompareRegister)                                                      \
//     INST(Jump)                                                                 \
//     INST(JumpIfEquals)                                                         \
//     INST(JumpIfNotEquals)                                                      \
//     INST(Subroutine)                                                           \
//     INST(Return)                                                               \
//     INST(Halt)                                                                 \
//     INST(Label)
//

#define LIST_OF_INSTRUCTIONS                                                   \
    INST(Nop)                                                                  \
    INST(LoadImmediate)                                                        \
    INST(LoadAddress)                                                          \
    INST(LoadRegister)                                                         \
    INST(Return)                                                               \
    INST(Halt)

namespace Assembler {

class Assembler
{
public:
    Assembler(std::vector<std::uint8_t>&);

    void compile(std::vector<std::unique_ptr<Parser::Instruction>>&);

private:
    void emit8(std::uint8_t);
    void emit8(Luna16::Opcode);
    void emit16(std::uint16_t);

    void compile_inst(const Parser::Immediate&, Luna16::Opcode);
    void compile_inst(const Parser::Address&, Luna16::Opcode);
    void compile_inst(const Parser::Register&, Luna16::Opcode);
    void compile_inst(const Parser::Implicit&, Luna16::Opcode);
    void compile_inst(const Parser::Label&, Luna16::Opcode);

private:
    std::vector<std::uint8_t>& m_output;
    std::unordered_map<std::string_view, std::uint16_t> m_labels;
};

} // namespace Assembler
