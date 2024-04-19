#ifndef ELEMENTARY_CELLULAR_AUTOMATA_AUTOMATON_H
#define ELEMENTARY_CELLULAR_AUTOMATA_AUTOMATON_H

#include <vector>
#include <SDL.h>

std::vector<char> create_automata(size_t size);

std::vector<char> next_generation(const std::vector<char> &original_generation, int rule);

void render_generation(SDL_Renderer *renderer, const std::vector<char>& generation, int y, int cell_size,
                       char r, char g, char b, char a);

#endif //ELEMENTARY_CELLULAR_AUTOMATA_AUTOMATON_H
