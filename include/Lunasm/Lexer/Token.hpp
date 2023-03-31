#pragma once

#include <string>
#include <unordered_map>

#include "Kind.hpp"

namespace Lunasm {

class Token
{
public:
    Token(Kind, std::size_t, std::size_t, std::string_view);

    void print() const;

    TokenKind kind() const;

    constexpr explicit operator bool() noexcept { return true; }

private:
    Kind m_kind;
    std::size_t m_line;
    std::size_t m_offset;
    std::string_view m_text;
};

}  // namespace Lunasm
