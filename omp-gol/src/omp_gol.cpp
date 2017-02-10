#include <cstdlib>
#include <random>
#include <stdexcept>
#include <iostream>

#include "omp_gol.h"

omp_game_of_life::omp_game_of_life(const omp_game_of_life::grid_t& init_generation)
        : game_of_life(init_generation)
{ }

void omp_game_of_life::launch(std::size_t num_generations)
{
    bool is_changed = true;

    {
        for (std::size_t step_counter = 0;
             step_counter < num_generations && is_changed;
             ++step_counter, ++generation_counter_)
        {
            //display_grid(current_generation_);

            is_changed = false;

            // avoiding borders
            #pragma omp parallel for schedule (dynamic) reduction(||: is_changed)
            for (std::size_t i = 1; i < x_grid_size_ - 1; ++i)
            {
                for (std::size_t j = 1; j < y_grid_size_ - 1; ++j)
                {
                    std::size_t num_live = get_num_live_(i, j);

                    if (num_live == 2)
                    {
                        next_generation_[i][j] = current_generation_[i][j];
                    }
                    else if (num_live == 3)
                    {
                        next_generation_[i][j] = LIVE_;
                    }
                    else if (num_live < 2 || num_live > 3)
                    {
                        next_generation_[i][j] = DEAD_;
                    }

                    if (current_generation_[i][j] != next_generation_[i][j])
                    {
                        is_changed = true;
                    }
                }
            }

            std::swap(current_generation_, next_generation_);
        }
    }
}