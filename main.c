#include <stdio.h>

#include "param.h"
#include "screen.h"


int main(int argc, char **argv) {
    uint8_t ret_val = parse_param(argc,argv);
    if (ret_val != 0) {
        return 1;
    }

    if (param.help) {
        print_help();
        return 0;
    }

    CHIP8 *chip8 = CHIP8_init();
    if (!chip8) {
        fprintf(stderr, "Initialisation of the CHIP-8 structure failed\n");
        return 1;
    }

    ret_val = CHIP8_load(chip8, param.file);
    if (ret_val) {
        fprintf(stderr, "The program is too big to fit in memory\n");
        CHIP8_free(chip8);
        return 1;  
    }
    
    ret_val = SCREEN_Init();
    if (ret_val) {
        return 1;
    }

    SCREEN_MainLoop();

    CHIP8_free(chip8);
    SCREEN_Quit();
    return 0;
}
