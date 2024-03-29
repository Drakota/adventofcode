#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strtokm(char *input, char *delim, char **saveptr);
void map_delim(char *str, char *delim, void (*map)(char *, int, void *),
               void *data);
void str_split(char *str, char *delim, char *out[]);

#endif