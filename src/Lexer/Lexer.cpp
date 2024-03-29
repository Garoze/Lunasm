#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

#include "fmt/core.h"

#include "Lexer/Keywords.hpp"
#include "Lexer/Kind.hpp"
#include "Lexer/Lexer.hpp"
#include "Lexer/Token.hpp"

namespace Lexer {

Lexer::Lexer()
    : m_line(1)
    , m_index(0)
{}

Lexer::Lexer(const std::string& source_code)
    : m_line(1)
    , m_index(0)
    , m_source_code(source_code)
{}

void Lexer::step()
{
    if ((m_index + 1) <= m_source_code.length())
    {
        m_index++;
    }
}

bool Lexer::is_empty() const
{
    return m_index >= m_source_code.length();
}

char Lexer::current_char() const
{
    return m_source_code.at(m_index);
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

std::string Lexer::sanitize_input(std::string input)
{
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    return input;
}

void Lexer::handle_space()
{
    if (current_char() == '\n')
    {
        m_line++;
    }

    step();
}

void Lexer::lex_comments()
{
    switch (current_char())
    {
        case ';':
            while (!is_empty() && current_char() != '\n')
            {
                step();
            }
            break;

        default:
            break;
    }
}

Token Lexer::lex_directives()
{
    switch (current_char())
    {
        case '@':
        {
            step();
            auto start = m_index;

            while (!is_empty() &&
                   (std::isalnum(current_char()) || current_char() == '_'))
            {
                step();
            }

            auto text = std::string_view{ m_source_code }.substr(
                start, m_index - start);

            if (!is_directive(text))
            {
                return Token(Kind::kind_t::ERROR, "Invalid Directive", "",
                             m_line, m_index);
            }

            return Token(DIRECTIVES.at(text), text, "", m_line, m_index);
        }
        break;
    }

    return Token(Kind::kind_t::ERROR, "Invalid directive", "", m_line, m_index);
}

Token Lexer::lex_separators()
{
    switch (char c = current_char())
    {
        case ',':
        case ':':
        case '[':
        case ']':
        case '(':
        case ')':
        case '{':
        case '}':
            step();
            return Token(
                CHAR_TO_KIND.at(c),
                std::string_view{ m_source_code }.substr(m_index - 1, 1), "",
                m_line, m_index);
            break;

        default:
            fmt::print("Invalid Separator on Line: {} and Column: {} -> {}\n",
                       m_line, m_index, c);
            break;
    }

    return Token(Kind::kind_t::ERROR, "Invalid token from lex_separators", "",
                 m_line, m_index);
}

Token Lexer::lex_operators()
{
    switch (char c = current_char())
    {
        case '+':
        case '-':
        case '=':
            step();
            return Token(
                CHAR_TO_KIND.at(c),
                std::string_view{ m_source_code }.substr(m_index - 1, 1), "",
                m_line, m_index);
            break;

        default:
            fmt::print("Invalid Operator on Line: {} and Column: {} -> {}\n",
                       m_line, m_index, c);
            break;
    }

    return Token(Kind::kind_t::ERROR, "Invalid token from lex_operators", "",
                 m_line, m_index);
}

const std::unordered_map<char, int> CHAR_TO_DIGIT = {
    { '0', 0 },  { '1', 1 },  { '2', 2 },  { '3', 3 },
    { '4', 4 },  { '5', 5 },  { '6', 6 },  { '7', 7 },
    { '8', 8 },  { '9', 9 },  { 'a', 10 }, { 'b', 11 },
    { 'c', 12 }, { 'd', 13 }, { 'e', 14 }, { 'f', 15 },
};

std::uint16_t Lexer::get_base()
{
    std::uint16_t base{ 10 };

    switch (current_char())
    {
        case '#':
        case '$':
            step();
            base = 16;
            break;

        case '0':
            step();
            switch (current_char())
            {
                case 'x':
                    step();
                    base = 16;
                    break;
                case 'b':
                    step();
                    base = 2;
                    break;
                default:
                    base = 8;
                    break;
            }
            break;
    }

    return base;
}

Token Lexer::lex_immediates()
{
    std::uint16_t value{ 0 };
    std::uint16_t base = get_base();

    while (!is_empty() &&
           (std::isdigit(current_char()) || std::isxdigit(current_char())))
    {
        double digit = CHAR_TO_DIGIT.at(current_char());

        if (digit == 0 && is_empty())
        {
            break;
        }

        if (digit >= base)
        {
            auto err =
                fmt::format("Digit '{}' out of range for base {}", digit, base);

            return Token(Kind::kind_t::ERROR, err, "", m_line, m_index);
            digit = 0;
        }

        if (value > (std::numeric_limits<std::uint16_t>::max() / base))
        {
            auto err = fmt::format("Integer literal overflow");

            return Token(Kind::kind_t::ERROR, err, "", m_line, m_index);

            while (isdigit(current_char()))
            {
                step();
            }
            value = 0;
            break;
        }

        value = (value * base) + digit;
        step();
    }

    return Token(Kind::kind_t::Immediate, value, "", m_line, m_index);
}

Token Lexer::lex_registers()
{
    switch (current_char())
    {
        case 'r':
            step();
            switch (char r = current_char())
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                    step();
                    return Token(Kind::kind_t::Register,
                                 static_cast<std::uint16_t>(r - '0'), "",
                                 m_line, m_index);

                default:
                    return Token(Kind::kind_t::ERROR, "Invalid Register", "",
                                 m_line, m_index);
                    break;
            }
            break;

        default:
            return lex_instructions();
            break;
    }

    return Token(Kind::kind_t::ERROR, "Invalid Register", "", m_line, m_index);
}

Token Lexer::lex_instructions()
{
    auto start = m_index;

    while (!is_empty() &&
           (std::isalnum(current_char()) || current_char() == '_'))
    {
        step();
    }

    auto text =
        std::string_view{ m_source_code }.substr(start, m_index - start);

    if (is_instruction(text))
    {
        return Token(INSTRUCTIONS.at(text), text, "", m_line, m_index);
    }

    return Token(Kind::kind_t::Symbol, text, "", m_line, m_index);
}

std::vector<Token> Lexer::Tokenizer()
{
    std::vector<Token> tokens;

    while (auto token = next_token())
    {
        tokens.push_back(token);

        if (token.kind().raw() == Kind::kind_t::__EOF)
            break;
    }

    return tokens;
}

std::vector<Token> Lexer::Lex_source(std::string source_code)
{
    m_source_code = sanitize_input(source_code);

    return Tokenizer();
}

std::vector<Token> Lexer::Lex_file(std::filesystem::path const& file_path,
                                   bool debug = false)
{
    std::stringstream ss;

    const std::ifstream file(file_path, std::ios::in);

    if (!file.good())
    {
        auto err =
            fmt::format("Could not open the file {}", file_path.string());
        throw std::runtime_error(err);
    }

    ss << file.rdbuf();
    std::string source = ss.str();

    m_source_code = sanitize_input(source);

    auto tokens = Tokenizer();

    if (debug)
    {
        for (const auto& t : tokens)
        {
            fmt::print("{}\n", t.as_string());
        }
    }

    return tokens;
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
            case '\n':
                handle_space();
                break;

            case ';':
                lex_comments();
                break;

            case '@':
                return lex_directives();
                break;

            case ',':
            case ':':
            case '[':
            case ']':
            case '(':
            case ')':
            case '{':
            case '}':
                return lex_separators();
                break;

            case '+':
            case '-':
            case '=':
                return lex_operators();
                break;

            case '#':
            case '$':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return lex_immediates();
                break;

            case 'r':
                if (std::isdigit(peek().value()))
                {
                    return lex_registers();
                }

            default:
                return lex_instructions();
                break;
        }
    }

    return Token(Kind::kind_t::__EOF, "EOF", "", m_line, m_index);
}

} // namespace Lexer
