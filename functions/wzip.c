#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    int current_char;
    int prev_char = -1;
    int count = 0;

    for (int i = 1; i < argc; i++) {

        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        while ((current_char = fgetc(fp)) != EOF) {

            if (prev_char == -1) {
                prev_char = current_char;
                count = 1;
            }
            else if (current_char == prev_char) {
                count++;
            }
            else {
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&prev_char, sizeof(char), 1, stdout);

                prev_char = current_char;
                count = 1;
            }
        }

        fclose(fp);
    }

    if (prev_char != -1) {
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&prev_char, sizeof(char), 1, stdout);
    }

    return 0;
}