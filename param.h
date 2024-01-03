#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    bool help;
    bool log;
    bool log_file;
    char *log_file_name;
    char *file;
    bool machine;
    char *machine_name;
} Param;

extern Param param;

uint8_t parse_param(int argc, char **argv);

void print_help(void);
