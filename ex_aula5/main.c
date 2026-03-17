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

bool isnumber(char character) {
  char *numbers = "1234567890";
  return (char *)strchr(numbers, character) != NULL;
}

void handleDigit(char **str_pointer, Token *tokens, int tokens_count) {
  char *start_pointer = *str_pointer;
  char *current_pointer = *str_pointer;
  int token_length = 0;
  while (isnumber(*current_pointer) && *current_pointer != '\0') {
    current_pointer = *str_pointer;
    token_length++;
    current_pointer++;
    *str_pointer = current_pointer;
  }

  char *token_value = malloc(token_length * sizeof(char));

  for (int i = 0; i < token_length; i++) {
    token_value[i] = *start_pointer;
    start_pointer++;
  }

  Token new_token = {.type = NUM};
  new_token.value = token_value;
  tokens[tokens_count] = new_token;
}

void handleOperator(char *str_pointer, Token *tokens, int tokens_count) {
  char *token_value = (char *)malloc(sizeof(char));
  *token_value = *str_pointer;
  Token new_token = {
      .type = OP,
  };
  new_token.value = token_value;

  tokens[tokens_count] = new_token;
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Erro: necessário passar parâmetro!\n");
    return 1;
  }

  char *str_pointer = argv[1];
  Token *tokens = malloc(strlen(argv[1]) * sizeof(Token));

  int tokens_count = 0;
  while (*str_pointer != '\0') {
    if (isnumber(*str_pointer)) {
      handleDigit(&str_pointer, tokens, tokens_count);
      tokens_count++;
    }

    if (isoperator(*str_pointer)) {
      handleOperator(str_pointer, tokens, tokens_count);
      tokens_count++;
    }

    str_pointer++;
  }

  for (int i = 0; i < tokens_count; i++) {
    // Se chegou no NULL, significa que acabou
    if (&tokens[i] == NULL) {
      break;
    }
    printf("Token %d: TIPO: %d, VALOR: %s\n", i, tokens[i].type,
           tokens[i].value);
  }
  return 0;
}
