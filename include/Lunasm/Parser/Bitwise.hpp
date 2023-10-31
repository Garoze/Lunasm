#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class ShiftLeft : public Instruction
{
public:
    ShiftLeft(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class ShiftRight : public Instruction
{
public:
    ShiftRight(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class And : public Instruction
{
public:
    And(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class Or : public Instruction
{
public:
    Or(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class Xor : public Instruction
{
public:
    Xor(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class Not : public Instruction
{
public:
    Not(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
};

} // namespace Parser
