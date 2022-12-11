#include "utils.h"

char *strtokm(char *input, char *delimiter, char **saveptr) {
  char *string;
  if (input != NULL)
    string = input;
  else
    string = *saveptr;

  if (string == NULL)
    return string;

  char *end = strstr(string, delimiter);
  if (end == NULL) {
    char *tok = string;
    *saveptr = NULL;
    return tok;
  }

  char *tok = string;

  *end = '\0';
  *saveptr = end + strlen(delimiter);
  return tok;
}

void map_delim(char *str, char *delim, void (*map)(char *, void *),
               void *data) {
  int index = 0;
  char *saveptr;
  char *token = strtokm(str, delim, &saveptr);
  while (token != NULL) {
    if (map != NULL) {
      map(token, data);
    }
    token = strtokm(NULL, delim, &saveptr);
    index++;
  }
}

void str_split(char *str, char *delim, char *out[]) {
  int index = 0;
  char *saveptr;
  char *token = strtokm(str, delim, &saveptr);
  while (token != NULL) {
    out[index] = token;
    token = strtokm(NULL, delim, &saveptr);
    index++;
  }
}