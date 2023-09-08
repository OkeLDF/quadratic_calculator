#include "history.h"

#define CLEAN_UP 	 \
	printf("\n\n "); \
	system("pause"); \
	system("cls")

EQ_INFO temp_history[3];

HY_USER *ALL_USERS;

char curr_user_history[30];

void hy_create_temp_history(){
	FILE *historyf;
	
	historyf = fopen(curr_user_history, "rb");
	hy_file_verification(historyf);
	
	for(int i=0; i<3; i++){
		fread(&temp_history[i], sizeof(EQ_INFO), 1, historyf);
	}
	
	fclose(historyf);
}


void hy_request_user(){
	int r, num_of_users;
	FILE *user_listf;
	
	system("cls");
	
	user_listf = fopen("user_list.dad", "rb");
	if (hy_file_verification(user_listf) == -1) exit(-1);
	
	fseek(user_listf,0,SEEK_END);
	num_of_users = ftell(user_listf) / sizeof(HY_USER);
	ALL_USERS = (HY_USER*) malloc(num_of_users * sizeof(HY_USER));
	
	fclose(user_listf);
	
	do{
		printf("\n Entre na conta ou crie uma nova:\n\n (1) Entrar.\n (2) Criar.\n (0) Sair.\n\n R: ");
		scanf("%d", &r);
		fflush(stdin);
		
		switch(r){
			case 0: exit(0);
			
			case 1: r = hy_user_login(); break;
				
			case 2: hy_create_user(); break;
				
			default: 
				printf("\n Resposta invalida!");
				CLEAN_UP;
				break;
		}
		
	} while(r!=1);
	
	CLEAN_UP;
}


int hy_create_user() {
	HY_USER new_user;
	char temp_name[17];
	FILE *user_listf;
	FILE *new_user_historyf;
	int num_of_users;
	
	system("cls");
	fflush(stdin);
	
	printf("\n Insira o nome do usuario (maximo: 16 caracteres):\n\n R: ");
	gets(new_user.name);
	strcpy(temp_name, new_user.name);
	
	printf("\n Insira a senha da conta (maximo: 16 caracteres):\n\n R: ");
	gets(new_user.password);
	
	strcpy(new_user.history, (strcat(temp_name, "_history.dad")));
	
	new_user_historyf = fopen(new_user.history, "wb");
	if(hy_file_verification(new_user_historyf)==-1) return -1;
	
	printf("\n Historico %s criado.\n", new_user.history);
	
	user_listf = fopen("user_list.dad", "ab");
	if(hy_file_verification(user_listf)==-1) return -2;
	
	fwrite(&new_user, sizeof(HY_USER), 1, user_listf);
	
	printf("\n Usuario criado com sucesso!", new_user.history);
	
	fclose(new_user_historyf);
	fclose(user_listf);
	
	CLEAN_UP;
	return 0;
}


int hy_user_login(){
	FILE *user_listf;
	char login_name[17];
	char login_password[17];
	HY_USER user_from_file;
	int i, num_of_users;
	
	system("cls");
	printf("\n > Insira o nome de usuario: ");
	gets(login_name);
	
	printf("\n > Insira a senha: ");
	gets(login_password);
	
	user_listf = fopen("user_list.dad","rb");
	if(hy_file_verification(user_listf)==-1) return -1;
	
	fseek(user_listf, 0, SEEK_END);
	num_of_users = ftell(user_listf) / sizeof(HY_USER);
	fseek(user_listf, 0, SEEK_SET);
	
	for(i=0; i<num_of_users; i++)
	{
		fread(&user_from_file, sizeof(HY_USER), 1, user_listf);
		
		if(strcmp(user_from_file.name, login_name)==0)
		{
			if(strcmp(user_from_file.password, login_password)==0)
			{
				strcpy(curr_user_history, user_from_file.history);
				return 1;
			}
			else
			{
				printf("\n > Senha incorreta!");
				CLEAN_UP;
				return -1;
			}
		}
	}
	
	printf("\n > Usuario nao foi encontrado!");
	CLEAN_UP;
	return -2;
}


void hy_save_on_history (EQ_INFO save){ /* Salva os coeficientes, a discriminante e o resultado no histórico */
	FILE *historyf;

	historyf = fopen(curr_user_history, "wb");
	hy_file_verification(historyf);
	
	fseek(historyf,0,2);
	
	temp_history[0] = temp_history[1];
	temp_history[1] = temp_history[2];
	temp_history[2] = save;
	
	for(int i=0; i<3; i++){
		fwrite(&temp_history[i], sizeof(EQ_INFO), 1, historyf);
	}
	
	fclose(historyf);
}


int hy_access_history(float *A, float *B, float *C){ /* Permite que o usuário veja as últimas operações, salvas no histórico*/
	FILE *historyf;
	
	EQ_INFO save;
	float file_size;
	int r;
	
	historyf = fopen(curr_user_history, "rb");
	if(hy_file_verification(historyf)==-1) return -1;
	
	system("cls");
	
	printf("\n ___ HISTORICO DE RESOLUCOES: ___\n");
	
	for(int i=0; i<3; i++){
		fread(&save, sizeof(EQ_INFO), 1, historyf);
		
		printf("\n %.2fxý + %.2fx + %.2f = 0\n	X1 = %.2f;\n	X2 = %.2f;\n	DELTA = %.2f;\n	roots qt = %d\n",
			save.A, save.B, save.C, save.X1, save.X2, save.DELTA, save.roots_qt);
	}
	
	fclose(historyf);
	
	printf("\n\n\n (1) Apagar Historico.\n (2) Copiar Equacao.\n (0) Voltar.\n\n R: ");
	scanf("%d", &r);
	
	switch(r){
		case 0: break;
		
		case 1: hy_delete_history(); break;
		
		case 2: 
			printf("\n Escolha uma equação para copiar: 1, 2 ou 3\n\n R: ");
			scanf("%d", &r);
			
			if(r<0 || r>3){
				printf("\n\a > Resposta invalida!\n\n ");
				system("pause");
			}
			
			else{
				hy_take_equation(r-1, A, B, C); 
			}
			
			printf("\n Equacao copiada!\n\n ");
			system("pause");
			
			break;
		
		default: 
			printf("\n\a > Resposta invalida!\n\n ");
			system("pause");
			break;
	}
	
    system("cls");
    return 0;
}


int hy_file_verification (FILE* file){
	if(!file){
    	printf("\n Erro ao abrir arquivo!\n\n ");
		system("pause");
		return -1;
	}
	return 0;
}


void hy_delete_history (){
	FILE *historyf;
	
	historyf = fopen(curr_user_history, "wb");
	hy_file_verification(historyf);
	
	fprintf(historyf, "");
	fseek(historyf,0,2);
	
	if(ftell(historyf)==0){
		printf("\n Historico apagado com sucesso\n\n ");
		system("pause");
	}
	else{
		printf("\n Falha ao apagar historico!\n\n ");
		system("pause");
	}
	
	for(int i=0; i<3; i++){
		temp_history[i].A = 0;
		temp_history[i].B = 0;
		temp_history[i].C = 0;
		temp_history[i].DELTA = 0;
		temp_history[i].roots_qt = 0;
		temp_history[i].X1 = 0;
		temp_history[i].X2 = 0;
	}
	
	fclose(historyf);
}


void hy_take_equation(int n, float *A, float *B, float *C){
	*A = temp_history[n].A;
	*B = temp_history[n].B;
	*C = temp_history[n].C;
}
