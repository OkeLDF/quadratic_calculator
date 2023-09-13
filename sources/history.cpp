#include "history.h"

void save_on_history (EQUATION save, char filename[FN_SIZE], EQUATION *lastops_history){
	FILE *history_file;
	
	history_file = get_file(filename, "ab");
	fwrite(&save, sizeof(EQUATION), 1, history_file);
	
	fclose(history_file);
}


void print_history(int outnum, int num_of_ops, char filename[FN_SIZE]){
	FILE *history_file;
	EQUATION saved_info;
	
	history_file = get_file(filename, "rb");
	fseek(history_file, (num_of_ops-outnum)*sizeof(EQUATION), SEEK_SET);
	
	for(int i=0; i<outnum; i++){
		fread(&saved_info, sizeof(EQUATION), 1, history_file);
		
		if(saved_info.roots_qt<=0 && saved_info.DELTA==0) continue;
		
		printf("\n%d:\n %.2fxý + %.2fx + %.2f = 0",
			outnum-i, saved_info.A, saved_info.B, saved_info.C);
		
		if(saved_info.DELTA < 0){
			printf("\n	X1 = %.2f + %.2f * i;", saved_info.X1, saved_info.X2);
			printf("\n	X2 = %.2f - %.2f * i;", saved_info.X1, saved_info.X2);
		}
		else printf("\n	X1 = %.2f;\n	X2 = %.2f;", saved_info.X1, saved_info.X2);
		
		printf("\n	DELTA = %.2f;\n	roots qt = %d\n", saved_info.DELTA, saved_info.roots_qt);
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
	
	history_file = get_file(filename, "wb");
	
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
	
	history_file = get_file(filename, "rb");
	
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
