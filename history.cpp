#include "history.h"

EQ_INFO temp_history[3];


void hy_create_temp_history(){
	FILE *historyf;
	
	historyf = fopen("history_save.dad", "rb");
	hy_file_verification(historyf);
	
	for(int i=0; i<3; i++){
		fread(&temp_history[i], sizeof(EQ_INFO), 1, historyf);
	}
	
	fclose(historyf);
}


void hy_save_on_history (EQ_INFO save){ /* Salva os coeficientes, a discriminante e o resultado no histórico */
	FILE *historyf;
	
	historyf = fopen("history_save.dad", "wb");
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


void hy_access_history(float *A, float *B, float *C){ /* Permite que o usuário veja as últimas operações, salvas no histórico*/
	FILE* historyf;
	EQ_INFO save;
	float file_size;
	int r;
	
	historyf = fopen("history_save.dad", "rb");
	
	if(hy_file_verification(historyf)==0){
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
				printf("\n Escolha uma equacao para copiar: 1, 2 ou 3\n\n R: ");
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
	}
	else{
		printf("\n > Erro ao abrir arquivo! (impossivel abrir historico em caso de exclusao).\n\n ");
	}
	
    system("cls");
}


int hy_file_verification (FILE* file){
	if(!file){
    	return -1;
	}
	return 0;
}


void hy_delete_history (){
	FILE *historyf;
	
	historyf = fopen("history_save.dad", "w");
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
	
	fclose(historyf);
}


void hy_take_equation(int n, float *A, float *B, float *C){
	*A = temp_history[n].A;
	*B = temp_history[n].B;
	*C = temp_history[n].C;
}
