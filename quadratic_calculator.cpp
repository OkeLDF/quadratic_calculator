#include "quadratic_calculator.h"
#include "history.h"

void qc_insert(float *A, float *B, float *C){ /* Insere os valores da A, B e C */
    system("cls");
    printf("\n > Insira os coeficientes da funcao, separado por espaco:\n\n axý + bx + c = 0\n\n R: ");
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
		hy_save_on_history(equation);      
    }
    else{
    	if(DELTA<0){ /* Discriminante negativa => impossível */
    		printf("\n\n\a > Impossivel calucar a raiz! (discriminante = %.2f)\n\n\n ", DELTA);
            hy_save_on_history(equation);
        }
        else{ /* Discriminante positiva => 2 raizes, se A!=0 */
            if(A==0){
            	equation.X1 = -C/B;
            	equation.roots_qt = 1;
            	
				printf("\n\n > X = %.2f\n\n\n ", equation.X1);
				hy_save_on_history(equation);
			}
            else{
            	equation.X1 = (sqrt(DELTA)-B)/(2*A);
            	equation.X2 = -(sqrt(DELTA)+B)/(2*A);
            	equation.roots_qt = 2;
            	
				printf("\n\n > X = %.2f  ou  X = %.2f\n\n > Delta = %.2f\n\n\n ", equation.X1, equation.X2, DELTA);
				hy_save_on_history(equation);
			}
        }
    }
    
    system("pause");
    system("cls");
}



