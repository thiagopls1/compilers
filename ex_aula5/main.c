#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

void handleDigit() {}

void handleOperator(char *str_pointer, Token *tokens, int tokens_count) {
  char *token_value = (char *)malloc(sizeof(char));
  *token_value = *str_pointer;
  Token new_token = {
      .type = OP,
  };
  new_token.value = token_value;

  tokens[tokens_count] = new_token;
  str_pointer++;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Erro: necessário passar parâmetro!\n");
    return 1;
  }

  char *str_pointer = argv[1];
  Token tokens[strlen(str_pointer)];

  int tokens_count = 0;
  while (*str_pointer != '\0') {
    if (isdigit(*str_pointer)) {
      printf("Dígito detectado!\n");
      // tokens_count++;
    }

    if (isoperator(*str_pointer)) {
      printf("Operador detectado!\n");
      handleOperator(str_pointer, tokens, tokens_count);
      tokens_count++;
    }

    str_pointer++;
  }

  for (int i = 0; i < tokens_count; i++) {
    printf("%s\n", tokens[i].value);
  }

  printf("\n");
  return 0;
}
