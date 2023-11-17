#pragma once

#include "Parser/Operand.hpp"

#include "Parser/Instruction.hpp"

#include "Parser/Modes/Address.hpp"
#include "Parser/Modes/Immediate.hpp"
#include "Parser/Modes/Register.hpp"

namespace Parser {

class LoadImmediate : public Immediate
{
public:
    LoadImmediate(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;
};

class LoadRegister : public Register
{
public:
    LoadRegister(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    [[nodiscard]] const Operand& dst() const;
    [[nodiscard]] const Operand& src() const;

private:
    Operand m_dst;
    Operand m_src;
};

class LoadAddress : public Address
{
public:
    LoadAddress(Operand::value_t, Operand::value_t);

    [[nodiscard]] virtual std::string as_string() const override;

    [[nodiscard]] const Operand& dst() const;
    [[nodiscard]] const Operand& src() const;

private:
    Operand m_dst;
    Operand m_src;
};

} // namespace Parser
