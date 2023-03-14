#include "quadratic_calculator.h"

EQUATION insert_coefficients(){
	EQUATION eq;
	
    system("cls");
    printf("\n > Insira os coeficientes da funcao, separado por espaco:\n\n axý + bx + c = 0\n\n R: ");
    
	fflush(stdin);
	if(scanf("%f %f %f", &eq.A, &eq.B, &eq.C)!=3){
		printf("\n\n\a > Resposta invalida!");
		eq.A=0; eq.B=0; eq.C=0;
		CLOSE_MENU(1);
		return eq;
	}

    printf("\n > Coeficientes salvos!");
    CLOSE_MENU(2);
    return eq;
}


EQUATION find_roots(EQUATION eq){
    eq.DELTA = (eq.B*eq.B)-(4*eq.A*eq.C);
    eq.X1 = 0;
    eq.X2 = 0;
    eq.roots_qt = INVALID;
    
    if(eq.DELTA==0){
    	eq.X1 = -eq.B/(2*eq.A);
    	eq.X2 = eq.X1;
    	eq.roots_qt = 1;
		return eq;
    }
	
	if(eq.DELTA<0){
		eq.roots_qt = 0;
        return eq;
    }
    
    if(eq.A==0){
    	eq.X1 = -eq.C/eq.B;
    	eq.X2 = eq.X1;
    	eq.roots_qt = 1;	
		return eq;
	}
	
	eq.X1 = (sqrt(eq.DELTA)-eq.B)/(2*eq.A);
	eq.X2 = -(sqrt(eq.DELTA)+eq.B)/(2*eq.A);
	eq.roots_qt = 2;
	return eq;
}


void print_results(EQUATION eq){
	printf("\n\n > ");
	
    if(eq.DELTA==0){
    	printf("X = %.2f\n\n > Delta = %.2f", eq.X1, eq.DELTA);
		CLOSE_MENU(3);
		return;
    }
	
	if(eq.DELTA<0){
		printf("Impossivel calucar a raiz! (discriminante = %.2f) \a", eq.DELTA);
		CLOSE_MENU(2);
        return;
    }
    
    if(eq.A==0){
		printf("X = %.2f", eq.X1);
		CLOSE_MENU(3);		
		return;
	}
	
	printf("X = %.2f  ou  X = %.2f\n\n > Delta = %.2f", eq.X1, eq.X2, eq.DELTA);	
	CLOSE_MENU(3);
}
