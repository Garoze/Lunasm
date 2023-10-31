#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class StoreImmediate : public Instruction
{
public:
    StoreImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class StoreRegister : public Instruction
{
public:
    StoreRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class StoreAddress : public Instruction
{
public:
    StoreAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

} // namespace Parser
