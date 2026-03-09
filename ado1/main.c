#include "neander.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) { // Checa se recebeu o arquivo do programa
    printf("Sintaxe incorreta. Deve-se seguir o modelo: %s programa.mem [--hex "
           "| --dec]\n",
           argv[0]);
    return 1;
  }

  int hex_mode = 0;

  if (argc >= 3 &&
      strcmp(argv[2], "--hex") == 0) { // Ativa o modo hexadecimal se forem = 0
    hex_mode = 1;
  }

  Neander n;
  neander_init(&n);

  if (!neander_load_program(&n, argv[1])) {
    printf("Erro ao carregar o arquivo\n");
    return 1;
  }

  printf("Memória antes: \n");
  neander_print_mem(n.original_mem, hex_mode);

  printf("Memória depois: \n");
  neander_print_mem(n.mem, hex_mode);

  neander_print_state(&n, hex_mode);

  return 0;
}
