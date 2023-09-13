#include "security.h"

FILE* get_file(char filename[], const char* mode){
	FILE* fp = fopen(filename, mode);
	char r[2];
	
	if(fp) return fp;
	printf("\n > Erro ao abrir arquivo: '%s'!\n\n Deseja criar o arquivo %s? (s/n): ", filename, filename);
	fflush(stdin);
	fgets(r, sizeof(r), stdin);
	
	switch(r[0]){
		case 's':
		case 'S':
		case 'y':
		case 'Y':
		case '1':
			fclose(fp);
			fp = fopen(filename, "w");
			fclose(fp);
			fp = fopen(filename, mode);
			return fp;
			
		default:
			exit(2);
	}
}
