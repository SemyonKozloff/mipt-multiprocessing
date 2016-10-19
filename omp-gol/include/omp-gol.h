#ifndef MIPT_MP_OMP_GOL_H
#define MIPT_MP_OMP_GOL_H

#include <stdbool.h>
#include <stddef.h>

#define ALIVE 1
#define DEAD 0

#define SWAP(x, y) do { typeof(x) _t = x; x = y; y = _t; } while (false)

void launch_game(size_t x_grid_size, size_t y_grid_size,
                 size_t num_generations);

void set_init_generation(size_t x_grid_size, size_t y_grid_size,
                         char **init_generation);
void display_grid(size_t x_grid_size, size_t y_grid_size, char **generation);

void copy_grid(size_t x_grid_size, size_t y_grid_size,
               char **to, char **from);
char **alloc_grid(size_t x_grid_size, size_t y_grid_size);
void free_grid(size_t x_grid_size, char **grid);

#endif //MIPT_MP_OMP_GOL_H
