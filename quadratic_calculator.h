#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "def_macros_and_types.h"
#include "history.h"

void qc_insert_coefficients (float *A, float *B, float *C);

void qc_find_roots (float A, float B, float C);
