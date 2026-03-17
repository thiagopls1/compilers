#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef enum {
  OP = 1,
  NUM = 2,
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

bool isoperator(char character) {
  char *operators = "+-*/";
  return (char *)strchr(operators, character) != NULL;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Erro: necessário passar parâmetro!\n");
    return 1;
  }

  char *str_pointer = argv[1];

  // Iterate until end of string
  while (*str_pointer != '\0') {
    if (isdigit(*str_pointer))
      printf("Dígito detectado!\n");

    if (isoperator(*str_pointer))
      printf("Operador detectado!\n");

    str_pointer++;
  }

  printf("\n");
  return 0;
}
