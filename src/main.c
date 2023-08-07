#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "bobflow/flow.h"
#include "uthash/utlist.h"


static int test_cb(void *context, void *data) {
    (void)(context);
    bf_prop_t *x = data;

    printf("cb x = %f\n", bf_prop_get_value(x));
    return 0;
}

int main(int argc, char *argv[]) {
    (void)(argc);
    (void)(argv);

    bflow_t *bf = bflow_new("test");

    bflow_add_node(bf, "node1");

    bf_event_add_handler(bf->nodes->x->on_change, test_cb, NULL);

    bool quit = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Bobflow",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        640, 480,
        SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    while (!quit) {
        SDL_Delay(10);
        SDL_PollEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
        }

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
                .x = node->x->value * node_scale - node_size / 2 + wx / 2,
                .y = node->y->value * node_scale - node_size / 2 + wy / 2,
                .w = node_size,
                .h = node_size
            };
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    bflow_free(bf);

    return 0;
}
