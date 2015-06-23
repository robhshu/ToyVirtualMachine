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
  HLT
};

enum ERegisters
{
  A, B, C, D, E, F,

  NUM_OF_REGISTERS
};

class CToyVirtualMachine
{
  static const int STACK_SIZE = 256;

  bool running;       // loop mechanism
  int const * ip;             // instruction pointer
  int  sp;             // stack pointer
  int stack[STACK_SIZE];

  int registers[NUM_OF_REGISTERS];

  int fetch() {
    return *ip;
  }

  void eval(int instr) {
    switch (instr) {
    case HLT: {
      running = false;
    }
    break;

    case PSH: {
      sp++;
      stack[sp] = *ip;
      ++ip;
    }
    break;

    case POP: {
      int val_popped = stack[sp--];
      printf("popped %d\n", val_popped);
    }
    break;

    case ADD: {
      // first we pop the stack and store it as a
      int a = stack[sp--];

      // then we pop the top of the stack and store it as b
      int b = stack[sp--];

      // we then add the result and push it to the stack
      int result = b + a;
      sp++; // increment stack pointer **before**
      stack[sp] = result; // set the value to the top of the stack

      // all done!
      break;
    }

    default:
      printf("Unimplemented opcode: %i\n", instr);
      break;
    }
  }

public:
  CToyVirtualMachine()
    : running(false)
    , ip(nullptr)
    , sp(-1)
  { }

  void Step() {
    eval(fetch());
    ++ip; // increment the ip every iteration
  }
  
  void Run() {
    while (running) {
      Step();
    }
  }

  void Reset(int const * program) {
    ip = program;
    sp = -1;
    // also clear stack?
    // also clear registers?
    running = true;
  }
};

int main()
{
  const int program[] = {
    PSH, 5,
    PSH, 6,
    ADD,
    POP,
    HLT
  };

  CToyVirtualMachine vm;

  vm.Reset(program);

  vm.Run();

  return 0;
}
