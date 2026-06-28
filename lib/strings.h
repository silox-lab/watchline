#ifndef STRINGS
#define STRINGS

typedef struct {
  int capacity;
  char *buffer;
} String;

String string_new(char *str);
void string_concat(String *dest, char *src);
void string_mutate(String *dest, char *src);

#endif
