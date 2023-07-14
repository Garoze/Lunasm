#include <variant>

#include "fmt/core.h"
#include "fmt/ranges.h"

#include "Parser/ASLL.hpp"
#include "Parser/Instruction.hpp"

namespace Lunasm {

ASLL::ASLL()
    : m_index(0)
{}

ASLL::ASLL(const std::vector<Inst>& instructions)
    : m_index(0)
    , m_instructions(instructions)
{}

void ASLL::resolve_labels()
{
    auto visitor = [&](auto& arg) {
        using T = std::remove_reference_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, Instruction>)
        {
            m_index += arg.size();
        }
        else if constexpr (std::is_same_v<T, Label>)
        {
            auto label = arg.label();
            if (m_labels.count(label) == 0)
            {
                m_labels[label] = m_index;
            }

            arg.set_address(m_index);
        }
    };

    for (auto& inst : m_instructions)
    {
        std::visit(visitor, inst);
    }
}

void ASLL::generate(std::string const& path)
{
    resolve_labels();

    auto visitor = [&](auto& arg) {
        using T = std::remove_reference_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, Instruction>)
        {
            arg.eval(m_output);
            arg.print();
        }
        else if constexpr (std::is_same_v<T, Label>)
        {
            auto label = arg.label();
            if (m_labels.count(label) != 0)
            {
                arg.print();
                arg.eval(m_output);
            }
        }
    };

    for (auto& i : m_instructions)
    {
        std::visit(visitor, i);
    }

    fmt::print("{::02x} \n", m_output);
}

void ASLL::handle_instructions(const std::vector<Inst>& instructions)
{
    m_instructions = instructions;
    generate("teste");
}

} // namespace Lunasm
