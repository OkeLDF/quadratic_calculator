#include "quadratic_calculator.h"
#include "history.h"

#define LOG_ON 						\
	hy_request_user();				\
	hy_create_temp_history();		\
	hy_take_equation(2, &A, &B, &C)

int main(){
    int r; // 'r' é a variável padrão para a Resposta do usuário em menus
    float A = 0, B = 0, C = 0;
    FILE *historyf;
    
    LOG_ON;
    
    do{
        printf("\n ___ RAIZ DE EQUA. DE SEGUNDO GRAU ___\n");
        
        if(A==0 && B==0 && C==0) printf("\n\n > Nenhum coeficiente salvo\n");
        else printf("\n\n > %.0fx2 + %.0fx + %.0f = 0\n", A,B,C);
        
        printf("\n\n (1) Inserir Coeficientes.\n\n (2) Calcular Raizes.\n\n (3) Acessar Historico.\n\n (4) Trocar usuario.\n\n (5) Editar usuario.\n\n (0) Sair.\n\n\n R: ");
        scanf("%d",&r);
        
        switch(r){
            case 1: qc_insert_coefficients(&A, &B, &C); break;
                
            case 2: qc_find_roots(A,B,C); break;
            
            case 3: hy_access_history(&A,&B,&C); break;
            
            case 4: LOG_ON; break;
            
            case 5: if(hy_edit_user() == 1) LOG_ON; break;
            
            case 0: break;
                
            default: printf("\n\n\a > Resposta invalida!\n\n ");
        }
		        
    } while(r!=0);
    
    return 0;
}
