#include "tp_core.h"
#include "tp_logger.h"

int main(int argc, char *argv[]) {
    base_t b;

    if (argc == 1) {
        printf("'--help' or '-h' for help.\n");
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--list") || !strcmp(argv[i], "-l")) {
            if (!tp_list_proc(&b)) return 1;
        } 
        
        else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
            tp_show_help();
            return 0;
        } 

        else if (!strcmp(argv[i], "--kill-by-program-name") || !strcmp(argv[i], "-kn")) {
            if (i + 1 >= argc) {
                TP_ERROR("No program name specified after %s\n", argv[i]);
                return 1;
            }

            int sig = SIGTERM;
            i++; 

            if (argv[i][0] == '-' && isdigit(argv[i][1])) {
                sig = atoi(argv[i] + 1);
                i++;
            }

            if (i >= argc) {
                TP_ERROR("No program name specified after signal\n");
                return 1;
            }

            const char *program_name = argv[i];

            // still not implemented
            return 1;
        } 

       else if (!strcmp(argv[i], "--kill-by-pid") || !strcmp(argv[i], "-kp")) {
            if (i + 1 >= argc) {
                TP_ERROR("No PID specified after %s\n", argv[i]);
                return 1;
            }

            int sig = SIGTERM;
            i++;

           
            if (argv[i][0] == '-' && isdigit(argv[i][1])) {
                sig = atoi(argv[i] + 1);
                i++;
                if (i >= argc) {
                    TP_ERROR("No PID specified after signal %d\n", sig);
                    return 1;
                }
            }

            
            if (!kill_pids_from_argv(argv, i, argc, sig)) {
                return 1;
            }
        }

        else {
            TP_ERROR("Unknown option: %s\n", argv[i]);
            return 1;
        }
    }

    return 0;
}