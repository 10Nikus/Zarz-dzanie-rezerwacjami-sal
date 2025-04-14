#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LINE 1024

int main() {
    setlocale(LC_ALL, "");
    FILE* plik = fopen("rezerwacje.csv", "r");
    if (plik == NULL) {
        perror("Nie mo¿na otworzyæ pliku");
        return 1;
    }

    char linia[MAX_LINE];

    while (fgets(linia, MAX_LINE, plik)) {
        linia[strcspn(linia, "\n")] = 0;

        char* context = NULL;
        char* kolumna = strtok_s(linia, ",", &context);
        while (kolumna != NULL) {
            printf("%s\t", kolumna);
            kolumna = strtok_s(NULL, ",", &context);
        }
        printf("\n");
    }

    fclose(plik);
    return 0;
}
