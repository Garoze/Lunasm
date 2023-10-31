#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class CompareImmediate : public Instruction
{
public:
    CompareImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
    Operand m_src;
};

class CompareAddress : public Instruction
{
public:
    CompareAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
    Operand m_src;
};

class CompareRegister : public Instruction
{
public:
    CompareRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
    Operand m_src;
};

} // namespace Parser
