#pragma once

#include <string>
#include <string_view>

#include "Kind.hpp"
#include "Location.hpp"
#include "Value.hpp"

namespace Lexer {

class Token
{
public:
    Token(Kind::kind_t, Value::value_t, std::string, std::size_t, std::size_t);

    [[nodiscard]] const Kind& kind() const;
    [[nodiscard]] const Value& value() const;
    [[nodiscard]] const Location& location() const;

    [[nodiscard]] std::string as_string() const;

public:
    constexpr explicit operator bool() noexcept
    {
        return static_cast<bool>(m_value);
    }

private:
    Kind m_kind;
    Value m_value;
    Location m_location;
};

} // namespace Lexer
