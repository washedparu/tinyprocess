#include "process.h"

int main(int argc, char **argv) {
    base_t cb;

    if (argc == 1) {
        printf("'--help' or '-h' for help.\n");
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--list") == 0 || strcmp(argv[i], "-l") == 0) {
            if (list_proc(&cb) == FAILED) return 1;
        }

        else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--h") == 0) {
            cli_help();
        }

        else if (strcmp(argv[i], "--kill-by-program-name") == 0 || strcmp(argv[i], "-kn") == 0) {
            bool_t force = FALSE;

            // Check if next argument is --sig-kill
            if (i + 2 < argc &&
                (strcmp(argv[i + 2], "--sig-kill") == 0 || strcmp(argv[i + 2], "-sg") == 0)) {
                force = TRUE;
            }

            if (i + 1 < argc) {
                kill_by_comm(argv[i + 1], force);
                i += force ? 2 : 1;  // skip over name and optional --sig-kill
            } else {
                fprintf(stderr, "Error: --kill-by-program-name requires a program name\n");
                return 1;
            }
        }

        else if (strcmp(argv[i], "--kill-by-pid") == 0 || strcmp(argv[i], "-kp") == 0) {
            bool_t force = FALSE;

            // Check if --sig-kill is after the PID
            if (i + 2 < argc &&
                (strcmp(argv[i + 2], "--sig-kill") == 0 || strcmp(argv[i + 2], "-sg") == 0)) {
                force = TRUE;
            }

            if (i + 1 < argc) {
                pid_t pid = atoi(argv[i + 1]);
                int signal = force ? SIGKILL : SIGTERM;

                if (kill(pid, signal) == 0) {
                    printf("Killed PID %d with signal %s\n", pid, force ? "SIGKILL" : "SIGTERM");
                } else {
                    perror("kill");
                }

                i += force ? 2 : 1;  // skip over pid and optional --sig-kill
            } else {
                fprintf(stderr, "Error: --kill-by-pid requires a PID\n");
                return 1;
            }
        }

        else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    return 0;
}
