#include <cctype>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

#include "fmt/core.h"

#include "Lexer/Kind.hpp"
#include "Lexer/Lexer.hpp"
#include "Lexer/Token.hpp"
#include "Lexer/Instructions.hpp"

namespace Lunasm {

Lexer::Lexer()
    : m_line(1)
    , m_index(0)
{}

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
    if ((m_index + n) <= m_source_code.length())
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

    if (index < m_source_code.length())
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

            return Token(TokenKind::Register, m_line, offset(), text);
        }
        default: throw std::runtime_error("Invalid Register."); break;
    }
}

Token Lexer::Immediate()
{
    skip("Skipping the '$' character");

    if (!peek(0).has_value() || !std::isxdigit(peek(0).value()))
    {
        auto err = fmt::format("Missing immediate after '$' on line: {} offset: {}", m_line, offset());
        throw std::runtime_error(err);
    }

    auto start = offset();

    while (!is_empty() && std::isxdigit(current_char()))
    {
        step();
    }

    std::string_view text(m_source_code.c_str() + start, offset(start));

    return Token(TokenKind::Immediate, m_line, offset(), text);
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

    return Token(TokenKind::Label, m_line, offset(), text);
}

std::string Lexer::sanitize_input(std::string input)
{
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); });

    return input;
}

Token Lexer::next_token()
{
    while (!is_empty())
    {
        switch (current_char())
        {
            case ' ':
            case '\r':
            case '\t':
            case '\n': space(); break;

            case '[':
                step();
                return Token(TokenKind::OpenBracket, m_line, offset(), "[");
                break;
            case ']':
                step();
                return Token(TokenKind::CloseBracket, m_line, offset(), "]");
                break;
            case '+':
                step();
                return Token(TokenKind::AddOperation, m_line, offset(), "+");
                break;
            case '-':
                step();
                return Token(TokenKind::SubOperation, m_line, offset(), "-");
                break;
            case ',':
                step();
                return Token(TokenKind::Comma, m_line, offset(), ",");
                break;
            case ':':
                step();
                return Token(TokenKind::Colon, m_line, offset(), ":");
                break;

            case '$': return Immediate(); break;
            case 'r':
                if (std::isdigit(peek().value()))  // check if the next char is a number or not.
                {
                    return Register();
                }

            default: return Identifier(); break;
        }
    }

    return Token(TokenKind::END, m_line, offset(), "EOF");
}

std::vector<Token> Lexer::Tokenizer()
{
    std::vector<Token> tokens;

    while (auto token = next_token())
    {
        tokens.push_back(token);

        if (token.kind() == TokenKind::END)
            break;
    }

    return tokens;
}

std::vector<Token> Lexer::Lex_source(std::string source_code)
{
    m_source_code = sanitize_input(source_code);

    return Tokenizer();
}

}  // namespace Lunasm
