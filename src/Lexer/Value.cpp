#include <cstdint>
#include <string>

#include "Lexer/Value.hpp"

namespace Lexer {

Value::Value(value_t value)
    : m_value(value)
{}

Value::value_t Value::raw() const
{
    return m_value;
}

std::string Value::as_string() const
{
    auto visitor = [&](auto& arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::monostate>)
        {
            return "";
        }
        else if constexpr (std::is_same_v<T, std::uint16_t>)
        {
            return std::to_string(arg);
        }
        else if constexpr (std::is_same_v<T, std::string_view>)
        {
            return std::string{ arg };
        }
    };

    return std::visit(visitor, m_value);
}

} // namespace Lexer
