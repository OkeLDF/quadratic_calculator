#include <stdlib.h>
#include <stdio.h>

#include "types_and_macros.h"
#include "quadratic_calculator.h"
#include "history.h"
#include "login.h"
#include "menus.h"

int main(){
	EQUATION eq, *lastops_history;
	USER current_user;
	char list_of_users[] = "user_list.dad";
    int r; // 'r' é a variável padrão para a Resposta do usuário em menus
    
    sign_up_menu(&current_user, list_of_users);
    eq = take_equation(1, current_user.history);
    
    do{
        printf("\n ___ RAIZ DE EQUA. DE SEGUNDO GRAU ___\n");        
        
        if(eq.A==0 && eq.B==0 && eq.C==0) printf("\n\n > Nenhum coeficiente salvo\n");
        else printf("\n\n > %.0fxý + %.0fx + %.0f = 0\n", eq.A, eq.B, eq.C);
		
		printf("\n\n (1) Inserir Coeficientes.\n\n (2) Calcular Raizes.\n\n (3) Acessar Historico.\n\n (4) Trocar usuario.\n\n (5) Editar usuario.\n\n (0) Sair.\n\n\n R: ");
        fflush(stdin);
		if(scanf("%d",&r)==0) r=-1;
        
        switch(r){
            case 1: eq = insert_coefficients(); break;
                
            case 2: 
				eq = find_roots(eq);
				print_results(eq);
				save_on_history(eq, current_user.history, lastops_history);
				break;
            
            case 3: access_history_menu(&eq, current_user.history); break;
            
            case 4: 
				sign_up_menu(&current_user, list_of_users); 
				eq = take_equation(1, current_user.history);
				break;
            
            case 5: 
				if(user_info_menu(&current_user, list_of_users)==USER_REMOVED){
					sign_up_menu(&current_user, list_of_users); 
					eq = take_equation(1, current_user.history);
				} 
				break;
            
            case 0: break;
                
            default: INVALID_ANS; break;
        }
		        
    } while(r!=0);
    
    return 0;
}
