#include "Parser/LoadImmediate.hpp"

namespace Lunasm {

LoadImmediate::LoadImmediate(std::size_t size, std::uint8_t output, Register r, Immediate i)
    : m_size(size)
    , m_output(output)
    , m_register(r)
    , m_immediate(i)
{}

void LoadImmediate::print() {}

std::uint8_t LoadImmediate::eval()
{
    return m_output;
}

std::size_t LoadImmediate::size() const
{
    return m_size;
}

}  // namespace Lunasm
