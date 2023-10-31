#pragma once

#include <cstdint>
#include <string_view>
#include <variant>

namespace Parser {

class Instruction
{
public:
    enum class kind_t
    {
        Nop,

        LoadImmediate,
        LoadAddress,
        LoadRegister,

        StoreImmediate,
        StoreAddress,
        StoreRegister,

        ShiftLeft,
        ShiftRight,

        And,
        Or,
        Not,
        Xor,

        PushImmediate,
        PushAddress,
        PushRegister,
        Pop,

        Increment,
        Decrement,

        AddImmediate,
        AddAddress,
        AddRegister,

        SubImmediate,
        SubAddress,
        SubRegister,

        MulImmediate,
        MulAddress,
        MulRegister,

        DivImmediate,
        DivAddress,
        DivRegister,

        ModImmediate,
        ModAddress,
        ModRegister,

        CompareImmediate,
        CompareAddress,
        CompareRegister,

        Jump,
        JumpIfEquals,
        JumpIfNotEquals,

        Subroutine,
        Return,

        Halt,

        Label,
    };

    Instruction(kind_t);
    virtual ~Instruction() = default;

    [[nodiscard]] kind_t raw() const;
    [[nodiscard]] virtual std::string as_string() const = 0;

private:
    kind_t m_kind;
};

} // namespace Parser
