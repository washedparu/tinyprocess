#include "process.h"

int main(int argc, char **argv) {
    base cb;

    if(argc == 1) cli_help();

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "--list-processes") == 0 || strcmp(argv[i], "-lf") == 0) {
            if(list_proc(&cb) == FAILED) return 1;
        }
        else if(strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            cli_help();
        }
        else {
            printf("Unknown option: %s\n", argv[i]);
        }
    }
    return 0;
}
