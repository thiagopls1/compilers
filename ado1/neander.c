#include "neander.h"
#include <stdio.h>
#include <string.h>

static uint8_t read_mem(Neander *n, uint8_t posMem) {
  n->accesses_mem++;
  return n->mem[posMem];
}

static void write_mem(Neander *n, uint8_t posMem, uint8_t val) {
  n->accesses_mem++;
  n->mem[posMem] = val;
}

static void update_flags(Neander *n) {
  n->flag_zero = (n->acc == 0); // Verifica se o acumulador é igual a 0
  n->flag_negative =
      (n->acc & 0x80) != 0; // Faz uma comparação bit a bit com o MSB(0x80)
}

void neander_init(Neander *n) {
  // Zeramos a memória para limpar a struct
  memset(n->mem, 0, TAM_MEM);
  memset(n->original_mem, 0, TAM_MEM);

  n->acc = 0;
  n->pc = 0;
  n->flag_negative = 0;
  n->flag_zero = 0;
  n->accesses_mem = 0;
  n->executed_instructions = 0;
}

int neander_load_program(Neander *n, const char *file) {
  FILE *f = fopen(file, "rb");
  if (!f) {
    printf("Erro ao abrir o arquivo");
    return 0;
  }

  fread(n->mem, sizeof(uint8_t), TAM_MEM, f);
  fclose(f);

  memcpy(n->original_mem, n->mem, TAM_MEM);

  return 1;
}

void neander_execute_program(Neander *n) {
  int running = 1;

  while (running) {
    uint8_t instrucao = read_mem(
        n, n->pc++); // Passa o computador com o PC atual e avança o mesmo em 1
    n->executed_instructions++;

    uint8_t address;
    switch (instrucao) { // Baseado nos mnemônicos do Neander
    case 0:              // NOP
      break;
    case 32: // LDA
      address = read_mem(n, n->pc++);
      n->acc = read_mem(n, address);
      update_flags(n);
      break;
    case 16: // STA
      address = read_mem(n, n->pc++);
      write_mem(n, address, n->acc);
      break;
    case 48: // ADD
      address = read_mem(n, n->pc++);
      n->acc = read_mem(n, address);
      update_flags(n);
      break;
    case 64: // OR
      address = read_mem(n, n->pc++);
      n->acc |= read_mem(n, address);
      update_flags(n);
      break;
    case 80: // AND
      address = read_mem(n, n->pc++);
      n->acc &= read_mem(n, address);
      update_flags(n);
      break;
    case 96:            // NOT
      n->acc = ~n->acc; //"~": bitwise operator para negar os bits
      update_flags(n);
      break;
    case 128: // JMP(sem condições)
      address = read_mem(n, n->pc++);
      n->pc = address;
      break;
    case 144: // JN(condicional negativo)
      address = read_mem(n, n->pc++);
      if (n->flag_negative) {
        n->pc = address;
      }
      break;
    case 160: // JZ(condicional zero)
      address = read_mem(n, n->pc++);
      if (n->flag_zero) {
        n->pc = address;
      }
      break;
    case 240: // HLT
      running = 0;
      break;
    default:
      printf("Instrução não reconhecida: %u", instrucao); //"%u": unsigned
      running = 0;
    }
  }
}

void neander_print_state(Neander *n, int hex_mode) {
  printf("Estado final da máquina:\n");

  if (hex_mode) {
    printf("Acumulador: 0x%02X\n", n->acc);
    printf("Program counter: 0x%02X\n", n->pc);
  } else {
    printf("Acumulador: %d\n", (int8_t)n->acc);
    printf("Program counter: %d\n", n->pc);
  }

  printf("Flag negativa: %u\n", n->flag_negative);
  printf("Flag zero: %u\n", n->flag_zero);
  printf("Número de acessos a memória: %u\n", n->accesses_mem);
  printf("Numero de instruções executadas: %u\n", n->executed_instructions);
}

void neander_print_mem(uint8_t *mem, int hex_mode) {
  for (int i = 0; i < TAM_MEM; i++) {

    if (i % 16 == 0) // Mostra o endereço inicial do bloco de memória
      printf("\n%03d: ", i);

    if (hex_mode)
      printf("%02X ", mem[i]);
    else
      printf("%03d ", mem[i]);
  }
  printf("\n");
}
