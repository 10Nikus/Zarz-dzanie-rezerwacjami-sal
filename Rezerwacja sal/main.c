#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LINE 1024

void open_file(void);
void write_file(void);
void menu(void);

int main() {
    setlocale(LC_ALL, "");
    menu();
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
    menu();
}


void write_file(void)
{   
    FILE* plik = fopen("rezerwacje.csv", "a");
    if (plik == NULL) {
        perror("Nie mo¿na otworzyæ pliku");
        return ;
    }
    printf("Podaj dane do rezerwacji:\n");
    char imie[20], nazwisko[20], data[10], godzina_p[5], godzina_k[5], numer_sali[5], cel[20];
    printf("Imie: ");
    scanf_s("%19s", imie, (unsigned)sizeof(imie));

    printf("Nazwisko: ");
    scanf_s("%19s", nazwisko, (unsigned)sizeof(nazwisko));

    printf("Data (YYYY-MM-DD): ");
    scanf_s("%10s", data, (unsigned)sizeof(data));

    printf("Godzina rozpoczêcia (HH:MM): ");
    scanf_s("%5s", godzina_p, (unsigned)sizeof(godzina_p));

    printf("Godzina zakoñczenia (HH:MM): ");
    scanf_s("%5s", godzina_k, (unsigned)sizeof(godzina_k));

    printf("Numer sali: ");
    scanf_s("%5s", numer_sali, (unsigned)sizeof(numer_sali));

    printf("Cel rezerwacji: ");
    scanf_s("%19s", cel, (unsigned)sizeof(cel));
    fprintf(plik, "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\"\n", imie, nazwisko, data, godzina_p, godzina_k, numer_sali, cel);
    printf("Dodano rezerwacje!\n");
    fclose(plik);
    menu();
}

void remove_from_file(void)
{
    printf("Deleted");
    menu();
}


void menu(void)
{
    int option;
    printf("Choose action:\n 1.Add Reservation\n 2.Remove reservation\n 3.Show reservations\n 4.Exit\n");
    scanf_s( "%d", &option);
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
