#pragma once

#include <cstdint>
#include <string_view>
#include <variant>

namespace Parser {

class Operand
{
public:
    using value_t =
        std::variant<std::monostate, std::uint16_t, std::string_view>;

    Operand();
    Operand(value_t);

    [[nodiscard]] value_t raw() const;
    [[nodiscard]] std::string as_string() const;

    [[nodiscard]] std::uint16_t as_u16() const;
    [[nodiscard]] std::string_view as_string_view() const;

public:
    constexpr explicit operator bool() noexcept
    {
        return !m_value.valueless_by_exception();
    }

private:
    value_t m_value;
};

} // namespace Parser
