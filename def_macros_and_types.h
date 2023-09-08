#pragma once

#define N_LAST_OPERATIONS 3

#define CLOSE_MENU(n_of_endl) \
	for(int i=0; i < (n_of_endl); i++){ \
		printf("\n "); \
	} \
	system("pause"); \
	system("cls")


#define HY_VERIFY_FILE(file,filename) \
	if(!file){ \
    	printf("\n > Erro ao abrir arquivo: '"); \
		printf(filename);\
		printf("'!\n\n "); \
		system("pause"); \
		exit(-1); \
	}
	
#define INVALID_ANS \
	printf("Resposta invalida!\a"); \
	CLOSE_MENU(2); \
	break
	

typedef struct{
	int index;
	char name[17];
	char password[17];
	char history[30];
	
} USER;


typedef struct{
	float A;
	float B;
	float C;
	float DELTA;
	float X1;
	float X2;
	int roots_qt;
} EQ_INFO;
