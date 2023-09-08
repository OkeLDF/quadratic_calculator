#include "quadratic_calculator.h"

void qc_insert_coefficients(float *A, float *B, float *C){ /* Insere os valores da A, B e C */
    system("cls");
    printf("\n > Insira os coeficientes da funcao, separado por espaco:\n\n axý + bx + c = 0\n\n R: ");
    scanf("%f %f %f", A, B, C);

    printf("\n > Coeficientes salvos!");
    CLOSE_MENU(2);
}


void qc_find_roots(float A, float B, float C){ /* Calcula as raizes da Eq */
    float DELTA=(B*B)-(4*A*C);
    EQ_INFO equation;
    
    equation.A = A;
    equation.B = B;
    equation.C = C;
    equation.DELTA = DELTA;
    equation.X1 = 0;
    equation.X2 = 0;
    equation.roots_qt = -1;
    
    printf("\n\n > ");
    
    // CASO: 1 raiz
    if(DELTA==0){
    	equation.X1 = -B/(2*A);
    	equation.roots_qt = 1;
    	
        printf("X = %.2f\n\n > Delta = %.2f", equation.X1, DELTA);
		hy_save_on_history(equation);
		
		CLOSE_MENU(3);
		return;    
    }
	
	// CASO: impossível
	if(DELTA<0){
		printf("Impossivel calucar a raiz! (discriminante = %.2f) \a", DELTA);
		equation.roots_qt = 0;
        hy_save_on_history(equation);
        
        CLOSE_MENU(2);
        return;
    }
    
	// CASO: 1 raiz
    if(A==0){
    	equation.X1 = -C/B;
    	equation.roots_qt = 1;
    	
		printf("X = %.2f", equation.X1);
		hy_save_on_history(equation);
		
		CLOSE_MENU(3);		
		return;
	}
	
	// CASO: 2 raizes
	equation.X1 = (sqrt(DELTA)-B)/(2*A);
	equation.X2 = -(sqrt(DELTA)+B)/(2*A);
	equation.roots_qt = 2;
	
	printf("X = %.2f  ou  X = %.2f\n\n > Delta = %.2f", equation.X1, equation.X2, DELTA);
	hy_save_on_history(equation);
	
	CLOSE_MENU(3);
}

