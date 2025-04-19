#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LINE 1024
#define _CRT_SECURE_NO_WARNINGS

void read_from_file(void);
void write_to_file(void);
void menu(void);
void remove_from_file(void);


typedef struct reservation {
    int id;
    char first_name[50];
    char last_name[50];
    char date[11];
    char hour_start[6];
    char hour_end[6];
    char number[20];
    char reason[100];
};

int main() {
    menu();
    return 0;
}



void remove_from_file(void)
{
    printf("Deleted");
    menu();
}

void read_from_file(void)
{
    FILE * file = fopen("reservation.bin", "rb");
    if (file == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    struct reservation res;

    while (fread(&res, sizeof(res), 1, file)){
        printf("%i, %s, %s, %s, %s, %s, %s, %s\n", 
            res.id, 
            res.first_name, 
            res.last_name, 
            res.date, 
            res.hour_start, 
            res.hour_end, 
            res.number,
            res.reason);
    }
    fclose(file);
    menu();
}


void write_to_file(void)
{
    FILE* file = fopen( "reservation.bin", "ab");
    if (file == NULL) {
        printf("Error! opening file");

        exit(1);
    }
   
    int flag = 0;

    struct reservation res;
    

    printf("Enter ID: ");
    scanf_s("%d", &res.id);

    printf("Enter first name: ");
    scanf_s("%49s", res.first_name, (unsigned)_countof(res.first_name));

    printf("Enter last name: ");
    scanf_s("%49s", res.last_name, (unsigned)_countof(res.last_name));

    printf("Enter date (DD.MM.YYYY): ");
    scanf_s("%10s", res.date, (unsigned)_countof(res.date));

    printf("Enter start time (HH:MM): ");
    scanf_s("%5s", res.hour_start, (unsigned)_countof(res.hour_start));

    printf("Enter end time (HH:MM): ");
    scanf_s("%5s", res.hour_end, (unsigned)_countof(res.hour_end));

    printf("Enter the number of room (123):");
    scanf_s("%5s", res.number, (unsigned)_countof(res.number));

    printf("Enter reason for reservation: ");
    scanf_s("%99s", res.reason, (unsigned)_countof(res.reason));

    flag = fwrite(&res, sizeof(res), 1, file);

    if (!flag) {
        printf("Write Operation Failure\n");
    }
    else {
        printf("Write Operation Successful\n");
    }

    fclose(file);
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
        write_to_file();
        break;
    case 2:
        remove_from_file();
        break;
    case 3:
        read_from_file();
        break;
    case 4:
        return;

    default:
        break;
    }

}