///////////////////////////////////////////////////////////////////////////////
// Toy Virtual Machine
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

enum EInstructionSet
{
  PSH,  // value          value to stack
  POP,  // REG            from stack to register
  MOV,  // REG, value     
  ADD,  // REG, value     
  SUB,  // REG, value     
  NOP,  // --             dud
  INT,  // --             trigger a breakpoint
  HLT   // end
};

enum ERegisters
{
  // General Purpose

  EAX, // Accumulator
  ECX, // Counter
  EDX, // Data
  EBX, // Base

  // Pointer Registers

  ESP, // Stack
  EBP, // Base

  // Stack Registers

  ESI, // Source Index
  EDI, // Destination Index

  EIP, // Instruction Pointer

  NUM_OF_REGISTERS
};

class CToyVirtualMachine
{
  static const int STACK_SIZE = 256;

  bool running;          // loop mechanism
  int *base;
  int length;
  int ip;                // instruction pointer
  int sp;                // stack pointer

  int stack[STACK_SIZE];

  int registers[NUM_OF_REGISTERS];

#define REG_IP registers[EIP]
#define REG_SP registers[ESP]

  int fetch() {
    int instr = base[REG_IP];
    ++REG_IP;
    return instr;
  }

  void push(int val) {
    ++REG_SP;
    stack[REG_SP] = val;
  }

  int pop() {
    int val = stack[REG_SP];
    --REG_SP;
    return val;
  }

  void eval(int instr) {
    switch (instr)
    {
    case HLT:
    {
              Stop();

              break;
    }

    case PSH:
    {
              int val = fetch();

              push(val);

              break;
    }


    case POP:
    {
              int reg = fetch();
              int val = pop();

              registers[reg] = val;

              break;
    }

    case MOV:
    {
              int reg = fetch();
              int val = fetch();

              registers[reg] = val;

              break;
    }

    case ADD:
    {
              int reg = fetch();
              int val = fetch();

              registers[reg] += val;

              break;
    }

    case SUB:
    {
              int reg = fetch();
              int val = fetch();

              registers[reg] -= val;

              break;
    }

    case INT:
    {
              break;
    }

    case NOP:
    {
              break;
    }

    default:
    {
             printf("Unimplemented opcode: %i\n", instr);
             break;
    }
    }
  }

public:
  CToyVirtualMachine()
    : running(false)
    , base(nullptr)
    , length(0)
    , ip(-1)
    , sp(-1)
  { }

  int GetInstructionPtr() const {
    return ip;
  }

  void Step() {
    eval(fetch());

    // sanity check
    if (REG_IP > length) {
      running = false;
    }
  }

  void Run() {
    while (running) {
      Step();
    }
  }

  void Stop() {
    running = false;
  }

  void Reset(int * program, const int size) {
    base = program;
    length = size;
    ip = -1;
    sp = -1;
    // also clear stack?
    // also clear registers?
    running = true;
  }
};

int main()

{
  int program[] = {
    MOV, EAX, 10,
    NOP,
    INT,

    HLT
  };

  CToyVirtualMachine vm;

  vm.Reset(program, sizeof(program)/sizeof(program[0]));
  vm.Run();

  return 0;
}
