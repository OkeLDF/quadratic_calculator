#include "menus.h"

void sign_up_menu(USER *user, char list_of_users[]){
	int r;
		
	system("cls");
	
	do{
		printf("\n Entre na conta ou crie uma nova:\n\n (1) Entrar.\n (2) Criar.\n (0) Sair.\n\n R: ");
		fflush(stdin);
		if(scanf("%d",&r)==0) r=-1;
		fflush(stdin);
		
		switch(r){
			case 0: system("cls"); exit(0);
			
			case 1:	r = login_menu(user, list_of_users); break;
				
			case 2: r = create_user(list_of_users); break;
				
			default: printf("\n\a > Resposta invalida!"); break;
		}
		
		CLOSE_MENU(2); 
	} while(r!=USER_LOGGED_IN);
}


int create_user(char filename[]) {
	USER new_user;
	FILE *list_of_users_file;
	
	system("cls");
	fflush(stdin);
	
	printf("\n Insira o nome do usuario (maximo: 16 caracteres):\n\n R: ");
	fgets(new_user.name, sizeof(new_user.name), stdin);
	REMOVE_SLASH_N(new_user.name);
	
	if(search_user(new_user, filename)==WRONG_PASSWORD){
		printf("\n > Nome indisponivel!");
		return FALSE;
	}
	
	printf("\n Insira a senha da conta (maximo: 16 caracteres):\n\n R: ");
	fgets(new_user.password, sizeof(new_user.password), stdin);
	REMOVE_SLASH_N(new_user.password);
	
	strcpy(new_user.history, new_user.name);
	strcat(new_user.history, "_history.dad");
	if(create_file(new_user.history)) printf("\n Historico %s criado.\n", new_user.history);
	
	list_of_users_file = fopen(filename, "ab");
	VERIFY_FILE(list_of_users_file, filename,1);
	
	fseek(list_of_users_file, 0, SEEK_END);
	new_user.index = ftell(list_of_users_file) / sizeof(USER);
	fwrite(&new_user, sizeof(USER), 1, list_of_users_file);
	
	fclose(list_of_users_file);
	printf("\n Numero de cadastro do usuario (Num): %d\n\n Usuario %s criado com sucesso!", new_user.index, new_user.name);
	return 0;
}


int login_menu(USER *user, char filename[]){
	int ver=0;
	
	system("cls");
	
	printf("\n > Insira o nome de usuario: ");
	fgets((*user).name, sizeof((*user).name), stdin);
	REMOVE_SLASH_N((*user).name);
	
	printf("\n > Insira a senha: ");
	fgets((*user).password, sizeof((*user).password), stdin);
	REMOVE_SLASH_N((*user).password);
	
	ver = search_user(*user, filename);
	
	if(ver==NO_MATCH){
		printf("\n > Usuario nao foi encontrado!");
		return FALSE;
	}
	if(ver==WRONG_PASSWORD){
		printf("\n > Senha incorreta!");
		return WRONG_PASSWORD;
	}
	
	return log_on_user(user, ver, filename);
}


int user_info_menu (USER *user, char filename[]){
	FILE *list_of_users_file;
	char command_DEL[FN_SIZE+4]="DEL ";
	int r;
	
	system("cls");
		
	do{
		printf("\n ___ INFORMACOES DO USUARIO: ___\n\n Nome: %s\n Senha: %s\n\n Historico: %s\n Numero de Cadastro: %d\n\n O que deseja alterar?\n\n (1) Nome.\n (2) Senha.\n (3) Excluir Permanentemente.\n (0) Voltar.\n\n R: ", 
			(*user).name, (*user).password, (*user).history, (*user).index);
		
		fflush(stdin);
		if(scanf("%d",&r)==0) r=-1;
		fflush(stdin);
		
		switch(r){
			case 1: 
				printf("\n > Novo nome (max: 16 caracteres): ");
				fgets((*user).name, sizeof((*user).name), stdin);
				REMOVE_SLASH_N((*user).name);
				edit_user(*user, filename);
				
				break;
			
			case 2:
				printf("\n > Nova senha (max: 16 caracteres): ");
				fgets((*user).password, sizeof((*user).password), stdin);
				REMOVE_SLASH_N((*user).password);
				edit_user(*user, filename);
				
				break;
			
			case 3:
				printf("\n > Confirme com 1: ");
				if(!scanf("%d",&r)) break;
				if(r!=1) break;
				
				delete_user(*user, filename);
				strcat(command_DEL, (*user).history);
				system(command_DEL);
				
				return USER_REMOVED;
			
			case 0: break;
			
			default: INVALID_ANS;
		}
		system("cls");
		
	} while(r!=0);
	
	return 0;
}


int access_history_menu(EQUATION *eq, char history_fname[FN_SIZE]){
	int r, outnum=2;
	FILE *history_file;
	int num_of_ops=0;
	
	history_file = fopen(history_fname, "rb");
	VERIFY_FILE(history_file, history_fname, 0);
	
	fseek(history_file, 0, SEEK_END);
	num_of_ops = ftell(history_file) / sizeof(EQUATION);
	
	fclose(history_file);
	printf("\n > Insira o numero de entradas a serem mostradas: ");
	fflush(stdin);
	outnum = get_valid_num(num_of_ops);
				
	do{
		system("cls");
		printf("\n ___ HISTORICO DE RESOLUCOES: ___\n\n > Mostrando %d de %d\n", outnum, num_of_ops);
		print_history(outnum, num_of_ops, history_fname);
		
		printf("\n\n (1) Mostrar Entradas Anteriores.\n (2) Apagar Historico.\n (3) Copiar Equacao.\n (0) Voltar.\n\n R: ");
		fflush(stdin);
		if(scanf("%d",&r)==0) r=-1;
		
		switch(r){
			case 0: system("cls"); break;
			
			case 1:
				printf("\n > Insira o numero de entradas a serem mostradas: ");
				fflush(stdin);
				outnum = get_valid_num(num_of_ops);
				break;
			
			case 2: 
				clean_history(eq, history_fname);
				outnum = num_of_ops = 0;
				break;
			
			case 3:
				printf("\n > Escolha uma equacao entre 1 e %d para copiar\n\n R: ", outnum);
				fflush(stdin);
				if(scanf("%d",&r)==0) r=-1;
				
				if(r<1 || r > outnum){
					r=1;
					INVALID_ANS;
					break;
				}
				
				*eq = take_equation(r, history_fname);
				printf("\n > Equacao copiada!");
				CLOSE_MENU(2);
				
				break;
			
			default: INVALID_ANS;
		}
		
	} while(r!=0);
	
    return 0;
}
