#include <stdlib.h>
#include <stdio.h>
#include "c8_cpu.h"

C8_BYTE*
c8_load_binary(char* file_name, int* size_out) {
  FILE* bin_file = fopen(file_name, "r");
  if (!bin_file) {
    fprintf(stderr, "Unable to open %s\n", file_name);
    exit(1);
  }
  fseek(bin_file, 0, SEEK_END);
  long file_size = ftell(bin_file);
  fseek(bin_file, 0, SEEK_SET);

  C8_BYTE* buffer = malloc(sizeof(C8_BYTE) * file_size);
  *size_out = (int) fread(buffer, 1, file_size, bin_file);
  fclose(bin_file);
  return buffer;
}

void 
c8_unload_binary(C8_BYTE* binary) {
  if (binary) {
    free(binary);
  }
}

int
main(int argc, char **argv) {

  if (argc <= 1) {
    fprintf(stdout, "Usage: %s <chip8 rom>\n", argv[0]);
    exit(1);
  }

  char* file_name = argv[1];
  int file_size;
  C8_BYTE* c8_rom = c8_load_binary(file_name, &file_size);

  fprintf(stdout, "Loaded %s - %d bytes\n", file_name, file_size);

  struct c8_cpu* cpu = c8_cpu_init();
  c8_cpu_load_rom(c8_rom, file_size);
  c8_unload_binary(c8_rom);

  int running = 1;

  //TODO(bryan) initialize graphics here
  while (running) {
    c8_cpu_cycle(cpu);

    if (c8_cpu_draw_flag_set(cpu)) {
      //TODO(bryan) render to screen
    }

    c8_cpu_update_key_state(cpu);
  }


  c8_cpu_destroy(cpu);
  return 0;
}
