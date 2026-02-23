#include <stdio.h>

const int BIT_SIZE = 8;
const int MEM_MAX_POSITIONS = 256;

typedef enum {
  NOP = 0,
  STA = 16,
  LDA = 32,
  ADD = 48,
  OR = 64,
  AND = 80,
  NOT = 96,
  JMP = 128,
  JN = 144,
  JZ = 160,
  HTL = 240
} NianderInstruction;

int main() {
  printf("Hello, world!");
  return 0;
}
