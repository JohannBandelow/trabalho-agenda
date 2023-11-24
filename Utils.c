#include <stdio.h>

void print_line_separator() {
  printf("\n---------------------------------------------\n\n");
}

void limpa_buffer() {
  while (getchar() != '\n')
    ;
}
