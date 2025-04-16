#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LINE 1024

void open_file(void);
void write_file(void);


int main() {
    setlocale(LC_ALL, "");
    // write_file();
    open_file();
    return 0;
}

void open_file(void)
{
    FILE* plik = fopen("rezerwacje.csv", "r");
    if (plik == NULL) {
        perror("Nie mo¿na otworzyæ pliku");
        return ;
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
}


void write_file(void)
{   
    FILE* plik = fopen("rezerwacje.csv", "a");
    if (plik == NULL) {
        perror("Nie mo¿na otworzyæ pliku");
        return ;
    }
    fprintf(plik, "6,Paulina,Maj,2025-04-23,10:00,12:00,102,Warsztaty\n");
    printf("Dodano rezerwacje!\n");
    fclose(plik);
}

