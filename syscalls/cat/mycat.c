/**
 * cat using regular C code.
 */
#include <stdio.h>

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        int c;
        FILE *file;
        file = fopen(argv[i], "r");
        if (file) {
            while ((c = getc(file)) != EOF)
                putchar(c);
            fclose(file);
        }
    }
}
