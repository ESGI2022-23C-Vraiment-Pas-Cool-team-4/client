#include <windows.h>
#include <stdlib.h>

#include "includes/internal.h"

#define HOTEL_WINDOW_WIDTH 720
#define HOTEL_WINDOW_HEIGTH 576

void displayLogin(HWND hHotel);
void RegisterLoginClass(HINSTANCE hInst);

LRESULT CALLBACK LoginProcedure(HWND hHotel, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK HotelProcedure(HWND, UINT, WPARAM, LPARAM);

HWND hHotelWindow, hUsername, hPassword;

enum AppMessages{
    LOGIN_BUTTON
};

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){
	
    WNDCLASSW HotelClass = {0};

	HotelClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	HotelClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	HotelClass.hInstance = hInst;
	HotelClass.lpszClassName = L"HotelClass";
	HotelClass.lpfnWndProc = HotelProcedure;

	if (!RegisterClassW(&HotelClass)) return -1;
        RegisterLoginClass(hInst);

		hHotelWindow = CreateWindowW(L"HotelClass", L"Hotel Manager", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, HOTEL_WINDOW_WIDTH, HOTEL_WINDOW_HEIGTH, NULL, NULL, NULL, NULL);

	    MSG msg = {0};

    while(GetMessage(&msg, NULL, NULL, NULL)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}

LRESULT CALLBACK HotelProcedure(HWND hHotel, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_CREATE:
            displayLogin(hHotel);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hHotel, msg, wp, lp);
    }
    return 0;
}

void RegisterLoginClass(HINSTANCE hInst){

    WNDCLASSW LoginClass = {0};

	LoginClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	LoginClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	LoginClass.hInstance = hInst;
	LoginClass.lpszClassName = L"LoginClass";
	LoginClass.lpfnWndProc = LoginProcedure;

    RegisterClassW(&LoginClass);
}

LRESULT CALLBACK LoginProcedure(HWND hLogin, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_DESTROY:
            DestroyWindow(hLogin);
            EnableWindow(hHotelWindow, TRUE);
            break;
        case WM_COMMAND:
            switch(wp){
                case LOGIN_BUTTON:;
                    char username[40], password[40], print[80];
                    GetWindowText(hUsername, username, 40);
                    GetWindowText(hPassword, password, 40);
                    if(login(username, password))
                        MessageBoxW( hLogin, L"ok", L"ok", MB_OK);
                    else
                        MessageBoxW( hLogin, L"No", L"No", MB_OK);
            }
            break;
        default:
            EnableWindow(hHotelWindow, TRUE);
            return DefWindowProcW(hLogin, msg, wp, lp);
    }
    return 0;
}

void displayLogin(HWND hHotel){
    HWND hLogin = CreateWindowW(L"LoginClass", L"Login", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 260, 238, 400, 300, hHotel, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Username : ", WS_VISIBLE | WS_CHILD, 100,10,200,30,hLogin,NULL,NULL,NULL);
    hUsername = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 50, 200, 30, hLogin, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Password : ", WS_VISIBLE | WS_CHILD, 100,100,200,30,hLogin,NULL,NULL,NULL);
    hPassword = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 100, 140, 200, 30, hLogin, NULL, NULL, NULL);
    CreateWindowW(L"Button", L"Log In", WS_VISIBLE | WS_CHILD, 150, 200, 100, 50, hLogin, (HMENU) LOGIN_BUTTON, NULL, NULL);
    EnableWindow(hHotel, FALSE);
}