#include "automaton.h"

std::vector<char> create_automata(size_t size)
{
    std::vector<char> out;
    for (size_t i = 0; i < size; i++)
        out.push_back(i == size / 2 ? 1 : 0);
    return out;
}

std::vector<char> next_generation(const std::vector<char> &original_generation, int rule)
{
    // generate rule set from decimal rule number (ex. 30 -> [0, 1, 1, 1, 1, 0, 0, 0])
    char rule_set[8];
    for (char &i: rule_set)
    {
        i = rule & 1 ? 1 : 0;
        rule >>= 1;
    }

    size_t size = original_generation.size();
    std::vector<char> out;
    out.resize(size);

    for (int i = 0; i < size; i++)
    {
        char left = original_generation[(i + size - 1) % size];
        char center = original_generation[i];
        char right = original_generation[(i + 1) % size];
        int rule_index = (left << 2) | (center << 1) | right;
        out[i] = rule_set[rule_index];
    }

    return out;
}

void
render_generation(SDL_Renderer *renderer, const std::vector<char> &generation, int y, int cell_size,
                  char r, char g, char b, char a)
{
    for (int i = 0; i < generation.size(); i++)
    {
        if (generation[i] == 1)
        {
            SDL_Rect cell = {i * cell_size, y, cell_size, cell_size};
            SDL_SetRenderDrawColor(renderer, r, g, b, a);
            SDL_RenderFillRect(renderer, &cell);
        }
    }
}
