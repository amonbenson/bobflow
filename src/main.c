#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "bobflow/flow.h"
#include "uthash/utlist.h"


int main(int argc, char *argv[]) {
    (void)(argc);
    (void)(argv);

    bflow_t *bf = bflow_new("test");

    bflow_add_node(bf, "n1", -1, -0.5);
    bflow_add_node(bf, "n2", 1, 0.5);

    bool quit = false;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Bobflow",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    while (!quit) {
        SDL_Event event;

        // handle events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        // update all nodes
        bflow_update(bf, 0.01);

        // start rendering
        SDL_SetRenderDrawColor(renderer, 35, 40, 45, 255);
        SDL_RenderClear(renderer);

        int wx, wy;
        SDL_GetWindowSize(window, &wx, &wy);

        // draw all nodes
        const int node_size = 10;
        const int node_scale = 100;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        bf_node_t *node;
        LL_FOREACH(bf->nodes, node) {
            SDL_Rect rect = {
                .x = node->x * node_scale - node_size / 2 + wx / 2,
                .y = node->y * node_scale - node_size / 2 + wy / 2,
                .w = node_size,
                .h = node_size
            };
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    bflow_free(bf);

    return 0;
}
