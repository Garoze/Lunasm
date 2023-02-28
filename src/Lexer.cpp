#include <cctype>

#include "fmt/core.h"

#include "Lexer.hpp"
#include "Token.hpp"

namespace Lunasm {

Lexer::Lexer(const std::string& source_code)
    : m_line(1)
    , m_index(0)
    , m_source_code(source_code)
{}

char Lexer::eat()
{
    return m_source_code.at(m_index++);
}

void Lexer::step()
{
    m_index++;
}

void Lexer::skip(std::size_t n = 1)
{
    m_index += n;
}

void Lexer::skip(const std::string& message)
{
#ifdef __LEXER_DEBUG__
    fmt::print("DEBUG: {}\n", message);
#endif
    m_index++;
}

char Lexer::current_char() const
{
    return m_source_code.at(m_index);
}

bool Lexer::is_empty() const
{
    return m_index >= m_source_code.length();
}

std::size_t Lexer::offset(std::size_t pos = 0) const
{
    return m_index - pos;
}

std::optional<char> Lexer::peek(std::size_t pos = 1) const
{
    auto index = m_index + pos;

    if (index < m_source_code.length())
    {
        return m_source_code.at(index);
    }

    return {};
}

Token Lexer::Immediate()
{
    auto is_hex = std::isxdigit(peek().value());
    if (!is_hex)
    {
        fmt::print("Exception missing immediate after $");
        std::exit(1);
    }

    skip("Skipping the '$' character");

    auto start = offset();

    while (!is_empty() && std::isxdigit(current_char()))
    {
        step();
    }

    std::string_view text(m_source_code.c_str() + start, offset(start));

    // FIXME: use the right kind <Immediate>
    return Token(L16TokenKind::NOP, m_line, offset(), text);
}

Token Lexer::Identifier()
{
    auto start = offset();

    while (!is_empty() && std::isalnum(current_char()))
    {
        step();
    }

    std::string_view text(m_source_code.c_str() + start, offset(start));

    // TODO: Verify if the text is a keyword/instruction or label
    // FIXME: also use the right kind on the Token constructor
    return Token(L16TokenKind::NOP, m_line, offset(), text);
}

}  // namespace Lunasm
