#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "types_and_macros.h"

int search_user(USER searched_user, char filename[]);

int log_on_user(USER *user, int count, char filename[]);

int create_file(char filename[]);

int edit_user (USER user, char filename[]);
