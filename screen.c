#include "screen.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Event event;

uint8_t SCREEN_Init(void)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    // Create window
    window = SDL_CreateWindow("CHIP-8", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_Quit();
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf("Renderer could not be created! SDL_Error: %s\n",
               SDL_GetError());
        return 1;
    }

    return 0;
}

void SCREEN_Quit(void)
{
    // Cleanup and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SCREEN_MainLoop(void)
{
    int quit = 0;
    // Main loop
    while (!quit)
    {
        // Handle events
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = 1;
                }
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        // Draw a rectangle
        SDL_Rect rect = { BLOCK_SIZE * 2, BLOCK_SIZE * 2, BLOCK_SIZE,
                          BLOCK_SIZE};
        SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x10, 0xFF);
        SDL_RenderFillRect(renderer, &rect);

        // Update screen
        SDL_RenderPresent(renderer);
    }
}

void SCREEN_UpdatePixel(const uint8_t x, const uint8_t y, bool value) {
    SDL_Rect rect = {x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
    if (value) {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x77, 0xFF, 0xFF);
    } else {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    }
    SDL_RenderFillRect(renderer, &rect);
}

