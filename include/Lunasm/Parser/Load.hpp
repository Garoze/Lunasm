#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class LoadImmediate : public Instruction
{
public:
    LoadImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class LoadRegister : public Instruction
{
public:
    LoadRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class LoadAddress : public Instruction
{
public:
    LoadAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

} // namespace Parser
