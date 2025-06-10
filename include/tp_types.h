#pragma once

// includes for base struct
#include <stdio.h>
#include <dirent.h>

// colors in ASCII format
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"


#define MAX_PATH 256

// base struct 
typedef struct {
    char cmdline_path[MAX_PATH];
    char cmdline[MAX_PATH];
    char program_name_path[MAX_PATH];

    FILE *cmdline_file;
    FILE *program_file;
    
    DIR *proc_dir;
} base_t;


// return types
typedef enum {
    SUCCESS,
    FAILED,  
} PROC_T;

typedef enum {
    FALSE,
    TRUE
} bool_t;