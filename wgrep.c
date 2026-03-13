#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void  lines_reader(const char *term, FILE *file);

int main(int argc, char *argv[]){

	/*Validación en caso de que se especifiquen archivos*/
	if (argc == 1) {
		printf("wgrep: searchterm [file...]\n");
		return 1;
	}

	/*Tomar termino de busqueda*/
	const char *searchterm = argv[1];

	if (argc == 2) {
		printf("Introduce texto (presiona Ctrl+D para terminar): \n");
		lines_reader(searchterm, stdin);
	}

	/*Iteración de argumentos*/
	for (int i = 2; i < argc; i++){
		/*Lectura de archivo*/
		FILE *fp = fopen(argv[i], "r");
		/*Validación de lectura*/
		if (fp == NULL) {
			printf("wgrep: cannot open file\n");
			return 1;
		}
		lines_reader(searchterm, fp);
		fclose(fp);
	}
	return 0;
}

void lines_reader(const char *term, FILE *file) {
	char *line = NULL;
	size_t tam = 0;
	ssize_t bytes_reader;

	/*Iteración sobre lineas*/
	while ((bytes_reader = getline(&line, &tam, file)) != -1) {
		/*Verificación termino contenido*/
		if (strstr(line, term) != NULL) {
			printf("%s", line); /*Imprime linea si contiene termino*/
		}
	}
	free(line);
}
