#pragma once

#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class ShiftLeft : public Instruction
{
public:
    ShiftLeft(Operand::value_t, Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
    Operand m_src;
};

class ShiftRight : public Instruction
{
public:
    ShiftRight(Operand::value_t, Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
    Operand m_src;
};

class BitwiseAnd : public Instruction
{
public:
    BitwiseAnd(Operand::value_t, Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
    Operand m_src;
};

class BitwiseOr : public Instruction
{
public:
    BitwiseOr(Operand::value_t, Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
    Operand m_src;
};

class BitwiseXor : public Instruction
{
public:
    BitwiseXor(Operand::value_t, Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
    Operand m_src;
};

class BitwiseNot : public Instruction
{
public:
    BitwiseNot(Operand::value_t);

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const override;

private:
    Operand m_dst;
};

} // namespace Parser
