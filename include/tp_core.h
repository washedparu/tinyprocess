#pragma once


#define _GNU_SOURCE
#include "tp_types.h"
#include <linux/prctl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>


#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int tp_is_number(const char *str);

// kill processes
// TODO: add signals instead of a forcing(-9) bool
bool tp_kill_by_comm(const char *target_name, bool force);


// list processes
bool tp_list_proc(base_t* b);

// '---help'
void tp_show_help();

// kills pids from argv returns 0 on failure 1 on success
bool kill_pids_from_argv(char **argv, int start, int argc, int sig);