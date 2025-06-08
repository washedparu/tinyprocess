#include "process.h"


int is_number(const char *str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}



PROC_T list_proc(base_t* b) {
    b->cmdline_file = NULL;
    b->proc_dir = opendir("/proc");

    if (!b->proc_dir) {
        perror("Couldn't open /proc");
        return FAILED;
    }

    struct dirent *entry;

    while ((entry = readdir(b->proc_dir)) != NULL) {
        if (entry->d_type == DT_DIR && is_number(entry->d_name)) {

            snprintf(b->cmdline_path, sizeof(b->cmdline_path), "/proc/%s/cmdline", entry->d_name);
            snprintf(b->program_name_path, sizeof(b->program_name_path), "/proc/%s/comm", entry->d_name);

            b->cmdline_file = fopen(b->cmdline_path, "r");
            b->program_file = fopen(b->program_name_path, "r");


            if (b->cmdline_file) {
                size_t nread = fread(b->cmdline, 1, sizeof(b->cmdline) - 1, b->cmdline_file);
                fclose(b->cmdline_file);

                if (nread > 0) {
                    b->cmdline[nread] = '\0';

                    
                    for (size_t i = 0; i < nread; i++) {
                        if (b->cmdline[i] == '\0') b->cmdline[i] = ' ';
                    }

                    printf(BOLD GREEN "\nPID: " RESET "%s   ", entry->d_name);
                    printf(BOLD RED "Command:   " RESET "%s\n", b->cmdline);

                }
            }
            if (b->program_file) {
                if (fgets(b->program_name_path, sizeof(b->program_name_path), b->program_file)) {
                    // Remove trailing newline
                    size_t len = strlen(b->program_name_path);
                    if (len > 0 && b->program_name_path[len - 1] == '\n') {
                        b->program_name_path[len - 1] = '\0';
                    }
                    printf(BOLD CYAN "Program: " RESET "%s\n", b->program_name_path);
                }
                fclose(b->program_file);
}
            
        }
    }
    
    closedir(b->proc_dir);
    
    return SUCCESS;
} 

void cli_help() {
    printf("(C) 2025 Process. All rights reserved.\n\n\nUsage: process [FLAGS]\n\nFLAGS:\n");
    printf("\t--help | -h shows this message\n");
    printf("\t--list-processes | -lp   list processes\n");

}   