#include <stdio.h>
int main(int argc, char *argv[]){
	/*Validación  en caso que no se especifiquen archivos*/
	if (argc == 1){
		return 1;
	}
	/*Iteración de argumentos*/
	for (int i = 1; i < argc; i++){
		/*Lectura de archivo*/
		FILE *fp = fopen(argv[i], "r");
		/*Validación de lectura*/
		if (fp == NULL){
			printf("wcat: cannot open file\n");
			return 1;
		}
		/*Capacidad de carácteres a imprimir por secuencia*/
		char buffer[60];
		while (fgets(buffer, 60, fp) != NULL) {
			printf("%s", buffer);
		}
		fclose(fp);
	}
	return 0;
}

