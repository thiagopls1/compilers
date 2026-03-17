#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  OK = 0,
  INVALID_PARAM = 1,
  UNEXPECTED_TOKEN = 2,
} ExitCode;

typedef enum {
  OP = 1,
  NUM = 2,
} TokenType;

typedef struct {
  TokenType type;
  char *value;
} Token;

bool isoperator(char character) {
  return (char *)strchr("+-*/", character) != NULL;
}

bool isnumber(char character) {
  return (char *)strchr("1234567890", character) != NULL;
}

void handleDigit(char **str_pointer, Token *tokens, int tokens_count) {
  char *start_pointer = *str_pointer;
  int token_length = 0;

  while (isnumber(**str_pointer) && **str_pointer != '\0') {
    (*str_pointer)++;
    token_length++;
  }

  char *token_value = malloc(token_length + 1);

  for (int i = 0; i < token_length; i++) {
    token_value[i] = *start_pointer;
    start_pointer++;
  }
  token_value[token_length] = '\0';

  tokens[tokens_count] = (Token){
      .type = NUM,
      .value = token_value,
  };
}

void handleOperator(char **str_pointer, Token *tokens, int tokens_count) {
  char *token_value = (char *)malloc(sizeof(char));
  *token_value = **str_pointer;
  Token new_token = {
      .type = OP,
  };
  new_token.value = token_value;

  tokens[tokens_count] = new_token;
  (*str_pointer)++;
}

char *token_type_str(TokenType type) {
  switch (type) {
  case OP:
    return "OP";
  case NUM:
    return "NUM";
  default:
    return "DESC.";
  }
}

int main(int argc, char *argv[]) {
  ExitCode exit_code = OK;
  if (argc <= 1) {
    printf("Erro: necessário passar parâmetro!\n");
    exit_code = INVALID_PARAM;
    return exit_code;
  }

  char *str_pointer = argv[1];
  Token *tokens = malloc(strlen(argv[1]) * sizeof(Token));

  int tokens_count = 0;
  // Quem lida com o avanço dos ponteiros são as funções handle
  while (*str_pointer != '\0') {
    if (isnumber(*str_pointer)) {
      handleDigit(&str_pointer, tokens, tokens_count);
      tokens_count++;
      continue;
    }

    if (isoperator(*str_pointer)) {
      handleOperator(&str_pointer, tokens, tokens_count);
      tokens_count++;
      continue;
    }

    // Se não passou em nenhuma condição, então temos um token inesperado!
    break;
  }
  printf("str_pointer finalizou com: %c\n", *str_pointer);

  if (*str_pointer != '\0') {
    printf("Erro: token inesperado '%c'\n", *str_pointer);
    exit_code = 1;
  } else {
    for (int i = 0; i < tokens_count; i++) {
      // Se chegou no NULL, significa que acabou
      if (&tokens[i] == NULL) {
        break;
      }
      printf("Token %d: TIPO: %s, VALOR: %s\n", i,
             token_type_str(tokens[i].type), tokens[i].value);
    }
  }

  for (int i = 0; i < tokens_count; i++) {
    free(tokens[i].value);
  }

  free(tokens);

  return exit_code;
}
