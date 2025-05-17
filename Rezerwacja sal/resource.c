#include <windows.h>
#include <stdio.h>
#include "resource.h"

// Identyfikatory przycisków
#define BTN_ADD 1
#define BTN_EXIT 5

// --- PROTOTYPY ---
INT_PTR CALLBACK AddReservationDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// --- G£ÓWNE OKNO ---
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case BTN_ADD:
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ADD_RESERVATION), hwnd, AddReservationDialogProc);
            break;
        case BTN_EXIT:
            PostQuitMessage(0);
            break;
        }
        break;

    case WM_CREATE:
        CreateWindow(L"BUTTON", L"Add Reservation", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 50, 200, 30, hwnd, (HMENU)BTN_ADD, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        CreateWindow(L"BUTTON", L"Exit", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            50, 90, 200, 30, hwnd, (HMENU)BTN_EXIT, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

// --- DIALOG: Add Reservation ---
INT_PTR CALLBACK AddReservationDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDOK: {
            wchar_t name[256];
            GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 256);

            FILE* file = NULL;
            errno_t err = _wfopen_s(&file, L"reservations.txt", L"a+, ccs=UTF-8");
            if (err == 0 && file != NULL) {
                fwprintf(file, L"%s\n", name);
                fclose(file);
                MessageBox(hDlg, L"Reservation added!", L"Success", MB_OK | MB_ICONINFORMATION);
            }
            else {
                MessageBox(hDlg, L"Error saving reservation.", L"Error", MB_OK | MB_ICONERROR);
            }

            EndDialog(hDlg, IDOK);
            return (INT_PTR)TRUE;
        }
        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// --- FUNKCJA G£ÓWNA ---
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
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 320, 200,
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
