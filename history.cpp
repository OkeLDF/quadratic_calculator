#include "history.h"

EQ_INFO temp_history[N_LAST_OPERATIONS];
USER *ALL_USERS;
char curr_user_hy_name[30];

void hy_create_temp_history(){
	FILE *history_file;
	
	history_file = fopen(curr_user_hy_name, "rb");
	HY_VERIFY_FILE(history_file, curr_user_hy_name);
	
	for(int i=0; i < N_LAST_OPERATIONS; i++){
		fread(&temp_history[i], sizeof(EQ_INFO), 1, history_file);
	}
	
	fclose(history_file);
}


void hy_request_user(){
	int r, num_of_users;
	FILE *user_list_file;
	
	system("cls");
	
	user_list_file = fopen("user_list.dad", "rb");
	HY_VERIFY_FILE(user_list_file, "user_list.dad");
	
	fseek(user_list_file, 0, SEEK_END);
	num_of_users = ftell(user_list_file) / sizeof(USER);
	ALL_USERS = (USER*) malloc(num_of_users * sizeof(USER));
	
	fclose(user_list_file);
	
	do{
		printf("\n Entre na conta ou crie uma nova:\n\n (1) Entrar.\n (2) Criar.\n (0) Sair.\n\n R: ");
		scanf("%d", &r);
		fflush(stdin);
		
		switch(r){
			case 0: exit(0);
			
			case 1: r = hy_log_on_user(); break;
				
			case 2: hy_create_user(); break;
				
			default: printf("\n Resposta invalida!"); break;
		}
		
		CLOSE_MENU(2); 
	} while(r!=1);
}


int hy_create_user() {
	USER new_user;
	char temp_name[17];
	FILE *user_list_file;
	FILE *new_user_hy_file;
	int num_of_users;
	
	system("cls");
	fflush(stdin);
	
	// ENTRADA DE DADOS:
	printf("\n Insira o nome do usuario (maximo: 16 caracteres):\n\n R: ");
	gets(new_user.name);
	strcpy(temp_name, new_user.name);
	
	printf("\n Insira a senha da conta (maximo: 16 caracteres):\n\n R: ");
	gets(new_user.password);
	
	// CRIAÇÃO DO HISTÓRICO:
	strcpy(new_user.history, (strcat(temp_name, "_history.dad")));
	
	new_user_hy_file = fopen(new_user.history, "wb");
	HY_VERIFY_FILE(new_user_hy_file, new_user.history);
	
	printf("\n Historico %s criado.\n", new_user.history);
	
	// INCLUSÃO DO USUÁRIO NA LISTA DE USUÁRIOS:
	user_list_file = fopen("user_list.dad", "ab");
	HY_VERIFY_FILE(user_list_file, "user_list.dad");
	
	fwrite(&new_user, sizeof(USER), 1, user_list_file);
	
	printf("\n Usuario criado com sucesso!", new_user.history);
	
	fclose(new_user_hy_file);
	fclose(user_list_file);
	
	return 0;
}


int hy_log_on_user(){
	FILE *user_list_file;
	char login_name[17];
	char login_password[17];
	USER user_from_file;
	int i, num_of_users;
	
	system("cls");
	printf("\n > Insira o nome de usuario: ");
	gets(login_name);
	
	printf("\n > Insira a senha: ");
	gets(login_password);
	
	user_list_file = fopen("user_list.dad","rb");
	HY_VERIFY_FILE(user_list_file, "user_list.dad");
	
	fseek(user_list_file, 0, SEEK_END);
	num_of_users = ftell(user_list_file) / sizeof(USER);
	fseek(user_list_file, 0, SEEK_SET);
	
	for(i=0; i<num_of_users; i++)
	{
		fread(&user_from_file, sizeof(USER), 1, user_list_file);
		
		if(strcmp(user_from_file.name, login_name)==0)
		{
			if(strcmp(user_from_file.password, login_password)==0)
			{
				strcpy(curr_user_hy_name, user_from_file.history);
				return 1;
			}
			
			printf("\n > Senha incorreta!");
			return -1;
		}
	}
	
	printf("\n > Usuario nao foi encontrado!");
	return -2;
}


void hy_save_on_history (EQ_INFO save){
	FILE *history_file;

	history_file = fopen(curr_user_hy_name, "wb");
	HY_VERIFY_FILE(history_file, curr_user_hy_name);
	
	//fseek(history_file, 0, SEEK_END); // acho que essa função está sobrando...
	
	for(int i=0; i < N_LAST_OPERATIONS-1; i++){
		temp_history[i] = temp_history[i+1];
	}
	temp_history[N_LAST_OPERATIONS-1] = save;
	
	for(int i=0; i<N_LAST_OPERATIONS; i++){
		fwrite(&temp_history[i], sizeof(EQ_INFO), 1, history_file);
	}
	
	fclose(history_file);
}


int hy_access_history(float *A, float *B, float *C){
	FILE *history_file;
	EQ_INFO saved_info;
	float file_size;
	int r;
	
	history_file = fopen(curr_user_hy_name, "rb");
	HY_VERIFY_FILE(history_file, curr_user_hy_name);
	
	system("cls");
	
	printf("\n ___ HISTORICO DE RESOLUCOES: ___\n");
	
	for(int i=0; i<N_LAST_OPERATIONS; i++){
		fread(&saved_info, sizeof(EQ_INFO), 1, history_file);
		
		if(saved_info.roots_qt>=0){
			printf("\n %.2fxý + %.2fx + %.2f = 0\n	X1 = %.2f;\n	X2 = %.2f;\n	DELTA = %.2f;\n	roots qt = %d\n",
			saved_info.A, saved_info.B, saved_info.C, saved_info.X1, saved_info.X2, saved_info.DELTA, saved_info.roots_qt);
		}
	}
	
	fclose(history_file);
	
	printf("\n\n\n (1) Apagar Historico.\n (2) Copiar Equacao.\n (0) Voltar.\n\n R: ");
	scanf("%d", &r);
	
	switch(r){
		case 0: system("cls"); break;
		
		case 1: hy_delete_history(); break;
		
		case 2: 
			printf("\n > Escolha uma equacao entre 1 e %d para copiar\n\n R: ", N_LAST_OPERATIONS);
			scanf("%d", &r);
			printf("\n > ");
			
			if(r<0 || r > N_LAST_OPERATIONS){
				printf("Resposta invalida!\a");
				CLOSE_MENU(2);
				
				break;
			}
			
			hy_take_equation(r-1, A, B, C);
			printf("Equacao copiada!");
			CLOSE_MENU(2);
			
			break;
		
		default: 
			printf("Resposta invalida!\a");
			CLOSE_MENU(2);
			
			break;
	}
	
    return 0;
}


void hy_delete_history (){
	FILE *history_file;
	
	history_file = fopen(curr_user_hy_name, "wb");
	HY_VERIFY_FILE(history_file, curr_user_hy_name);
	
	fprintf(history_file, "");
	fseek(history_file, 0, SEEK_END);
	
	printf("\n > ");
	
	if(ftell(history_file)==0){
		printf("Historico apagado com sucesso");
	}
	else{
		printf("Falha ao apagar historico!");
	}
	
	for(int i=0; i < N_LAST_OPERATIONS; i++){
		temp_history[i].A = 0;
		temp_history[i].B = 0;
		temp_history[i].C = 0;
		temp_history[i].DELTA = 0;
		temp_history[i].roots_qt = -1;
		temp_history[i].X1 = 0;
		temp_history[i].X2 = 0;
	}
	
	CLOSE_MENU(2);
	fclose(history_file);
}


void hy_take_equation(int n, float *A, float *B, float *C){
	*A = temp_history[n].A;
	*B = temp_history[n].B;
	*C = temp_history[n].C;
}
