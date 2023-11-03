#pragma once

#include "Parser/Direct.hpp"
#include "Parser/Instruction.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

class Increment : public Direct
{
public:
    Increment(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class Decrement : public Direct
{
public:
    Decrement(Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class AddImmediate : public Instruction
{
public:
    AddImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class AddAddress : public Instruction
{
public:
    AddAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};
class AddRegister : public Instruction
{
public:
    AddRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class SubImmediate : public Instruction
{
public:
    SubImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class SubAddress : public Instruction
{
public:
    SubAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class SubRegister : public Instruction
{
public:
    SubRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class MulImmediate : public Instruction
{
public:
    MulImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class MulAddress : public Instruction
{
public:
    MulAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class MulRegister : public Instruction
{
public:
    MulRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class DivImmediate : public Instruction
{
public:
    DivImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class DivAddress : public Instruction
{
public:
    DivAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class DivRegister : public Instruction
{
public:
    DivRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class ModImmediate : public Instruction
{
public:
    ModImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class ModAddress : public Instruction
{
public:
    ModAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class ModRegister : public Instruction
{
public:
    ModRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

} // namespace Parser
