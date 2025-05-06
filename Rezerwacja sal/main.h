#ifndef MAIN_H
#define MAIN_H

#include <windows.h>

// Identyfikatory dialogów
#define IDD_ADD_RESERVATION 101
#define IDD_REMOVE_RESERVATION 102
#define IDD_FIND_RESERVATION 103

// Identyfikatory pól tekstowych w dialogach
#define IDC_FIRST_NAME 201
#define IDC_LAST_NAME 202
#define IDC_DATE 203
#define IDC_HOUR_START 204
#define IDC_HOUR_END 205
#define IDC_NUMBER 206
#define IDC_REASON 207
#define IDC_RESERVATION_ID 208

// Struktura rezerwacji
typedef struct reservation {
    int id;
    wchar_t first_name[50];
    wchar_t last_name[50];
    wchar_t date[11];
    wchar_t hour_start[6];
    wchar_t hour_end[6];
    wchar_t number[20];
    wchar_t reason[100];
} reservation;

// Deklaracje funkcji
void write_to_file(HWND hwnd);
void read_from_file(HWND hwnd);
void remove_from_file(HWND hwnd);
void find_reservation_by_id(HWND hwnd);
void clear_all_reservations(HWND hwnd); // Nowa funkcja

// Prototypy funkcji dialogowych
INT_PTR CALLBACK AddReservationDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK RemoveReservationDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

#endif // MAIN_H
