#include "param.h"

Param param = {false, false, false, NULL, NULL, NULL};

static bool check_extension(char *str) {
    uint32_t i = strlen(str);

    return (strcmp(str + i - 4, ".ch8") == 0); 
}

uint8_t parse_param(int argc, char **argv) {
    if (argc == 1) {
        fprintf(stderr, "No argument were given\nUse ./chip8 --help for help\n");
        return 1;
    }
    for (int32_t i = 1; i < argc; i++) {
        if (strcmp("--help", argv[i]) == 0) {
            param.help = true;
        } else if (strcmp("--log", argv[i]) == 0) {
            param.log= true;
        } else if (strcmp("--log_file", argv[i]) == 0) {
            if (i + 1 == argc) {
                fprintf(stderr,"No file given for the option log_file\n");
                return 1;
            }
            param.log_file = true;
            param.log_file_name = argv[++i];
        } else if (strcmp(argv[i], "--machine") == 0) {
            if (i + 1 == argc) {
                fprintf(stderr,"No file given for the option log_file\n");
                return 1;
            }
            if (strcmp(argv[i+1], "COSMAC") && strcmp(argv[i+1], "CHIP-48")) {
                fprintf(stderr, "The machine %s is unknown: please use COSMAC or CHIP-48\n", argv[i+1]);
                return 1;        
            }
            param.machine = true;
            param.machine_name = argv[++i];
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "The option %s does not exist for this program\n", argv[i] + 1);
            return 1;
        } else if (!check_extension(argv[i])) {
            fprintf(stderr, "The extension of %s is wrong. Please use a file with the following extension: .ch8\n"
                    ,argv[i]); 
            return 1;
        } else {
            param.file = argv[i];
        }
    }
    if (param.machine == false) {
        param.machine_name = "CHIP-48";
    }
    return 0;
}

void print_help(void) {
    fprintf(stdout, "Usage: ./chip-8 [--log] [--help] [--log_file file_to_log_to] [--machine machine_name] rom\n");
    fprintf(stdout, "This program only uses files with the following extension: .ch8\n");
    fprintf(stdout, "This program has two option for which machine to use: COSMAC and CHIP-48\n");
    fprintf(stdout, "The machine by default is the CHIP-48\n");
}
