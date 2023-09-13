#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "types_and_macros.h"
#include "security.h"
#include "login.h"
#include "history.h"

void sign_up_menu(USER *user, char list_of_users[]);

int create_user(char filename[]);

int login_menu(USER *user, char filename[]);

int user_info_menu(USER *user, char filename[]);

int access_history_menu(EQUATION *eq, char history_fname[FN_SIZE]);
