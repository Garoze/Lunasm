#pragma once

#include <cstdint>

namespace Lunasm {

class Node
{
public:
    virtual void print() = 0;
    virtual std::uint8_t eval() = 0;
    virtual std::size_t size() const = 0;

private:
    std::uint8_t m_output;
    std::size_t m_size;
};

}  // namespace Lunasm
