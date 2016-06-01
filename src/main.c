#include <stdlib.h>
#include <stdio.h>

int
main(int argc, char **argv) {

  if (argc <= 1) {
    fprintf(stdout, "Usage: %s <chip8 rom>\n", argv[0]);
    exit(1);
  }

  char* file_name = argv[1];
  fprintf(stdout, "%s\n", file_name);

  return 0;
}
