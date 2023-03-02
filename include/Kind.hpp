#pragma once

#include <string>

namespace Lunasm {

enum class L16TokenKind {
    NOP,

    LoadImmediate,
    LoadAddress,

    Register,

    END,
};

class Kind
{
public:
    Kind(L16TokenKind);

    std::string as_string() const;

private:
    L16TokenKind m_kind;
};

}  // namespace Lunasm
