#include "Lexer.hpp"

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

std::size_t Lexer::offset(std::size_t pos = 1) const
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

}  // namespace Lunasm
