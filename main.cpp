#include "quadratic_calculator.h"
#include "history.h"

int main(){ /* Inicia o menu */
    int r;
    float A = 0, B = 0, C = 0;
    FILE *historyf;
    
    hy_create_temp_history();
    hy_take_equation(2, &A, &B, &C);
    
    do{
        printf("\n ___ RAIZ DE EQUA. DE SEGUNDO GRAU ___\n");
        
        if(A==0 && B==0 && C==0) printf("\n\n > Nenhum coeficiente salvo\n");
        else printf("\n\n > %.0fx2 + %.0fx + %.0f = 0\n", A,B,C);
        
        printf("\n\n (1) Inserir Coeficientes.\n\n (2) Calcular Raizes.\n\n (3) Acessar Historico.\n\n (0) Sair.\n\n\n R: ");
        scanf("%d",&r);
        
        switch(r){
            case 1: qc_insert(&A, &B, &C); break;
                
            case 2: qc_find_roots(A,B,C); break;
            
            case 3: hy_access_history(&A,&B,&C); break;
            
            case 0: break;
                
            default: printf("\n\n\a > Resposta invalida!\n\n ");
        }
		        
    } while(r!=0);
    
    return 0;
}
