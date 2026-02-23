#include <stdio.h>

const int BIT_SIZE = 8;
const int MEM_MAX_POSITIONS = 256;

// X = Próxima posição após instrução
typedef enum {
  NOP = 0,   // Não faz nada (Pula instrução)
  STA = 16,  // Guarda o acumulador na pos. X
  LDA = 32,  // Guarda no acumulador o valor da pos. X
  ADD = 48,  // Soma no acumulador o valor da pos. X
  OR = 64,   // Compara o acumulador e o valor da pos. X
  AND = 80,  // Compara o acumulador e o valor da pos. X
  NOT = 96,  // Inverte os bits do acumulador
  JMP = 128, // Desvia a execução para a pos. X
  JN = 144,  // JMP caso seja negativo
  JZ = 160,  // JMP caso seja zero
  HTL = 240  // Termina a execução
} NeanderInstruction;

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
