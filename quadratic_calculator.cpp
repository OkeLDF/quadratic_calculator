#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/* TIPOS: */
typedef struct{
	float A;
	float B;
	float C;
	float DELTA;
	float X1;
	float X2;
	int roots_qt;
} EQ_INFO;


/* PROTÓTIPOS: */
void qc_insert (float *A, float *B, float *C);

void qc_find_roots (float A, float B, float C);

void qc_save_on_history (EQ_INFO save);

void qc_acess_history ();

int qc_file_verification (FILE* file);

void qc_delete_history ();


/* MAIN: */
int main(){ /* Inicia o menu */
    int r;
    float A = 0, B = 0, C = 0;
    FILE *historyf;
    
    do{
        printf("\n ___ RAIZ DE EQUA. DE SEGUNDO GRAU ___\n");
        
        if(A==0 && B==0 && C==0) printf("\n\n > Nenhum coeficiente salvo\n");
        else printf("\n\n > %.0fx2 + %.0fx + %.0f = 0\n", A,B,C);
        
        printf("\n\n (1) Inserir Coeficientes.\n\n (2) Calcular Raizes.\n\n (3) Acessar Historico.\n\n (0) Sair.\n\n\n R: ");
        scanf("%d",&r);
        
        switch(r){
            case 1: qc_insert(&A,&B,&C); break;
                
            case 2: qc_find_roots(A,B,C); break;
            
            case 3: qc_acess_history(); break;
            
            case 0: break;
                
            default: printf("\n\n\a > Resposta invalida!\n\n ");
        }
		        
    } while(r!=0);
    
    return 0;
}


void qc_insert(float *A, float *B, float *C){ /* Insere os valores da A, B e C */
    system("cls");
    printf("\n > Insira os coeficientes da funcao, separado por espaco:\n\n ax2 + bx + c = 0\n\n R: ");
    scanf("%f %f %f", A, B, C);

    printf("\n > Coeficientes salvos!\n\n ");
    
    system("pause");
    system("cls");
}


void qc_find_roots(float A, float B, float C){ /* Calcula as raizes da Eq */
    float DELTA=(B*B)-(4*A*C);
    EQ_INFO equation;
    
    equation.A = A;
    equation.B = B;
    equation.C = C;
    equation.DELTA = DELTA;
    equation.X1 = -0.01;
    equation.X2 = -0.01;
    equation.roots_qt = 0;
    
    if(DELTA==0){ /* Discriminante nula => 1 raiz */
    	equation.X1 = -B/(2*A);
    	equation.roots_qt =  1;
    	
        printf("\n\n > X = %.2f\n\n > Delta = %.2f\n\n\n ", equation.X1, DELTA);
		qc_save_on_history(equation);      
    }
    else{
    	if(DELTA<0){ /* Discriminante negativa => impossível */
    		printf("\n\n\a > Impossivel calucar a raiz! (discriminante = %.2f)\n\n\n ", DELTA);
            qc_save_on_history(equation);
        }
        else{ /* Discriminante positiva => 2 raizes, se A!=0 */
            if(A==0){
            	equation.X1 = -C/B;
            	equation.roots_qt = 1;
            	
				printf("\n\n > X = %.2f\n\n\n ", equation.X1);
				qc_save_on_history(equation);
			}
            else{
            	equation.X1 = (sqrt(DELTA)-B)/(2*A);
            	equation.X2 = -(sqrt(DELTA)+B)/(2*A);
            	equation.roots_qt = 2;
            	
				printf("\n\n > X = %.2f  ou  X = %.2f\n\n > Delta = %.2f\n\n\n ", equation.X1, equation.X2, DELTA);
				qc_save_on_history(equation);
			}
        }
    }
    
    system("pause");
    system("cls");
}


void qc_save_on_history (EQ_INFO save){ /* Salva os coeficientes, a discriminante e o resultado no histórico */
	FILE *historyf;
	
	historyf = fopen("history_save.dad", "ab");
	qc_file_verification(historyf);
	
	fseek(historyf,0,2);
	
	fwrite(&save, sizeof(EQ_INFO), 1, historyf);
	
	fclose(historyf);
}


void qc_acess_history(){ /* Permite que o usuário veja as últimas operações, salvas no histórico*/
	FILE* historyf;
	EQ_INFO save;
	float file_size, current_position;
	int r;
	
	historyf = fopen("history_save.dad", "rb");
	
	if(qc_file_verification(historyf)==0){
		system("cls");
		
		fseek(historyf,0,2);
		file_size = ftell(historyf);
		fseek(historyf,0,0);
		
		printf("\n ___ HISTORICO DE RESOLUCOES: ___\n");
		
		while(current_position != file_size){
			fread(&save, sizeof(EQ_INFO), 1, historyf);
			
			printf("\n %.2fx2 + %.2fx + %.2f = 0\n	X1 = %.2f;\n	X2 = %.2f;\n	DELTA = %.2f;\n	roots qt = %d\n",
				save.A, save.B, save.C, save.X1, save.X2, save.DELTA, save.roots_qt);
				
			current_position = ftell(historyf);
		}
		
		fclose(historyf);
		
		do{
			printf("\n\n\n (0) Voltar.\n (1) Apagar historico.\n\n R: ");
			scanf("%d", &r);
			
			switch(r){
				case 0: break;
				
				case 1: qc_delete_history(); break;
				
				default: printf("\n\n\a > Resposta invalida!\n");
			}
			
		} while(r!=0 && r!=1);
		
		printf("\n ");
	}
	else{
		printf("\n > Erro ao abrir arquivo! (impossivel abrir historico em caso de exclusao).\n\n ");
	}
	
    system("cls");
}


int qc_file_verification (FILE* file){
	if(!file){
    	return -1;
	}
	return 0;
}

void qc_delete_history (){
	FILE *historyf;
	
	historyf = fopen("history_save.dad", "w");
	qc_file_verification(historyf);
	
	fprintf(historyf, "");
	fseek(historyf,0,2);
	if(ftell(historyf)==0){
		printf("\n Historico apagado com sucesso\n ");
		system("pause");
	}
	else{
		printf("\n Falha ao apagar historico!\n ");
		system("pause");
	}
	
	fclose(historyf);
}
