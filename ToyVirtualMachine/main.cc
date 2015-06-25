// Toy Virtual Machine

///////////////////////////////////////////////////////////////////////////////
// Instruction set implementation:
//
//    PSH, 5;   pushes 5 to the stack
//    PSH, 6;   pushes 6 to the stack
//    ADD;      pop two values, add together, push result to stack
//    POP;      pop the addition result (11) from the stack, also print it
//    HLT;      stop the program
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

enum EInstructionSet
{
  PSH,
  POP,
  ADD,
  SUB,
  JMP,
  HLT
};

enum ERegisters
{
  A, B, C, D, E, F,

  IP, SP,
  NUM_OF_REGISTERS
};

class CToyVirtualMachine
{
  static const int STACK_SIZE = 256;

  bool running;          // loop mechanism
  int *base;
  int ip;                // instruction pointer
  int sp;                // stack pointer

  int stack[STACK_SIZE];

  int registers[NUM_OF_REGISTERS];

#define REG_IP registers[IP]
#define REG_SP registers[SP]

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
              push(fetch());
              break;
    }


    case POP:
    {
              int val_popped = pop();
              printf("popped %d\n", val_popped);
              break;
    }


    case ADD:
    {
              int a = pop();
              int b = pop();

              int result = b + a;

              push(result);

              break;
    }

    case SUB:
    {
              int a = pop();
              int b = pop();

              int result = b - a;

              push(result);

              break;
    }

    case JMP:
    {

              int d = pop();
              REG_IP = d;

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
    , ip(-1)
    , sp(-1)
  { }

  int GetInstructionPtr() const {
    return ip;
  }

  void Step() {
    eval(fetch());
  }

  void Run() {
    while (running) {
      Step();
    }
  }

  void Stop() {
    running = false;
  }

  void Reset(int * program) {
    base = program;
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
    PSH, 5, // 0
    PSH, 6, // 2 
    JMP, 6, // 4
    PSH, 1, // 6
    ADD,    // 8
    POP,    // 9
    HLT     // 10
  };

  CToyVirtualMachine vm;

  vm.Reset(program);
  vm.Run();

  return 0;
}
