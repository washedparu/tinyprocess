#include "tp_core.h"
#include "tp_logger.h"

int main(int argc, char **argv) {
    base_t* b = (base_t*) malloc(sizeof(base_t));

    if (argc == 1) {
        printf("'--help' or '-h' for help.\n");
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--list") || !strcmp(argv[i], "-l")) {
            if (tp_list_proc(b) == FAILED) return 1;
        } 
        else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
            tp_cli_help();
        } 
        else if (!strcmp(argv[i], "--kill-by-program-name") || !strcmp(argv[i], "-kn")) {
            bool_t force = FALSE;
            
            if (i + 2 < argc && (!strcmp(argv[i + 2], "--sig-kill") || !strcmp(argv[i + 2], "-sg"))) {
                force = TRUE;
            }

            if (i + 1 < argc) {
                tp_kill_by_comm(argv[i + 1], force);
                i += force ? 2 : 1;
            } else {
                TP_ERROR("Error: --kill-by-program-name requires a program name\n");
                return 1;
            }
        } 
        else if (!strcmp(argv[i], "--kill-by-pid") || !strcmp(argv[i], "-kp")) {
            bool_t force = FALSE;
            
            if (i + 2 < argc && (!strcmp(argv[i + 2], "--sig-kill") || !strcmp(argv[i + 2], "-sg"))) {
                force = TRUE;
            }

            if (i + 1 < argc) {
                pid_t pid = atoi(argv[i + 1]);
                int signal = force ? SIGKILL : SIGTERM;

                if (kill(pid, signal) == 0) {
                    printf("Killed PID %d with signal %s\n", pid, force ? "SIGKILL" : "SIGTERM");
                } else {
                    TP_ERROR("Failed to kill process (PID: %d)\n", pid);
                }

                i += force ? 2 : 1;
            } else {
                TP_ERROR("Error: --kill-by-pid requires a PID\n");
                return 1;
            }
        } 
        else {
            TP_ERROR("Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    free(b);
    return 0;
}
