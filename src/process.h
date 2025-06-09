#pragma once


#define _GNU_SOURCE
#include <dirent.h>
#include <linux/prctl.h>
#include <unistd.h>
#include <signal.h>


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"


#define MAX_PATH 256

typedef struct {
    char cmdline_path[MAX_PATH];
    char cmdline[MAX_PATH];
    char program_name_path[MAX_PATH];

    FILE *cmdline_file;
    FILE *program_file;
    
    DIR *proc_dir;
} base_t;


typedef enum {
    SUCCESS,
    FAILED,  
} PROC_T;

typedef enum {
    FALSE,
    TRUE
} bool_t;


int is_number(const char *str);

// Kill processes
PROC_T kill_by_comm(const char *target_name, bool_t force);

// Kill processes
PROC_T list_proc(base_t* b);

// '---help'
void cli_help();
