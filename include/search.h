#ifndef IZ2_SEARCH_H
#define IZ2_SEARCH_H
// C headers
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct str_t {
  char* seq;
  int size;
} str_t;

typedef struct node_search_t {
  int first_el;
  int last_el;
  bool after_last_is_upper;
  str_t data;
} node_search_t;

str_t search(char* str, const int size);

bool readString(str_t* str, FILE* in);

node_search_t pidSearch(char* str, const int start_pos, const int end_pos);

bool isUpper(const char ch);

#endif  //IZ2_SEARCH_H
