#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class PushImmediate : public Instruction
{
public:
    PushImmediate(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_src;
};

class PushAddress : public Instruction
{
public:
    PushAddress(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_src;
};

class PushRegister : public Instruction
{
public:
    PushRegister(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_src;
};

class Pop : public Instruction
{
public:
    Pop(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
};

} // namespace Parser
