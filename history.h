#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quadratic_calculator.h"
#include "equation_typedef.h"

typedef struct{
	char name[17];
	char password[17];
	char history[30];
	
} HY_USER;

void hy_create_temp_history();

void hy_request_user();

int hy_create_user();

int hy_user_login();

void hy_save_on_history (EQ_INFO save);

int hy_access_history (float *A, float *B, float *C);

int hy_file_verification (FILE* file);

void hy_delete_history ();

void hy_take_equation(int n, float *A, float *B, float *C);
