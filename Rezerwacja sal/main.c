#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h> 


void read_from_file(void);
void write_to_file(void);
void menu(void);
void remove_from_file(void);
void find_reservation_by_id(void);
void find_reservation_by_date(void);

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
    struct reservation res;
    int id_to_delete;
    printf("Input id reservation to delete: ");
    scanf_s("%i", &id_to_delete);

    getchar();

    char agree;
    printf("Are you sure you want to delete reservation with id %i? (y/n): ", id_to_delete);
    scanf_s("%c", &agree, sizeof(agree));
    if (tolower(agree) == 'y') {


        FILE* file = fopen("reservation.bin", "rb");
        if (file == NULL) {
            printf("Error! opening file");
            exit(1);
        }

        FILE* temp_file = fopen("temp_reservation.bin", "wb");
        if (temp_file == NULL) {
            printf("Error! opening file");
            fclose(file);
            exit(1);
        }

        while (fread(&res, sizeof(res), 1, file))
        {
            if (id_to_delete != res.id)
            {
                fwrite(&res, sizeof(res), 1, temp_file);
            }
        }
        fclose(file);
        fclose(temp_file);

        remove("reservation.bin");
        rename("temp_reservation.bin", "reservation.bin");
        printf("Record with ID %d deleted successfully.\n", id_to_delete);
    }
    else
    {
        printf("Operation cancelled\n");
    }
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
    FILE* file = fopen( "reservation.bin", "rb");
    if (file == NULL) {
        printf("Error! opening file");
        exit(1);
    }
 

    struct reservation res;

    int last_id = -1;

    while (fread(&res, sizeof(res), 1, file) == 1) {
        last_id = res.id;
    }
    
    if (last_id == -1) {
        last_id = 0;
    }

    res.id = ++last_id;

    fclose(file);

    printf("Enter first name: ");
    scanf_s("%49s", res.first_name, (unsigned)_countof(res.first_name));

    printf("Enter last name: ");
    scanf_s("%49s", res.last_name, (unsigned)_countof(res.last_name));

    printf("Enter date (DD.MM.YYYY): ");
    scanf_s("%10s", res.date, (unsigned)_countof(res.date));

    printf("Enter start time (HH:MM):");
    scanf_s("%5s", res.hour_start, (unsigned)_countof(res.hour_start));

    printf("Enter end time (HH:MM): ");
    scanf_s("%5s", res.hour_end, (unsigned)_countof(res.hour_end));

    printf("Enter the number of room (123): ");
    scanf_s("%5s", res.number, (unsigned)_countof(res.number));

    printf("Enter reason for reservation: ");
    scanf_s("%99s", res.reason, (unsigned)_countof(res.reason));


    file = fopen("reservation.bin", "rb");
    if (file == NULL) {
        printf("Error! opening file\n");
        exit(1);
    }

    struct reservation temp;
    int is_taken = 0;

    while (fread(&temp, sizeof(temp), 1, file) == 1) {
        if (strcmp(temp.date, res.date) == 0 && strcmp(temp.number, res.number) == 0) {
            if (!(strcmp(res.hour_end, temp.hour_start) <= 0 || strcmp(res.hour_start, temp.hour_end) >= 0)) {
                is_taken = 1;
                break;
            }
        }
    }

    fclose(file);

    if (is_taken) {
        printf("\nERROR: Room %s is already reserved on %s between %s and %s\n",
            temp.number, temp.date, temp.hour_start, temp.hour_end);
        printf("Reservation not saved.\n\n");
    }
    else {
        file = fopen("reservation.bin", "ab");
        if (file == NULL) {
            printf("Error! opening file\n");
            exit(1);
        }

        int flag = fwrite(&res, sizeof(res), 1, file);

        if (!flag) {
            printf("Write Operation Failure\n");
        }
        else {
            printf("Write Operation Successful\n");
        }

        fclose(file);
    }
    menu();
}

void find_reservation_by_id(void)
{
    int id;
    int found = 0;
    printf("Id reservation to find: ");
    scanf_s("%i", &id);
    FILE* file = fopen("reservation.bin", "rb");
    if (file == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    struct reservation res;

    while (fread(&res, sizeof(res), 1, file))
    {
        if (res.id == id)
        {
            printf("%i, %s, %s, %s, %s, %s, %s, %s\n",
                res.id,
                res.first_name,
                res.last_name,
                res.date,
                res.hour_start,
                res.hour_end,
                res.number,
                res.reason);
            found = 1;
        }
    }
    if (!found) printf("Reservation not found!\n");
    fclose(file);
    menu();
}

void find_reservation_by_date(void)
{
    struct reservation res;
    char date[11];
    int found = 0;
    printf("Date reservation to find: ");
    scanf_s("%s", &date, sizeof(res.date));
    FILE* file = fopen("reservation.bin", "rb");
    if (file == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    while (fread(&res, sizeof(res), 1, file))
    {
        if (strcmp(date, res.date) == 0)
        {
            printf("%i, %s, %s, %s, %s, %s, %s, %s\n",
                res.id,
                res.first_name,
                res.last_name,
                res.date,
                res.hour_start,
                res.hour_end,
                res.number,
                res.reason);
            found = 1;
        }
    }
    if (!found) printf("Reservation not found!\n");
    fclose(file);
    menu();
}

void menu(void)
{
    int option;
    printf("Choose action:\n 1.Add Reservation\n 2.Remove reservation\n 3.Show all reservations\n 4.Find reservation by id \n 5.Find reservation by date\n 6.Exit\n");
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
        find_reservation_by_id();
        break;
    case 5:
        find_reservation_by_date();
        break;
    case 6:
        return;

    default:
        break;
    }
}