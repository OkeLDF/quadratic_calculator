#include "history.h"

int delete_user(USER user, char filename[]){
	USER *ALL_USERS, user_from_file;
	int num_of_users;
	FILE *list_of_users_file;
	int i=0;
	
	list_of_users_file = fopen(filename,"rb");
	VERIFY_FILE(list_of_users_file, filename, 2);
	
	fseek(list_of_users_file, 0, SEEK_END);
	num_of_users = ftell(list_of_users_file) / sizeof(USER);
	fseek(list_of_users_file, 0, SEEK_SET);
	
	ALL_USERS = (USER*) malloc (sizeof(USER) * num_of_users-1);
	
	while(i < num_of_users-1){
		fread(&user_from_file, sizeof(USER), 1, list_of_users_file);
		
		if(user_from_file.index != user.index){
			ALL_USERS[i] = user_from_file;
			ALL_USERS[i].index = i;
			i++;
		}
	}
	
	fclose(list_of_users_file);
	list_of_users_file = fopen(filename,"wb");
	VERIFY_FILE(list_of_users_file, filename, 1);
	
	for(i=0; i < num_of_users-1; i++){
		fwrite(&ALL_USERS[i], sizeof(USER), 1, list_of_users_file);
	}
	
	fclose(list_of_users_file);
	printf("\n > Usuario excluido com sucesso.");
	CLOSE_MENU(2);
	return USER_REMOVED;
}


void save_on_history (EQUATION save, char filename[FN_SIZE], EQUATION *lastops_history){
	FILE *history_file;
	
	history_file = fopen(filename, "ab");
	VERIFY_FILE(history_file, filename, 0);
	fwrite(&save, sizeof(EQUATION), 1, history_file);
	
	fclose(history_file);
}


void print_history(int outnum, int num_of_ops, char filename[FN_SIZE]){
	FILE *history_file;
	EQUATION saved_info;
	
	history_file = fopen(filename, "rb");
	VERIFY_FILE(history_file, filename, 0);
	fseek(history_file, (num_of_ops-outnum)*sizeof(EQUATION), SEEK_SET);
	
	for(int i=0; i<outnum; i++){
		fread(&saved_info, sizeof(EQUATION), 1, history_file);
		
		if(saved_info.roots_qt<=0 && saved_info.DELTA==0) continue;
		
		printf("\n%d:\n %.2fxý + %.2fx + %.2f = 0\n	X1 = %.2f;\n	X2 = %.2f;\n	DELTA = %.2f;\n	roots qt = %d\n",
			outnum-i, saved_info.A, saved_info.B, saved_info.C, saved_info.X1, saved_info.X2, saved_info.DELTA, saved_info.roots_qt);
	}
	
	fclose(history_file);
}


void clean_history (EQUATION *eq, char filename[FN_SIZE]){
	FILE *history_file;
	
	(*eq).A=0;
	(*eq).B=0;
	(*eq).C=0;
	(*eq).DELTA=0;
	(*eq).X1=0;
	(*eq).X2=0;
	(*eq).roots_qt=INVALID;
	
	history_file = fopen(filename, "wb");
	VERIFY_FILE(history_file, filename, 1);
	
	fprintf(history_file, "");
	fseek(history_file, 0, SEEK_END);
	
	printf("\n > ");
	
	if(ftell(history_file)==0){
		printf("Historico apagado com sucesso");
	}
	else{
		printf("Falha ao apagar historico!");
	}

	CLOSE_MENU(2);
	fclose(history_file);
}


EQUATION take_equation(int n, char filename[FN_SIZE]){
	EQUATION eq;
	FILE *history_file;
	int num_of_ops=0;
	
	history_file = fopen(filename, "rb");
	VERIFY_FILE(history_file, filename, 0);
	
	fseek(history_file, 0, SEEK_END);
	num_of_ops = ftell(history_file) / sizeof(EQUATION);
	
	if(num_of_ops==0){
		CLEAN_EQ(eq);
		fclose(history_file);
		return eq;
	}
	
	fseek(history_file, (num_of_ops-n)*sizeof(EQUATION), SEEK_SET);
	fread(&eq, sizeof(EQUATION), 1, history_file);
	
	fclose(history_file);
	return eq;
}


int get_valid_num(int num_of_ops){
	int num;
	
	if(scanf("%d",&num)!=1){
		INVALID_ANS;
		return 3;
	}
	
	if(num>num_of_ops) return num_of_ops;
	if(num<0) return 0;
	return num;
}
