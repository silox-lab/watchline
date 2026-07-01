#include "./strings.h"
#include <stdlib.h>
#include <string.h>

 
// Dynamic string implementation
String string_new(char *str) {
  int init_len = strlen(str);
  init_len++; // the null terminator isn't counted in 
  char *string_buffer = malloc(init_len * sizeof(char)); // FREE AFTER USE
  strcpy(string_buffer, str);
  String new_string = { .buffer = string_buffer, .capacity = init_len };
  return new_string;
}

// String concat implementation
// SRC IS INVALID AFTER CALL, FREE SRC IF HEAP ALLOCATED
void string_concat(String *dest, char *src) {
  int concat_len = strlen(src);
  
  if ((long unsigned int)dest->capacity < concat_len + strlen(dest->buffer) + 1) { // null terminator
    dest->buffer = realloc(dest->buffer, (concat_len + dest->capacity));
  }

  strcat(dest->buffer, src);
  dest->capacity = concat_len + dest->capacity;
  src = NULL;
}

// Dynamic string mutate implementaion
// SRC IS INVALID AFTER CALL, IF IT IS BUFFER FOR A STRING TYPE, FREE THE STRUCT AND MEMBERS
void string_mutate(String *dest, char *src) {
  
  if ((long unsigned int)dest->capacity < strlen(src) + 1) {
    dest->buffer = realloc(dest->buffer, strlen(src) + 1);
  }

  strcpy(dest->buffer, ""); // clean the buffer first
  strcpy(dest->buffer, src);
  dest->capacity = strlen(src) + 1;
  src = NULL;
}
