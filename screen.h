#pragma once
#include <SDL2/SDL.h>

#include "chip8.h"

#define BLOCK_SIZE (15u)

#define SCREEN_WIDTH (DISPLAY_WIDTH * BLOCK_SIZE)
#define SCREEN_HEIGHT (DISPLAY_HEIGTH * BLOCK_SIZE)

typedef enum
{
    one = 30,
    two = 31,
    three = 32,
    c = 33,
    four = 20,
    five = 26,
    six = 8,
    d = 21,
    seven = 4,
    eight = 22,
    nine = 7,
    e = 9,
    a = 29,
    zero = 27,
    b = 6,
    f = 25,
} keyboardInput;

uint8_t SCREEN_Init(void);

void SCREEN_Quit(void);

void SCREEN_MainLoop(void);

void SCREEN_UpdatePixel(const uint8_t x, const uint8_t y, bool value);
