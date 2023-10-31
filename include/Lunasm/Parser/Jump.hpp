#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class Jump : public Instruction
{
public:
    Jump(Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
};

class JumpIfEquals : public Instruction
{
public:
    JumpIfEquals(Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
};

class JumpIfNotEquals : public Instruction
{
public:
    JumpIfNotEquals(Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
};

} // namespace Parser
