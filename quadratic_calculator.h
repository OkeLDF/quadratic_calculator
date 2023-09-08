#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "types_and_macros.h"

EQUATION insert_coefficients();

EQUATION find_roots(EQUATION eq);

void print_results(EQUATION eq);
