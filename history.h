#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "quadratic_calculator.h"
#include "equation_typedef.h"

void hy_create_temp_history();

void hy_save_on_history (EQ_INFO save);

void hy_access_history (float *A, float *B, float *C);

int hy_file_verification (FILE* file);

void hy_delete_history ();

void hy_take_equation(int n, float *A, float *B, float *C);
