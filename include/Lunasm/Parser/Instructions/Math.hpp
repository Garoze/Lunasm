#pragma once

#include "Parser/Operand.hpp"

#include "Parser/Instructions/Instruction.hpp"

#include "Parser/Modes/Address.hpp"
#include "Parser/Modes/Direct.hpp"
#include "Parser/Modes/Immediate.hpp"
#include "Parser/Modes/Register.hpp"

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

class AddImmediate : public Immediate
{
public:
    AddImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class AddAddress : public Address
{
public:
    AddAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class AddRegister : public Register
{
public:
    AddRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class SubImmediate : public Immediate
{
public:
    SubImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    Operand m_dst;
    Operand m_src;
};

class SubAddress : public Address
{
public:
    SubAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class SubRegister : public Register
{
public:
    SubRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class MulImmediate : public Immediate
{
public:
    MulImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class MulAddress : public Address
{
public:
    MulAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class MulRegister : public Register
{
public:
    MulRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class DivImmediate : public Immediate
{
public:
    DivImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class DivAddress : public Address
{
public:
    DivAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class DivRegister : public Register
{
public:
    DivRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class ModImmediate : public Immediate
{
public:
    ModImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class ModAddress : public Address
{
public:
    ModAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class ModRegister : public Register
{
public:
    ModRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

} // namespace Parser
