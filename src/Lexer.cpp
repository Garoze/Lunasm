#include <cctype>
#include <vector>

#include "fmt/core.h"

#include "Lexer/Lexer.hpp"
#include "Lexer/Token.hpp"
#include "Lexer/Instructions.hpp"

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
    if ((m_index + 1) <= m_source_code.length())
    {
        m_index++;
    }
}

void Lexer::space()
{
    if (current_char() == '\n')
    {
        m_line++;
    }

    step();
}

void Lexer::skip(std::size_t n = 1)
{
    if (m_index + n <= m_source_code.length())
    {
        m_index += n;
    }
}

void Lexer::skip(const std::string& message)
{
#ifdef __LEXER_DEBUG__
    fmt::print("DEBUG: {}\n", message);
#endif
    step();
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

    if (index <= m_source_code.length())
    {
        return m_source_code.at(index);
    }

    return {};
}

Token Lexer::Register()
{
    skip("Skipping the 'r' character.");

    switch (char n = eat())
    {
        case '0' ... '7': {
            std::string_view text(m_source_code.c_str() + offset(2), 2);

            return Token(L16TokenKind::Register, m_line, offset(), text);
        }
        default:
            fmt::print("Invalid registe\n");
            std::exit(1);
            break;
    }
}

Token Lexer::Immediate()
{
    auto is_hex = std::isxdigit(peek().value());
    if (!is_hex)
    {
        fmt::print("Exception missing immediate after '$'.\n");
        std::exit(1);
    }

    skip("Skipping the '$' character");

    auto start = offset();

    while (!is_empty() && std::isxdigit(current_char()))
    {
        step();
    }

    std::string_view text(m_source_code.c_str() + start, offset(start));

    return Token(L16TokenKind::Immediate, m_line, offset(), text);
}

Token Lexer::Identifier()
{
    auto start = offset();

    while (!is_empty() && (std::isalnum(current_char()) || current_char() == '_'))
    {
        step();
    }

    std::string_view text(m_source_code.c_str() + start, offset(start));

    if (is_instruction(text))
    {
        return Token(INSTRUCTIONS.at(text), m_line, offset(), text);
    }

    return Token(L16TokenKind::Label, m_line, offset(), text);
}

Token Lexer::next_token()
{
    while (!is_empty())
    {
        switch (current_char())
        {
            case ' ':
            case '\t':
            case '\n': space(); break;

            case '[':
                step();
                return Token(L16TokenKind::OpenBracket, m_line, offset(), "[");
                break;
            case ']':
                step();
                return Token(L16TokenKind::CloseBracket, m_line, offset(), "]");
                break;
            case '+':
                step();
                return Token(L16TokenKind::AddOperation, m_line, offset(), "+");
                break;
            case '-':
                step();
                return Token(L16TokenKind::SubOperation, m_line, offset(), "-");
                break;
            case ',':
                step();
                return Token(L16TokenKind::Comma, m_line, offset(), ",");
                break;
            case ':':
                step();
                return Token(L16TokenKind::Colon, m_line, offset(), ":");
                break;

            case '$': return Immediate(); break;
            case 'r': return Register(); break;
            default: return Identifier(); break;
        }
    }

    fmt::print("[Lexer::Error] -> Line: {} Offset: {} Char: {}\n", m_line, m_index, current_char());
    std::exit(1);
}

std::vector<Token> Lexer::Tokenizer()
{
    std::vector<Token> tokens;

    while (!is_empty())
    {
        tokens.push_back(next_token());
    }

    tokens.push_back(Token(L16TokenKind::END, m_line, offset(), "EOF"));

    return tokens;
}

}  // namespace Lunasm
