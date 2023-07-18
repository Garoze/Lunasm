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

#include "Parser/ASLL.hpp"
#include "Parser/Instruction.hpp"
#include "Parser/Label.hpp"

namespace Lunasm {

using Inst = std::variant<Instruction, Label>;

class Parser
{
public:
    Parser();

    void Parse();
    void parse_file(std::filesystem::path const&, bool = false);

    void debug_instruction() const;

private:
    void step();
    std::optional<Token> look_ahead(std::size_t);

private:
    std::uint8_t parse_register();
    std::uint16_t parse_immediate();
    std::string_view parse_label();

    Operand parse_address();
    void handle_address(Opcode, std::size_t, Operand, std::optional<Operand>);

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
    Token expect(TokenKind);

    template <typename... Kinds>
    std::optional<Token> expect_any(Kinds... kinds);

private:
    std::size_t m_index;
    std::vector<Token> m_tokens;
    std::unique_ptr<ASLL> m_asll;
    std::unique_ptr<Lexer> m_lexer;
    std::vector<Inst> m_instructions;
};

} // namespace Lunasm
