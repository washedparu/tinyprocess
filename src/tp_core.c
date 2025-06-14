#include "tp_core.h"
#include "tp_logger.h"

int tp_is_number(const char *str) {
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}



// kills a process by name returns 0 for failure 1 for success
bool tp_kill_by_comm(const char *target_name, bool force) {
    DIR *proc = opendir("/proc");
    if (!proc) {
        TP_ERROR("opendir /proc");
        return false;
    }
    
    struct dirent *entry;
    int sig = force ? SIGKILL : SIGTERM;

    while ((entry = readdir(proc)) != NULL) {
        if (!tp_is_number(entry->d_name)) continue;

        char comm_path[PATH_MAX];
        snprintf(comm_path, sizeof(comm_path), "/proc/%s/comm", entry->d_name);

        FILE *f = fopen(comm_path, "r");
        if (!f) continue;

        char comm[256];
        if (fgets(comm, sizeof(comm), f)) {
            comm[strcspn(comm, "\n")] = 0; // remove newline

            if (strcmp(comm, target_name) == 0) {
                pid_t pid = atoi(entry->d_name);

                if (kill(pid, sig) == 0) {
                    printf("Killed %s (PID: %d) with signal %d\n", comm, pid, sig);
                } else {
                    printf("Failed to kill %s (PID: %d): %s\n", comm, pid, strerror(errno));
                }
            }
        } else {
            TP_ERROR("Failed to read comm for PID %s\n", entry->d_name);
        }

        fclose(f);
    }

    closedir(proc);
    return true;
}



// list processes returns 0 for failure 1 for success
bool tp_list_proc(base_t* b) {
    b->cmdline_file = NULL;
    b->proc_dir = opendir("/proc");

    if (!b->proc_dir) {
        TP_ERROR("Couldn't open /proc");
        return false;
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
    
    return true;
} 

// prints help
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

// kills pids from argv returns 0 on failure 1 on success
bool kill_pids_from_argv(char **argv, int start, int argc, int sig) {
    int valid_pid = 0;

    for (int i = start; i < argc; i++) {
        char *endptr = NULL;
        pid_t pid = (pid_t) strtol(argv[i], &endptr, 10);

        if (endptr == argv[i] || *endptr != '\0') {
            TP_ERROR("Invalid PID: %s\n", argv[i]);
            continue;
        }

        valid_pid++;

        // both if and else are called
       int ret = kill(pid, sig);
       printf("kill returned: %d\n", ret);
       if (ret == 0) {
           TP_INFO("Killed PID %d with signal %d\n", pid, sig);
       } else {
           TP_ERROR("Failed to send signal %d to PID %d", sig, pid);
       }

    }

    if (valid_pid == 0) {
        TP_ERROR("No valid PIDs provided.\n");
        return false;
    }

    return true;
}

