#include "tp_core.h"
#include "tp_logger.h"

int tp_is_number(const char *str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}





PROC_T tp_kill_by_comm(const char *target_name, bool_t force) {
    DIR *proc = opendir("/proc");
    if (!proc) {
        TP_ERROR("opendir /proc");
        return FAILED;
    }
    
    struct dirent *entry;
    while ((entry = readdir(proc)) != NULL) {
        if (!tp_is_number(entry->d_name)) continue;

        char comm_path[MAX_PATH];
        snprintf(comm_path, sizeof(comm_path), "/proc/%s/comm", entry->d_name);

        FILE *f = fopen(comm_path, "r");
        if (!f) continue;

        char comm[MAX_PATH];
        if (fgets(comm, sizeof(comm), f)) {
    
            comm[strcspn(comm, "\n")] = 0;

            if (strcmp(comm, target_name) == 0) {
                pid_t pid = atoi(entry->d_name);

                if (!force) {
                    if (kill(pid, SIGTERM) == 0) {
                        printf("Killed %s (PID: %d)\n", comm, pid);
                    } 
                    else {
                        printf("(%s) There is no such a process\n", comm);
                    }
                }

                else {
                    if (kill(pid, SIGTERM) == 0) {
                        printf("Killed %s (PID: %d)\n", comm, pid);
                    } 
                    else {
                        printf("(%s) There is no such a process\n", comm);
                    }
                }
            }
        }
        else {
            printf("Couldn't" RED "kill %s\n", target_name);
        }
        fclose(f);
    }

    closedir(proc);
}



PROC_T tp_list_proc(base_t* b) {
    b->cmdline_file = NULL;
    b->proc_dir = opendir("/proc");

    if (!b->proc_dir) {
        TP_ERROR("Couldn't open /proc");
        return FAILED;
    }

    struct dirent *entry;

    while ((entry = readdir(b->proc_dir)) != NULL) {
        if (entry->d_type == DT_DIR && tp_is_number(entry->d_name)) {

            snprintf(b->cmdline_path, sizeof(b->cmdline_path), "/proc/%s/cmdline", entry->d_name);
            snprintf(b->program_name_path, sizeof(b->program_name_path), "/proc/%s/comm", entry->d_name);

            b->cmdline_file = fopen(b->cmdline_path, "r");
            b->program_file = fopen(b->program_name_path, "r");


            if (b->cmdline_file && b->program_file) {
                size_t nread = fread(b->cmdline, 1, sizeof(b->cmdline) - 1, b->cmdline_file);
                fclose(b->cmdline_file);
                char *program_name = fgets(b->program_name_path, sizeof(b->program_name_path), b->program_file);

                for (size_t i = 0; i < nread; i++) {
                    if (b->cmdline[i] == '\0') b->cmdline[i] = ' ';
                }

                size_t len = strlen(b->program_name_path);
                if (len > 0 && b->program_name_path[len - 1] == '\n') {
                    b->program_name_path[len - 1] = '\0';
                }

                printf(BOLD GREEN "\nPID: " RESET "%s   "
                       BOLD RED "Command:   " RESET "%s\n"
                       BOLD CYAN "Program: " RESET "%s\n",
                       entry->d_name, b->cmdline, b->program_name_path);

                fclose(b->program_file);
                }
            }
    }
    
    closedir(b->proc_dir);
    
    return SUCCESS;
} 

void tp_show_help() {
    printf("© 2025 TinyProcess.\n\nUsage: process [FLAGS] [ARGS]\n\nFLAGS:\n"
    "\t--help | -h | --h            shows this message\n"
    "\t--list | -l                  list all processes\n"
    "\t--kill-by-program-name |     -kn kill a process by name\n"
    "\t--kill-by-pid | -kp          kills a process by pid.\n"
    "\t--sig-kill | -sg             forces a process to close(SIGKILL)\n"
    "\t(ARGS are user arguments).\n\te.g: -kp [pid] (pid is an argument)\n"
);
    
}   
