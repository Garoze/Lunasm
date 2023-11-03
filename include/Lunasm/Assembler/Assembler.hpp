#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

#include "Parser/Foward.hpp"
#include "Parser/Instruction.hpp"

#include "Arch.hpp"

#define LIST_OF_INSTRUCTIONS                                                   \
    INST(Nop)                                                                  \
    INST(LoadImmediate)                                                        \
    INST(LoadAddress)                                                          \
    INST(LoadRegister)                                                         \
    INST(StoreImmediate)                                                       \
    INST(StoreAddress)                                                         \
    INST(StoreRegister)                                                        \
    INST(ShiftLeft)                                                            \
    INST(ShiftRight)                                                           \
    INST(And)                                                                  \
    INST(Or)                                                                   \
    INST(Not)                                                                  \
    INST(Xor)                                                                  \
    INST(PushImmediate)                                                        \
    INST(PushAddress)                                                          \
    INST(PushRegister)                                                         \
    INST(Pop)                                                                  \
    INST(Increment)                                                            \
    INST(Decrement)                                                            \
    INST(AddImmediate)                                                         \
    INST(AddAddress)                                                           \
    INST(AddRegister)                                                          \
    INST(SubImmediate)                                                         \
    INST(SubAddress)                                                           \
    INST(SubRegister)                                                          \
    INST(MulImmediate)                                                         \
    INST(MulAddress)                                                           \
    INST(MulRegister)                                                          \
    INST(DivImmediate)                                                         \
    INST(DivAddress)                                                           \
    INST(DivRegister)                                                          \
    INST(ModImmediate)                                                         \
    INST(ModAddress)                                                           \
    INST(ModRegister)                                                          \
    INST(CompareImmediate)                                                     \
    INST(CompareAddress)                                                       \
    INST(CompareRegister)                                                      \
    INST(Jump)                                                                 \
    INST(JumpIfEquals)                                                         \
    INST(JumpIfNotEquals)                                                      \
    INST(Subroutine)                                                           \
    INST(Return)                                                               \
    INST(Halt)                                                                 \
    INST(Label)

namespace Assembler {

class Assembler
{
public:
    Assembler(std::vector<std::uint8_t>&);

    void compile(std::vector<std::unique_ptr<Parser::Instruction>>&);

private:
    void emit8(std::uint8_t);
    void emit8(Arch::Luna16);
    void emit16(std::uint16_t);

#define INST(name) void compile_inst(const Parser::name&, Arch::Luna16);
    LIST_OF_INSTRUCTIONS
#undef INST

    void compile_inst(const Parser::Immediate&, Arch::Luna16);
    void compile_inst(const Parser::Address&, Arch::Luna16);
    void compile_inst(const Parser::Register&, Arch::Luna16);

private:
    std::vector<std::uint8_t>& m_output;
    std::unordered_map<std::string_view, std::uint16_t> m_labels;
};

} // namespace Assembler
