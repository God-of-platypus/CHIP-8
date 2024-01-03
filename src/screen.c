#include "screen.h"

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *screen = NULL;
static SDL_Event event;
static uint8_t keyboard[16];

static void SCREEN_Draw(CHIP8 *chip8)
{
    uint32_t pixels[64 * 32] = { 0 };
    for (uint8_t x = 0; x < DISPLAY_WIDTH; x++)
    {
        for (uint8_t y = 0; y < DISPLAY_HEIGTH; y++)
        {
            if (chip8->display[y][x])
            {
                pixels[(x) + ((y)*64)] = UINT32_MAX;
            }
        }
    }
    SDL_UpdateTexture(screen, NULL, pixels, 64 * sizeof(uint32_t));

    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    position.w = DISPLAY_WIDTH;
    position.h = DISPLAY_HEIGTH;
    SDL_RenderCopy(renderer, screen, NULL, &position);
    SDL_RenderPresent(renderer);
}

uint8_t SCREEN_Init(void)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    // Create window
    window = SDL_CreateWindow(("CHIP-8: %s", param.file),
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        SDL_Quit();
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf("Renderer could not be created! SDL_Error: %s\n",
               SDL_GetError());
        return 1;
    }
    SDL_RenderSetLogicalSize(renderer, DISPLAY_WIDTH, DISPLAY_HEIGTH);
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_STREAMING, DISPLAY_WIDTH,
                               DISPLAY_HEIGTH);

    return 0;
}

void SCREEN_Quit(void)
{
    // Cleanup and quit
    SDL_DestroyTexture(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SCREEN_MainLoop(CHIP8 *chip8)
{
    int quit = 0;
    // Main loop
    static const uint16_t UPDATE_INTERVAL_MS = 1000 / 60;
    uint32_t lastUpdate = SDL_GetTicks();
    uint32_t currentUpdate = 0;
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
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_X:
                    keyboard[0] = 1;
                    break;
                case SDL_SCANCODE_1:
                    keyboard[1] = 1;
                    break;
                case SDL_SCANCODE_2:
                    keyboard[2] = 1;
                    break;
                case SDL_SCANCODE_3:
                    keyboard[3] = 1;
                    break;
                case SDL_SCANCODE_Q:
                    keyboard[4] = 1;
                    break;
                case SDL_SCANCODE_W:
                    keyboard[5] = 1;
                    break;
                case SDL_SCANCODE_E:
                    keyboard[6] = 1;
                    break;
                case SDL_SCANCODE_A:
                    keyboard[7] = 1;
                    break;
                case SDL_SCANCODE_S:
                    keyboard[8] = 1;
                    break;
                case SDL_SCANCODE_D:
                    keyboard[9] = 1;
                    break;
                case SDL_SCANCODE_Z:
                    keyboard[10] = 1;
                    break;
                case SDL_SCANCODE_C:
                    keyboard[11] = 1;
                    break;
                case SDL_SCANCODE_4:
                    keyboard[12] = 1;
                    break;
                case SDL_SCANCODE_R:
                    keyboard[13] = 1;
                    break;
                case SDL_SCANCODE_F:
                    keyboard[14] = 1;
                    break;
                case SDL_SCANCODE_V:
                    keyboard[15] = 1;
                    break;
                }
            }
            else if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_X:
                    keyboard[0] = 0;
                    break;
                case SDL_SCANCODE_1:
                    keyboard[1] = 0;
                    break;
                case SDL_SCANCODE_2:
                    keyboard[2] = 0;
                    break;
                case SDL_SCANCODE_3:
                    keyboard[3] = 0;
                    break;
                case SDL_SCANCODE_Q:
                    keyboard[4] = 0;
                    break;
                case SDL_SCANCODE_W:
                    keyboard[5] = 0;
                    break;
                case SDL_SCANCODE_E:
                    keyboard[6] = 0;
                    break;
                case SDL_SCANCODE_A:
                    keyboard[7] = 0;
                    break;
                case SDL_SCANCODE_S:
                    keyboard[8] = 0;
                    break;
                case SDL_SCANCODE_D:
                    keyboard[9] = 0;
                    break;
                case SDL_SCANCODE_Z:
                    keyboard[10] = 0;
                    break;
                case SDL_SCANCODE_C:
                    keyboard[11] = 0;
                    break;
                case SDL_SCANCODE_4:
                    keyboard[12] = 0;
                    break;
                case SDL_SCANCODE_R:
                    keyboard[13] = 0;
                    break;
                case SDL_SCANCODE_F:
                    keyboard[14] = 0;
                    break;
                case SDL_SCANCODE_V:
                    keyboard[15] = 0;
                    break;
                }
            }
        }

        // Clear the screenV
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);

        uint16_t opcode = CHIP8_fetch(chip8);

        printf("Current opcode: %X\n", opcode);
        printf("Current I: %X\n", chip8->I);
        printf("Current PC: %X\n", chip8->pc);

        CHIP8_exec(chip8, opcode);
        if (draw)
        {
            draw = false;
            SCREEN_Draw(chip8);
        }

        currentUpdate = SDL_GetTicks();
        if (currentUpdate - lastUpdate >= UPDATE_INTERVAL_MS)
        {
            if (chip8->delay_timer > 0)
            {
                chip8->delay_timer--;
            }
            if (chip8->sound_timer > 0)
            {
                chip8->sound_timer--;
            }
            lastUpdate = currentUpdate;
        }
        SDL_Delay(5);
    }
}

bool SCREEN_IsKeyPressed(uint8_t key)
{
    return keyboard[key];
}
