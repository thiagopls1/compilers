#include <stdbool.h>
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
  HLT = 240  // Termina a execução
} NeanderInstruction;

int acc = 0;
int p_counter = 0;

bool is_flag_zero() { return acc == 0; }

bool is_flag_negative() { return acc < 0; }

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Erro: Nenhum arquivo foi passado como parâmetro!\n");
    printf("\tUso: ./build/ado1 <ARQUIVO>");
    return 1;
  }

  FILE *file_ptr = fopen(argv[1], "rb");

  if (file_ptr == NULL) {
    printf("Erro: não foi possível abrir o arquivo %s.\n", argv[1]);
    printf("\tVerifique se o arquivo existe.");
    return 1;
  }

  unsigned char byte;
  // fread sempre avança 1. Se não for 1, é EOF
  while (fread(&byte, 1, 1, file_ptr) == 1) {
    switch ((NeanderInstruction)byte) {
    case NOP:
      printf("NOP Detected.\n");
      continue;
    case STA:
      printf("STA Detected.\n");
      continue;
    case LDA:
      printf("LDA Detected.\n");
      continue;
    case ADD:
      printf("ADD Detected.\n");
      continue;
    case OR:
      printf("OR Detected.\n");
      continue;
    case AND:
      printf("AND Detected.\n");
      continue;
    case NOT:
      printf("NOT Detected.\n");
      continue;
    case JMP:
      printf("JMP Detected.\n");
      continue;
    case JN:
      printf("JN Detected.\n");
      continue;
    case JZ:
      printf("JZ Detected.\n");
      continue;
    case HLT:
      printf("HLT Detected.\n");
      break;
    default:
      printf("%u Detected.\n", byte);
      continue;
    }
    break;
  }

  fclose(file_ptr);
  return 0;
}
