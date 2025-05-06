#include <windows.h>
#include <stdio.h> // Dodano dla FILE, fopen_s, fclose
#include "main.h"

// Identyfikatory przycisków
#define BTN_ADD 1
#define BTN_REMOVE 2
#define BTN_SHOW 3
#define BTN_FIND_ID 4
#define BTN_EXIT 5
#define BTN_CLEAR_ALL 6 // Nowy przycisk

// Funkcja obs³uguj¹ca komunikaty okna
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case BTN_ADD:
            write_to_file(hwnd); // Wywo³anie funkcji dodawania rezerwacji
            break;
        case BTN_REMOVE:
            remove_from_file(hwnd); // Wywo³anie funkcji usuwania rezerwacji
            break;
        case BTN_SHOW:
            read_from_file(hwnd); // Wywo³anie funkcji wyœwietlania wszystkich rezerwacji
            break;
        case BTN_FIND_ID:
            find_reservation(hwnd); // Wywo³anie dialogu wyszukiwania rezerwacji po ID
            break;
        case BTN_CLEAR_ALL:
            clear_all_reservations(hwnd); // Wywo³anie funkcji usuwania wszystkich rezerwacji
            break;
        case BTN_EXIT:
            PostQuitMessage(0); // Zakoñczenie programu
            break;
        }
        break;

    case WM_CREATE:
        // Tworzenie przycisków
        CreateWindow(L"BUTTON", L"Add Reservation", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 50, 300, 30, hwnd, (HMENU)BTN_ADD, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        CreateWindow(L"BUTTON", L"Remove Reservation", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 90, 300, 30, hwnd, (HMENU)BTN_REMOVE, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        CreateWindow(L"BUTTON", L"Show All Reservations", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 130, 300, 30, hwnd, (HMENU)BTN_SHOW, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        CreateWindow(L"BUTTON", L"Find Reservation by ID", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 170, 300, 30, hwnd, (HMENU)BTN_FIND_ID, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        CreateWindow(L"BUTTON", L"Delete All Reservations", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 210, 300, 30, hwnd, (HMENU)BTN_CLEAR_ALL, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        CreateWindow(L"BUTTON", L"Exit", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 250, 300, 30, hwnd, (HMENU)BTN_EXIT, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        break;

    case WM_DESTROY:
        PostQuitMessage(0); // Zakoñczenie programu
        return 0;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// Procedura dialogowa dla "Wyszukaj Rezerwacjê"
INT_PTR CALLBACK FindReservationDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            find_reservation_by_id(hDlg); // Wywo³anie funkcji wyszukiwania rezerwacji po ID
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// Funkcja wywo³uj¹ca dialog "Wyszukaj Rezerwacjê"
int find_reservation(HWND hwnd) {
    return (int)DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_FIND_RESERVATION), hwnd, FindReservationDialogProc);
}

// Funkcja usuwaj¹ca wszystkie rezerwacje
void clear_all_reservations(HWND hwnd) {
    FILE* file = NULL; // Deklaracja wskaŸnika na plik
    errno_t err = fopen_s(&file, "reservations.txt", "w"); // Otwórz plik w trybie zapisu
    if (err != 0) {
        MessageBox(hwnd, L"Failed to open the file to delete reservations!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Zamknij plik, co usuwa jego zawartoœæ
    fclose(file);

    MessageBox(hwnd, L"All reservations have been deleted!", L"Success", MB_OK | MB_ICONINFORMATION);
}

// Funkcja g³ówna
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"ReservationWindow";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, L"Failed to register the window class", L"Error", MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Room Reservation System",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 420, 360,
        NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, L"Failed to create the window!", L"Error", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
