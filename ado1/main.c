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

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Erro: Nenhum arquivo foi passado como parâmetro!\n");
    printf("\tUso: ./build/ado1 <ARQUIVO>");
    return 1;
  }

  FILE *file_ptr = fopen(argv[1], "r");

  if (file_ptr == NULL) {
    printf("Erro: não foi possível abrir o arquivo %s.\n", argv[1]);
    printf("\tVerifique se o arquivo existe.");
    return 1;
  }

  printf("Hello, world!");
  return 0;
}
