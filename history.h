#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quadratic_calculator.h"
#include "def_macros_and_types.h"

void hy_create_temp_history();

void hy_request_user();

int hy_create_user();

int hy_log_on_user();

int hy_edit_user();

void hy_delete_user();

void hy_save_on_history (EQ_INFO save);

int hy_access_history (float *A, float *B, float *C);

void hy_delete_history ();

void hy_take_equation(int n, float *A, float *B, float *C);
