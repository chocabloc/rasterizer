#include "window.h"
#include <SDL2/SDL.h>
#include <stdio.h>

#define TARGET_FPS 1000
#define MILLIS_PER_FRAME (1000 / TARGET_FPS)

static SDL_Window* window;
static SDL_Renderer* renderer;

static uint32_t ticks;

// initialize windowing
int win_init(void)
{
    // initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
        return -1;
    }

    // create window
    window = SDL_CreateWindow("3D Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "could not create window: %s\n", SDL_GetError());
        return -1;
    }

    // get the surface and renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "could not create renderer: %s\n", SDL_GetError());
        return -1;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    return 0;
}

// clear screen
void win_clear()
{
    ticks = SDL_GetTicks();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 10);
}

// main loop: handles events and timing
void win_mainloop()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            exit(0);
        }
    }

    SDL_RenderPresent(renderer);
    uint32_t delta = SDL_GetTicks() - ticks;
    //printf("%d\n", delta);
    if (delta < MILLIS_PER_FRAME)
        SDL_Delay(MILLIS_PER_FRAME - delta);
}

// put a pixel
void win_put(int x, int y)
{
    if(x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
        SDL_RenderDrawPoint(renderer, x, y);
}