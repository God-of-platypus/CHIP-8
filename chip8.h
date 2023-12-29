#pragma once

#define _POSIX_C_SOURCE 200809L

#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "screen.h"
#include "param.h"

#define STACK_SIZE              (32u)
#define MEMORY_SIZE             (4096u)
#define VARIABLE_REGISTER       (16u)
#define DISPLAY_WIDTH           (64u)
#define DISPLAY_HEIGTH          (32u)

#define FIRST_NIBBLE(A)         (((A) & 0xF000) >> 12)
#define SECOND_NIBBLE(A)        (((A) & 0x0F00) >> 8)
#define THIRD_NIBBLE(A)         (((A) & 0x00F0) >> 4)
#define FOURTH_NIBBLE(A)        ((A) & 0x000F)

#define LAST_THREE_NIBBLE(A)    ((A) & 0x0FFF)
#define LAST_BYTE(A)            ((A) & 0x00FF)

typedef struct {
    uint8_t memory[MEMORY_SIZE];
    uint8_t V[VARIABLE_REGISTER];
    uint16_t pc;                                    /*Program Counter*/
    uint16_t I;                                     /*Index register*/
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint16_t stack[STACK_SIZE];
    uint8_t stack_pos;
    bool display[DISPLAY_HEIGTH][DISPLAY_WIDTH];
} CHIP8;

typedef enum {
    ZERO    = 0x50u,
    ONE     = 0x55u,
    TWO     = 0x5Au,
    THREE   = 0x5Fu,
    FOUR    = 0x63u,
    FIVE    = 0x68u,
    SIX     = 0x6Du,
    SEVEN   = 0x72u,
    EIGHT   = 0x77u,
    NINE    = 0x7Cu,
    A       = 0x81u,
    B       = 0x86u,
    C       = 0x8Bu,
    D       = 0x90u,
    E       = 0x95u,
    F       = 0x9Bu,
} font_address;

CHIP8 *CHIP8_init(void);

void CHIP8_free(CHIP8 *chip8);

uint8_t CHIP8_load(CHIP8 *chip8, char *file_name);

uint16_t CHIP8_fetch(CHIP8 *chip8);

void CHIP8_exec(CHIP8 *chip8, uint16_t code);
