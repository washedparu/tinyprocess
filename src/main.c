#include "process.h"


int main(int argc, char **argv) {
    base_t cb;

    if(argc == 1) printf("'--help' or '-h' for help.\n");

    for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--list") == 0 || strcmp(argv[i], "-l") == 0) {
        if (list_proc(&cb) == FAILED) return 1;
    }

    else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--h") == 0) {
        cli_help();
    }

    else if (strcmp(argv[i], "--kill-by-program-name") == 0 || strcmp(argv[i], "-kn") == 0) {
        if (i + 1 < argc) {
            if (kill_by_comm(argv[++i]) == FAILED) {
                fprintf(stderr, "Error: Failed to kill by program name: %s\n", argv[i]);
                return 1;
            }
        } else {
            fprintf(stderr, "Error: --kill-by-program-name requires a program name\n");
            return 1;
        }
    }

    else if (strcmp(argv[i], "--kill-by-pid") == 0 || strcmp(argv[i], "-kp") == 0) {
        if (i + 1 < argc) {
            pid_t pid = atoi(argv[++i]);
            if (kill(pid, SIGTERM) == 0) {
                printf("Sent SIGTERM to PID %d\n", pid);
            } else {
                perror("Failed to send SIGTERM");
                return 1;
            }
        } else {
            fprintf(stderr, "Error: --kill-by-pid requires a PID\n");
            return 1;
        }
    }

    else {
        printf("Unknown option: %s\n", argv[i]);
        return 1;
    }
}

    return 0;
}