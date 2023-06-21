#include "login.h"

int search_user (USER searched_user, char filename[]){
	FILE *list_of_users_file;
	USER user_from_file;
	int num_of_users;
	
	list_of_users_file = fopen(filename, "rb");
	VERIFY_FILE(list_of_users_file, filename, 1);
	
	fseek(list_of_users_file, 0, SEEK_END);
	num_of_users = ftell(list_of_users_file) / sizeof(USER);
	fseek(list_of_users_file, 0, SEEK_SET);
	
	for(int i=0; i < num_of_users; i++){
		fread(&user_from_file, sizeof(USER), 1, list_of_users_file);
		
		if(strcmp(user_from_file.name, searched_user.name)!=0) continue;
		if(strcmp(user_from_file.password, searched_user.password)!=0) return WRONG_PASSWORD;
		
		fclose(list_of_users_file);
		return user_from_file.index;
	}
	fclose(list_of_users_file);
	return NO_MATCH;
}


int log_on_user(USER *user, int count, char filename[]){
	FILE *list_of_users_file;
	
	list_of_users_file = fopen(filename, "rb");
	VERIFY_FILE(list_of_users_file, filename, 1);
	
	fseek(list_of_users_file, count*sizeof(USER), SEEK_SET);
	fread(user, sizeof(USER), 1, list_of_users_file);
	
	fclose(list_of_users_file);
	return USER_LOGGED_IN;
}


int create_file(char filename[]){
	FILE *fp;
	fp = fopen(filename, "wb");
	VERIFY_FILE(fp, filename, 1);
	fclose(fp);
	return TRUE;
}


int edit_user (USER user, char filename[]){
	FILE *list_of_users_file;
	
	list_of_users_file = fopen(filename,"rb+");
	VERIFY_FILE(list_of_users_file, filename, 1);
	
	fseek(list_of_users_file, sizeof(USER)*user.index, SEEK_SET);
	fwrite(&user, sizeof(USER), 1, list_of_users_file);
	fclose(list_of_users_file);
}


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
