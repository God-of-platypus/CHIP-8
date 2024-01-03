#pragma once
#include <SDL2/SDL.h>
#include <err.h>

#include "chip8.h"

#define BLOCK_SIZE (15u)

#define SCREEN_WIDTH (DISPLAY_WIDTH * BLOCK_SIZE)
#define SCREEN_HEIGHT (DISPLAY_HEIGTH * BLOCK_SIZE)

uint8_t SCREEN_Init(void);

void SCREEN_Quit(void);

void SCREEN_MainLoop(CHIP8 *chip8);

void SCREEN_UpdatePixel(const uint8_t x, const uint8_t y, bool value);

void SCREEN_UpdateAll(void);

bool SCREEN_IsKeyPressed(uint8_t key);
