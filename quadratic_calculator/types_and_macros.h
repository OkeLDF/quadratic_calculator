#pragma once

#define USER_REMOVED 1
#define USER_LOGGED_IN 2

#define TRUE 1
#define FALSE 0

#define END 1
#define INVALID -1
#define WRONG_PASSWORD -1
#define NO_MATCH -2

#define FN_SIZE 30
#define STR_SIZE 17

#define CLEAN_EQ(eq) \
	(eq).A=0; \
	(eq).B=0; \
	(eq).C=0; \
	(eq).DELTA=0; \
	(eq).X1=0; \
	(eq).X2=0; \
	(eq).roots_qt=INVALID

#define CLOSE_MENU(n_of_endl) \
	for(int i=0; i < (n_of_endl); i++){ \
		printf("\n "); \
	} \
	system("pause"); \
	system("cls")


#define VERIFY_FILE(file,filename,flag) \
	if(!(file)){ \
    	printf("\n > Erro ao abrir arquivo: '"); \
		printf(filename);\
		printf("'!\n\n "); \
		system("pause"); \
		if(flag==1) exit(-1); \
	}
	
#define INVALID_ANS \
	printf("\n > Resposta invalida!\a"); \
	CLOSE_MENU(2)

#define REMOVE_SLASH_N(string) \
	string[strcspn((string), "\n")] = 0;


typedef struct{
	int index;
	char name[STR_SIZE];
	char password[STR_SIZE];
	char history[FN_SIZE];
} USER;


typedef struct{
	float A;
	float B;
	float C;
	float DELTA;
	float X1;
	float X2;
	int roots_qt;
} EQUATION;
