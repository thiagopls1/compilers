#ifndef NEANDER_H
#define NEANDER_H
#define TAM_MEM 256 // Padrão do Neander

#include <stdint.h> //Necessário para utilizarmos variáveis com 8 bits

typedef struct {
  uint8_t mem[TAM_MEM];
  uint8_t original_mem[TAM_MEM];

  uint8_t acc;
  uint8_t pc;

  uint8_t flag_negative;
  uint8_t flag_zero;

  uint32_t accesses_mem;
  uint32_t executed_instructions;
} Neander;

// Definição das funções:
void neander_init(Neander *n);
void neander_execute_program(Neander *program);
void neander_print_state(Neander *n, int hex_mode);
void neander_print_mem(uint8_t *mem, int hex_mode);
int neander_load_program(Neander *n, const char *file);

#endif
