#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "types_and_macros.h"
#include "security.h"

void save_on_history (EQUATION save, char filename[FN_SIZE], EQUATION *lastops_history);

void print_history(int outnum, int num_of_ops, char filename[FN_SIZE]);

void clean_history (EQUATION *eq, char filename[FN_SIZE]);

EQUATION take_equation(int n, char filename[FN_SIZE]);

int get_valid_num (int num_of_ops);
