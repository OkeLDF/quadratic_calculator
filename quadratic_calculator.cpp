#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* PROTÓTIPOS: */
void menu ();

void insert (float *A, float *B, float *C);

void calcula (float A, float B, float C);

void limpa ();


/* MAIN: */
int main(){
    menu();
    return 0;
}


/* DEFINIÇÕES: */

void menu(){ /* Inicia o menu e possibilita as outras funções  */
    int r;
    float A=0, B=0, C=0;
    
    do{
        printf("\n ___ RAIZ DE EQUA. DE SEGUNDO GRAU ___\n");
        
        if(A==0 && B==0 && C==0) printf("\n\n > Nenhum coeficiente salvo\n");
        else printf("\n\n > %.0fx2 + %.0fx + %.0f = 0\n", A,B,C);
        
        printf("\n\n (1) Inserir Coeficientes.\n\n (2) Calcular Raizes.\n\n (3) Sair.\n\n\n R: ");
        scanf("%d",&r);
        
        switch(r){
            case 1: insert(&A,&B,&C); break;
                
            case 2: calcula(A,B,C); break;
            
            case 3: break;
                
            default: 
                printf("\n\n > Resposta invalida!\n\n ");
                limpa();
        }
        
    } while(r!=3);
}


void insert(float *A, float *B, float *C){ /* Insere os valores da A, B e C */
    system("cls");
    printf("\n\a > Insira os coeficientes da funcao, separado por espaco:\n\n ax2 + bx + c = 0\n\n R: ");
    scanf("%f %f %f", A, B, C);

    printf("\n > Coeficientes salvos!\n\n ");
    limpa();
    printf("\a");
}


void calcula(float A, float B, float C){ /* Calcula as raizes da Eq */
    float DELTA=(B*B)-(4*A*C);
    
    if(DELTA==0){ /* Discriminante nula => 1 raiz */
        printf("\n\n > X = %.2f\n\n > Delta = %.2f\n\n\n ", -B/(2*A), DELTA);        
    }
    else{
        if(DELTA<0){ /* Discriminante negativa => imposs�vel */
            printf("\n\n > Impossivel calucar a raiz! (discriminante = %.2f)\n\n\n ", DELTA);
        }
        else{ /* Discriminante positiva => 2 raizes, se A!=0 */
            if(A==0) printf("\n\n > X = %.2f\n\n\n ", -C/B);
            else printf("\n\n > X = %.2f  ou  X = %.2f\n\n > Delta = %.2f\n\n\n ", (sqrt(DELTA)-B)/(2*A), -(sqrt(DELTA)+B)/(2*A), DELTA);
        }
    }
    limpa();
}


void limpa (){ /* pausa, reseta cor e limpa */
    system("pause");
    //system("color 07");
    system("cls");
}
