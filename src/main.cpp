#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <SDL.h>
#include "automaton.h"

int main(int, char *[])
{
    int window_width = 1280;
    int window_height = 720;

    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return -1;
    SDL_Window *window = SDL_CreateWindow(
            "Elementary Cellular Automata",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            window_width, window_height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    if (!window)
    {
        SDL_Quit();
        return -1;
    }
    SDL_Renderer *p_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!p_renderer)
    {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO();
    ImGui_ImplSDL2_InitForSDLRenderer(window, p_renderer);
    ImGui_ImplSDLRenderer2_Init(p_renderer);

    std::vector<std::vector<char>> automaton;
    int row_count = 0;

    // main loop
    bool isRunning = true;
    while (isRunning)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                isRunning = false;
            else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                window_width = event.window.data1;
                window_height = event.window.data2;
                row_count = 0;
            }
        }

        // start ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // draw ImGui elements
        ImGui::Begin("Options", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

        static int rule = 30;
        ImGui::Text("Rule (0-255):");
        ImGui::SameLine();
        ImGui::PushItemWidth(84);
        if (ImGui::InputInt("##rule", &rule))
        {
            {
                if (rule < 0)
                    rule = 0;
                else if (rule > 255)
                    rule = 255;
                row_count = 0;
            }}
        ImGui::PopItemWidth();

        static int cell_size = 20;
        ImGui::Text("Cell size:");
        ImGui::SameLine();
        if (ImGui::SliderInt("##cell_size", &cell_size, 1, 40))
            row_count = 0;

        static ImVec4 background_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImGui::Text("Background color:");
        ImGui::SameLine();
        ImGui::ColorEdit3("##background_color", (float *) &background_color);

        static ImVec4 cell_color = ImVec4(0, 0, 0, 1);
        ImGui::Text("Cell color:");
        ImGui::SameLine();
        ImGui::ColorEdit4("##cell_color", (float *) &cell_color);

        ImGui::End();

        if (row_count == 0)
            automaton.clear();
        if (row_count < (window_height / cell_size))
            automaton.push_back(row_count == 0
                                ? create_automata(window_width / cell_size)
                                : next_generation(automaton[automaton.size() - 1], rule));

        // render
        ImGui::Render();
        SDL_SetRenderDrawColor(p_renderer, (char) (background_color.x * 255), (char) (background_color.y * 255),
                               (char) (background_color.z * 255), (char) (background_color.w * 255));
        SDL_RenderClear(p_renderer);
        for (int i = 0; i < automaton.size(); i++)
            render_generation(p_renderer, automaton[i], i * cell_size, cell_size,
                              (char) (cell_color.x * 255), (char) (cell_color.y * 255),
                              (char) (cell_color.z * 255), (char) (cell_color.w * 255));
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(p_renderer);
        if (row_count < (window_height / cell_size))
            row_count++;
    }

    // cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
