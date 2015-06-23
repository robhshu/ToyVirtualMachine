// Toy Virtual Machine

///////////////////////////////////////////////////////////////////////////////
// Instruction set:
//    PSH 5; pushes 5 to the stack
//    PSH 10; pushes 10 to the stack
//    ADD; pops two values on top of the stack, adds them pushes to stack
//    POP; pops the value on the stack, will also print it for debugging
//    SET A 0; sets register A to 0
//    HLT; stop the program
///////////////////////////////////////////////////////////////////////////////

enum InstructionSet
{
  PSH,
  ADD,
  POP,
  SET,
  HLT
};

enum Registers
{
  A, B, C, D, E, F,

  NUM_OF_REGISTERS
};

bool running = true;
int ip = 0;
int sp = -1;
int stack[256]; // use a define or something here preferably
int registers[NUM_OF_REGISTERS];

const int program[] = {
  PSH, 5,
  PSH, 6,
  ADD,
  POP,
  HLT
};

int fetch() {
  return program[ip];
}

#include <stdio.h>

void eval(int instr) {
  switch (instr) {
    case HLT: {
      running = false;
    }
    break;

    case PSH: {
      sp++;
      stack[sp] = program[++ip];
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

int main()
{
  while (running) {
    eval(fetch());
    ip++; // increment the ip every iteration
  }

  return 0;
}
