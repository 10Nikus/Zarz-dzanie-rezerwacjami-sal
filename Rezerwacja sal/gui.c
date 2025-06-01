#include "gui.h"
#include <windows.h>

// Deklaracje funkcji
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void create_button(HWND hwnd);

// Okno aplikacji
void create_gui(HINSTANCE hInstance) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "ReservationAppClass";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        "Reservation App",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// Funkcja obs³uguj¹ca komunikaty okna
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE:
        create_button(hwnd);
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            MessageBox(hwnd, "Add Reservation button clicked!", "Info", MB_OK);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Funkcja tworz¹ca przycisk
void create_button(HWND hwnd) {
    CreateWindow(
        "BUTTON",  // Klasa przycisku
        "Add Reservation",  // Tekst przycisku
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Style
        50, 50, 200, 40,  // Pozycja i rozmiar
        hwnd, (HMENU)1, GetModuleHandle(NULL), NULL);
}
