#pragma once


#define _GNU_SOURCE
#include "tp_types.h"
#include <linux/prctl.h>
#include <unistd.h>
#include <signal.h>

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int tp_is_number(const char *str);

// kill processes
// TODO: add signals instead of a forcing(-9) bool
PROC_T tp_kill_by_comm(const char *target_name, bool_t force);

// list processes
PROC_T tp_list_proc(base_t* b);

// '---help'
void tp_cli_help();
