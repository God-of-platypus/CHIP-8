#include "chip8.h"

static void font_init(int8_t *array) {
    
    array[ZERO] = 0xF0u;
    array[ZERO + 1u] = 0x90u;
    array[ZERO + 2u] = 0x90u;
    array[ZERO + 3u] = 0x90u;
    array[ZERO + 4u] = 0xF0u;
    
    array[ONE] = 0x20u;
    array[ONE + 1u] = 0x60u;
    array[ONE + 2u] = 0x20u;
    array[ONE + 3u] = 0x20u;
    array[ONE + 4u] = 0xF0u;

    array[TWO] = 0xF0;
    array[TWO + 1u] = 0x10u;
    array[TWO + 2u] = 0xF0u;
    array[TWO + 3u] = 0x80u;
    array[TWO + 4u] = 0xF0u;

    array[THREE] = 0xF0u;
    array[THREE + 1u] = 0x10u;
    array[THREE + 2u] = 0xF0u;
    array[THREE + 3u] = 0x10u;
    array[THREE + 4u] = 0xF0u;

    array[FOUR] = 0x90u;
    array[FOUR + 1u] = 0x90u;
    array[FOUR + 2u] = 0xF0u;
    array[FOUR + 3u] = 0x10u;
    array[FOUR + 4u] = 0x10u;

    array[FIVE] = 0xF0u;
    array[FIVE + 1u] = 0x80u;
    array[FIVE + 2u] = 0xF0u;
    array[FIVE + 3u] = 0x10u;
    array[FIVE + 4u] = 0xF0u;

    array[SIX] = 0xF0u;
    array[SIX + 1u] = 0x80u;
    array[SIX + 2u] = 0xF0u;
    array[SIX + 3u] = 0x90u;
    array[SIX + 4u] = 0xF0u;

    array[SEVEN] = 0xF0u;
    array[SEVEN + 1u] = 0x10u;
    array[SEVEN + 2u] = 0x20u;
    array[SEVEN + 3u] = 0x40u;
    array[SEVEN + 4u] = 0x40u;

    array[EIGHT] = 0xF0u;
    array[EIGHT + 1u] = 0x90u;
    array[EIGHT + 2u] = 0xF0u;
    array[EIGHT + 3u] = 0x90u;
    array[EIGHT + 4u] = 0xF0u;

    array[NINE] = 0xF0u;
    array[NINE + 1u] = 0x90u;
    array[NINE + 2u] = 0xF0u;
    array[NINE + 3u] = 0x10u;
    array[NINE + 4u] = 0xF0u;

    array[A] = 0xF0u;
    array[A + 1u] = 0x90u;
    array[A + 2u] = 0xF0u;
    array[A + 3u] = 0x90u;
    array[A + 4u] = 0x90u;

    array[B] = 0xE0u;
    array[B + 1u] = 0x90u;
    array[B + 2u] = 0xE0u;
    array[B + 3u] = 0x90u;
    array[B + 4u] = 0xE0;

    array[C] = 0xF0u;
    array[C + 1u] = 0x80u;
    array[C + 2u] = 0x80u;
    array[C + 3u] = 0x80u;
    array[C + 4u] = 0xF0u;
    
    array[D] = 0xE0u;
    array[D + 1u] = 0x90u;
    array[D + 2u] = 0x90u;
    array[D + 3u] = 0x90u;
    array[D + 4u] = 0xF0u;
    
    array[E] = 0xF0u;
    array[E + 1u] = 0x80u;
    array[E + 2u] = 0xF0u;
    array[E + 3u] = 0x80u;
    array[E + 4u] = 0xF0u;

    array[F] = 0xF0u;
    array[F + 1u] = 0x80u;
    array[F + 2u] = 0xF0u;
    array[F + 3u] = 0x80u;
    array[F + 4u] = 0x80u; 
}

CHIP8 *CHIP8_init(void) {
    CHIP8 *chip8 = malloc(sizeof(CHIP8));
    if (!chip8) {
        return NULL;
    }

    for(uint16_t i = 0; i < MEMORY_SIZE; i++) {
        chip8->memory[i] = 0x00u;
    }

    for(uint8_t i = 0; i < VARIABLE_REGISTER; i++) {
        chip8->V[i] = 0x00u;
    }

    for(uint8_t i = 0; i < STACK_SIZE; i++) {
        chip8->stack[i] = 0x00u;
    }

    for(uint8_t i = 0; i < DISPLAY_HEIGTH; i++) {
        for(uint8_t j = 0; j < DISPLAY_WIDTH; j++) {
            chip8->display[i][j] = false;
        }
    }

    font_init(chip8->memory);

    chip8->pc = 0x200;
    chip8->I = 0x00;
    chip8->delay_timer = 0x00;
    chip8->sound_timer = 0x00;
    chip8->stack_pos = 0x00;

    return chip8;
}

void CHIP8_free(CHIP8 *chip8) {
    free(chip8);
}

uint8_t CHIP8_load(CHIP8 *chip8, char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (!file) {
        return 1;
    }    
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	while ((nread = getline(&line, &len, file)) != -1) {
        uint16_t i = 0;
        while(line[i] != '\n' && line[i] != '\0') {
            if (chip8->pc >= MEMORY_SIZE) {
                free(line);
                fclose(file);
                return 2;
            }
            chip8->memory[chip8->pc++] = line[i++];
        }
	}
    chip8->pc = 0x200;
    free(line);
    fclose(file);
    return 0;
}

