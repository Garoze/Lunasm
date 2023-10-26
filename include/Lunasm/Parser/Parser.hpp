#pragma once

#include <algorithm>
#include <filesystem>
#include <memory>
#include <optional>
#include <unordered_map>
#include <variant>
#include <vector>

#include "Lexer/Lexer.hpp"
#include "Lexer/Token.hpp"

#include "Parser/ASL.hpp"
#include "Parser/Instruction.hpp"
#include "Parser/Label.hpp"
#include "Parser/Operand.hpp"

namespace Parser {

using Inst = std::variant<Instruction, Label>;

class Parser
{
public:
    using Inst = std::unique_ptr<Instruction>;

    Parser();

    void Parse();
    void parse_file(std::filesystem::path const&, bool = false);

private:
    void step();
    std::optional<Lexer::Token> look_ahead(std::size_t);

private:
    std::string_view parse_label();
    std::optional<Operand::value_t> parse_operand();

private:
    void nop_instruction();

    void mov_instruction();

    void shl_instruction();
    void shr_instruction();

    void and_instruction();
    void bor_instruction();
    void xor_instruction();
    void not_instruction();

    void psh_instruction();
    void pop_instruction();

    void inc_instruction();
    void dec_instruction();

    void add_instruction();
    void sub_instruction();
    void mul_instruction();
    void div_instruction();
    void mod_instruction();

    void cmp_instruction();

    void jmp_instruction();
    void jeq_instruction();
    void jne_instruction();

    void jsr_instruction();
    void ret_instruction();

    void hlt_instruction();

private:
    Lexer::Token expect(Lexer::Kind::kind_t);

    template <typename... Kinds>
    std::optional<Lexer::Token> expect_any(Kinds... kinds);

    template <typename T, typename... Args>
    void push_instruction(Args&&... args);

private:
    std::size_t m_index;
    std::vector<Lexer::Token> m_tokens;
    std::unique_ptr<Lexer::Lexer> m_lexer;
    std::vector<Inst> m_instructions;
};

} // namespace Parser
