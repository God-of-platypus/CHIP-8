#include "param.h"

Param param = {false, false, false, NULL, NULL};

uint8_t parse_param(int argc, char **argv) {
    if (argc <= 1) {
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
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "The option %s does not exist for this program\n", argv[i] + 1);
            return 1;
        } else {
            param.file = argv[i];
        }
    }
    return 0;
}

void print_help(void) {
    fprintf(stdout, "Usage: ./chip-8 [--log] [--help] [--log_file file_to_log_to] rom\n");
}
