#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "includes/internal.h"

#define HOTEL_WINDOW_WIDTH 720
#define HOTEL_WINDOW_HEIGTH 576

void displayLogin(HWND hHotel);
void RegisterLoginClass(HINSTANCE hInst);
void menus(HWND hHotel);
void buttons(HWND hHotel);

LRESULT CALLBACK LoginProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HotelProcedure(HWND, UINT, WPARAM, LPARAM);

HWND hHotelWindow, hUsername, hPassword;
HMENU hMenuBar; 

enum AppMessages{
    LOGIN_BUTTON,
    RESERVATION_NEW,
    SEARCH_HOTEL,
    SEARCH_ROOM,
    SEARCH_RESERVATION,
    LOGOUT
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
            buttons(hHotel);
            menus(hHotel);
            displayLogin(hHotel);
            break;
        case WM_COMMAND:
            switch(wp){
                case RESERVATION_NEW:
                    MessageBox(hHotel, "Info", "New Reservation", MB_OK | MB_ICONINFORMATION);
                    break;
                case SEARCH_HOTEL:
                    MessageBox(hHotel, "Info", "Search Hotel", MB_OK | MB_ICONINFORMATION);
                    break;
                case SEARCH_ROOM:
                    MessageBox(hHotel, "Info", "Search Room", MB_OK | MB_ICONINFORMATION);
                    break;
                case SEARCH_RESERVATION:
                    MessageBox(hHotel, "Info", "Search Reservation", MB_OK | MB_ICONINFORMATION);
                    break;
                case LOGOUT:
                    MessageBox(hHotel, "Info", "Log out", MB_OK | MB_ICONINFORMATION);
                    break;
            }
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
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_DESTROY:
            DestroyWindow(hLogin);
            break;
        case WM_COMMAND:
            switch(wp){
                case LOGIN_BUTTON:;
                    char username[40], password[40];
                    GetWindowText(hUsername, username, 40);
                    GetWindowText(hPassword, password, 40);
                    loginLabel: if(login(username, password)){
                        EnableWindow(hHotelWindow, TRUE);
                        DestroyWindow(hLogin);
                    } else{
                        int val = MessageBoxW(hLogin, L"Login failed !", L"ERROR", MB_CANCELTRYCONTINUE | MB_ICONERROR);
                        switch(val){
                            case IDTRYAGAIN:
                                goto loginLabel;
                                break;
                            case IDCANCEL:
                                PostQuitMessage(0);
                            case IDCONTINUE:
                                break;
                        }
                    }
                    break;
            }
            break;
        default:
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

void menus(HWND hHotel){
    hMenuBar = CreateMenu();
    HMENU hNewMenu = CreateMenu();
    HMENU hSearchMenu = CreateMenu();
    HMENU hUserMenu = CreateMenu();

    AppendMenu(hNewMenu, MF_STRING, RESERVATION_NEW, "New Reservation");
    AppendMenu(hNewMenu, MF_POPUP, (UINT) hSearchMenu, "Search");

    AppendMenu(hSearchMenu, MF_STRING, SEARCH_HOTEL, "Hotel");
    AppendMenu(hSearchMenu, MF_STRING, SEARCH_ROOM, "Room");
    AppendMenu(hSearchMenu, MF_STRING, SEARCH_RESERVATION, "Reservation");

    AppendMenu(hUserMenu, MF_STRING, LOGOUT, "Logout");

    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR) hNewMenu, "New");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR) hUserMenu, "User");

    SetMenu(hHotel, hMenuBar);
}

void buttons(HWND hHotel){
    CreateWindowW(L"Button", L"New Reservation", WS_VISIBLE | WS_CHILD, 260, 60, 200, 50, hHotel, (HMENU)RESERVATION_NEW, NULL, NULL);
    CreateWindowW(L"Button", L"Search Hotel", WS_VISIBLE | WS_CHILD, 260, 150, 200, 50, hHotel, (HMENU)SEARCH_HOTEL, NULL, NULL);
    CreateWindowW(L"Button", L"Search Room", WS_VISIBLE | WS_CHILD, 260, 240, 200, 50, hHotel, (HMENU)SEARCH_ROOM, NULL, NULL);
    CreateWindowW(L"Button", L"Search Reservation", WS_VISIBLE | WS_CHILD, 260, 330, 200, 50, hHotel, (HMENU)SEARCH_RESERVATION, NULL, NULL);
}