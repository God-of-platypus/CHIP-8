#include "chip8.h"

static void font_init(uint8_t *array) {
    
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

static void CHIP8_clear_display(CHIP8 *chip8) {
    for(uint8_t i = 0; i < DISPLAY_HEIGTH; i++) {
        for(uint8_t j = 0; j < DISPLAY_WIDTH; j++) {
            chip8->display[i][j] = false;
        } 
    }
}

static void CHIP8_ALU(CHIP8 *chip8, uint16_t code) {
    uint8_t var1;
    uint8_t var2;
    uint8_t var3;
    switch (FOURTH_NIBBLE(code)) {
        case 0x0:
            chip8->V[SECOND_NIBBLE(code)] = chip8->V[THIRD_NIBBLE(code)];
            break;
        case 0x1:
            chip8->V[SECOND_NIBBLE(code)] |= chip8->V[THIRD_NIBBLE(code)];
            break;
        case 0x2:
            chip8->V[SECOND_NIBBLE(code)] &= chip8->V[THIRD_NIBBLE(code)];
            break;
        case 0x3:
            chip8->V[SECOND_NIBBLE(code)] ^= chip8->V[THIRD_NIBBLE(code)];
            break;
       case 0x4:
            var1 = chip8->V[SECOND_NIBBLE(code)];
            var2 = chip8->V[THIRD_NIBBLE(code)];
            var3 = var1 + var2;
            if (var3 < var1 || var3 < var2) {
                chip8->V[0xF] = 1;
            } else {
                chip8->V[0xF] = 0;
            }
            chip8->V[SECOND_NIBBLE(code)];
            break;
       case 0x5:
            var1 = chip8->V[SECOND_NIBBLE(code)];
            var2 = chip8->V[THIRD_NIBBLE(code)];
            chip8->V[0xF] = var1 >= var2;
            chip8->V[SECOND_NIBBLE(code)] = var1 - var2;
            break;
       case 0x6:
            if (strcmp(param.machine_name, "COSMAC") == 0) {
                chip8->V[SECOND_NIBBLE(code)] = chip8->V[THIRD_NIBBLE(code)];
            }
            chip8->V[0xF] = 0x1 & chip8->V[SECOND_NIBBLE(code)];
            chip8->V[SECOND_NIBBLE(code)] = chip8->V[SECOND_NIBBLE(code)] >> 1;
            break;
       case 0x7:
            var1 = chip8->V[SECOND_NIBBLE(code)];
            var2 = chip8->V[THIRD_NIBBLE(code)];
            chip8->V[0xF] = var2 >= var1;
            chip8->V[SECOND_NIBBLE(code)] = var2 - var1;
            break;
       case 0xE:
            if (strcmp(param.machine_name, "COSMAC") == 0) {
                chip8->V[SECOND_NIBBLE(code)] = chip8->V[THIRD_NIBBLE(code)];
            }
            chip8->V[0xF] = 0x80 & chip8->V[SECOND_NIBBLE(code)];
            chip8->V[SECOND_NIBBLE(code)] = chip8->V[SECOND_NIBBLE(code)] << 1;
            break;
        default:
            err(1, "Unknown command\n");
    }
}

static void CHIP8_display(CHIP8 *chip8, uint16_t code) {
    uint8_t x = chip8->V[SECOND_NIBBLE(code)] % DISPLAY_WIDTH;
    uint8_t y = chip8->V[THIRD_NIBBLE(code)] % DISPLAY_HEIGTH;
    uint8_t n = FOURTH_NIBBLE(code);

    chip8->V[0xF] = 0;

    for(uint8_t i = 0; i < n && y + i < DISPLAY_HEIGTH; i++) {
        uint8_t byte = chip8->memory[chip8->I + i];
        for (uint8_t j = 7; j >= 0 && x + j < DISPLAY_WIDTH; j++) 
        {
            bool pixel = (bool)(byte >> j & 0x1);
            if (pixel && chip8->display[y + i][x + j]) {
                chip8->V[0xF] = 1;
                SCREEN_UpdatePixel(x + j, y + i, false);
                chip8->display[y + i][x + j] = false;
            } else if (pixel && !chip8->display[y+i][x+j]){
                SCREEN_UpdatePixel(x + j, y + i, pixel);
                chip8->display[y + i][x + j] = true;
            }
        }
    }
};

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

uint16_t CHIP8_fetch(CHIP8 *chip8) {
    if (chip8->pc >=  MEMORY_SIZE - 1) {
        err(1, "Tried to acces memory out of bound\n");
    }
    uint16_t result = (chip8->memory[chip8->pc++] << 8) & chip8->memory[chip8->pc++];
}

void CHIP8_exec(CHIP8 *chip8, uint16_t code) {
    if (code == 0x00E0) {
        CHIP8_clear_display(chip8);
        return;
    } else if (FIRST_NIBBLE(code) == 0x1) {
        chip8->pc = LAST_THREE_NIBBLE(code);
        return; 
    } else if (FIRST_NIBBLE(code) == 0x2) {
        if (chip8->stack_pos == STACK_SIZE - 1) {
            err(1,"Stack overflow\n");
        }
        chip8->stack[chip8->stack_pos++] = chip8->pc;
        chip8->pc = LAST_THREE_NIBBLE(code);
    } else if (code == 0x00EE) {
        if (chip8->stack_pos == 0) {
            err(1, "Stack Underflow\n");
        }
        chip8->pc = chip8->stack[chip8->stack_pos--];
    } else if (FIRST_NIBBLE(code) == 0x3) {
        uint8_t compare1 = chip8->V[SECOND_NIBBLE(code)];
        uint8_t compare2 = LAST_BYTE(code);
        if (compare1 == compare2) {
            chip8->pc += 2;
        }
    } else if (FIRST_NIBBLE(code) == 0x4) {
        uint8_t compare1 = chip8->V[SECOND_NIBBLE(code)];
        uint8_t compare2 = LAST_BYTE(code);
        if (compare1 != compare2) {
            chip8->pc += 2;
        }
    } else if (FIRST_NIBBLE(code) == 0x5) {
        uint8_t compare1 = chip8->V[SECOND_NIBBLE(code)];
        uint8_t compare2 = chip8->V[THIRD_NIBBLE(code)];
        if (compare1 == compare2) {
            chip8->pc += 2;
        }
    } else if (FIRST_NIBBLE(code) == 0x9) {
        uint8_t compare1 = chip8->V[SECOND_NIBBLE(code)];
        uint8_t compare2 = chip8->V[THIRD_NIBBLE(code)];
        if (compare1 != compare2) {
            chip8->pc += 2;
        }
    } else if (FIRST_NIBBLE(code) == 0x6) {
        chip8->V[SECOND_NIBBLE(code)] = LAST_BYTE(code);
    } else if (FIRST_NIBBLE(code) == 0x7) {
        chip8->V[SECOND_NIBBLE(code)] += LAST_BYTE(code);
    } else if (FIRST_NIBBLE(code) == 0x8) {
        CHIP8_ALU(chip8, code);
    } else if (FIRST_NIBBLE(code) == 0xA) {
        chip8->I = LAST_THREE_NIBBLE(code);
    } else if (FIRST_NIBBLE(code) == 0xB) {
        chip8->pc = LAST_THREE_NIBBLE(code);
        if (strcmp(param.machine_name, "COSMAC") == 0) {
            chip8->pc += chip8->V[0];
        } else {
            chip8->pc += chip8->V[SECOND_NIBBLE(code)];
        }
    } else if (FIRST_NIBBLE(code) == 0xC) {
        uint8_t res = rand() % 0xFF;
        chip8->V[SECOND_NIBBLE(code)] = res & LAST_BYTE(code);
    } else if (FIRST_NIBBLE(code) == 0xD) {
        CHIP8_display(chip8, code);
    } else {
        err(1, "Unknown command\n");
    }
}
