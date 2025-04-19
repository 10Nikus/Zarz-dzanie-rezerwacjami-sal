#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LINE 1024

void open_file(void);
void write_file(void);
void menu(void);
void remove_from_file(void);


int main() {
    setlocale(LC_ALL, "");
    menu();
    return 0;
}



void remove_from_file(void)
{
    printf("Deleted");
    menu();
}

void open_file(void)
{
    FILE* plik = fopen("rezerwacje.csv", "r");
    if (plik == NULL) {
        perror("Nie mo¿na otworzyæ pliku");
        return;
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
    menu();
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

    char imie[50], nazwisko[50], data[15], godz_od[6], godz_do[6], sala[10], typ[50];

    printf("Podaj imiê: ");
    scanf("%20s", imie);

    printf("Podaj nazwisko: ");
    scanf("%20s", nazwisko);

    printf("Podaj datê (RRRR-MM-DD): ");
    scanf("%20s", data);

    printf("Godzina rozpoczêcia (HH:MM): ");
    scanf("%5s", godz_od);

    printf("Godzina zakoñczenia (HH:MM): ");
    scanf("%5s", godz_do);

    printf("Sala: ");
    scanf("%3s", sala);

    printf("Typ wydarzenia: ");
    scanf("%20s", typ);


    err = fopen_s(&plik, "rezerwacje.csv", "a");
    if (err != 0 || plik == NULL) {
        perror("Nie mo?na otworzy? pliku");
        return;
    }

    fprintf(plik, "%d,%s,%s,%s,%s,%s,%s,%s\n", new_id, imie, nazwisko, data, godz_od, godz_do, sala, typ);
    printf("Dodano rezerwacj? z ID %d!\n", new_id);

    fclose(plik);

    menu();
}



void menu(void)
{
    int option;
    printf("Choose action:\n 1.Add Reservation\n 2.Remove reservation\n 3.Show reservations\n 4.Exit\n");
    scanf_s("%d", &option);
    switch (option)
    {
    case 1:
        write_file();
        break;
    case 2:
        remove_from_file();
        break;
    case 3:
        open_file();
        break;
    case 4:
        return;

    default:
        break;
    }

}