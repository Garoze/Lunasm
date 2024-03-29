#pragma once

#include <cstdint>
#include <string_view>
#include <variant>

namespace Lexer {

class Value
{
public:
    using value_t =
        std::variant<std::monostate, std::uint16_t, std::string_view>;

    Value(value_t);

    [[nodiscard]] value_t raw() const;
    [[nodiscard]] std::string as_string() const;

public:
    constexpr explicit operator bool() noexcept
    {
        return !m_value.valueless_by_exception();
    }

private:
    value_t m_value;
};

} // namespace Lexer
