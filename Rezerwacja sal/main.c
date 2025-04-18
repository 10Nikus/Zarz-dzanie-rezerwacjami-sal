#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_LINE 1024

void open_file(void);
void write_file(void);


int main() {
    setlocale(LC_ALL, "");
    write_file();
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
    FILE* plik = NULL;
    errno_t err = fopen_s(&plik, "rezerwacje.csv", "r");
    if (err != 0 || plik == NULL) {
        perror("Nie mo¿na otworzyæ pliku");
        return;
    }

    char linia[MAX_LINE];
    int last_id = 0;

        while (fgets(linia, MAX_LINE, plik)) {
            linia[strcspn(linia, "\n")] = 0;

            char* context = NULL;
            char* kolumna = strtok_s(linia, ",", &context);
            if (kolumna != NULL) {
                int current_id = atoi(kolumna);
                if (current_id > last_id) {
                    last_id = current_id;
                }
            }
        }

    fclose(plik);

    int new_id = last_id + 1;

    // Sprawdzenie czy nowe ID jest poprawne
    printf("Nowe ID: %d\n", new_id);

    err = fopen_s(&plik, "rezerwacje.csv", "a");
    if (err != 0 || plik == NULL) {
        perror("Nie mo¿na otworzyæ pliku");
        return;
    }
 
    // Trzeba zmodyfikowaæ na pobieranie danych od u¿ytkownika - na razie wpisane na sztywno
    fprintf(plik, "6,Barbara,Williams,2025-04-23,10:00,12:00,102,Warsztaty\n");
    printf("Dodano rezerwacje!\n");

    fclose(plik);
}

