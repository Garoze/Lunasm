namespace Luna16 {

enum class Opcode
{
    Nop,

    LoadImmediate,
    LoadAddress,
    LoadRegister,

    StoreImmediate,
    StoreAddress,
    StoreRegister,

    ShiftLeft,
    ShiftRight,

    And,
    Or,
    Not,
    Xor,

    PushImmediate,
    PushAddress,
    PushRegister,
    Pop,

    Increment,
    Decrement,

    AddImmediate,
    AddAddress,
    AddRegister,

    SubImmediate,
    SubAddress,
    SubRegister,

    MulImmediate,
    MulAddress,
    MulRegister,

    DivImmediate,
    DivAddress,
    DivRegister,

    ModImmediate,
    ModAddress,
    ModRegister,

    CompareImmediate,
    CompareAddress,
    CompareRegister,

    Jump,
    JumpIfEquals,
    JumpIfNotEquals,

    Subroutine,
    Return,

    Halt,

    Label,
};

} // namespace Luna16
