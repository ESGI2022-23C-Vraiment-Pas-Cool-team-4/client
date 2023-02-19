#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

#include "includes/internal.h"
#include "includes/query.h"

#define HOTEL_WINDOW_WIDTH 720
#define HOTEL_WINDOW_HEIGTH 576

void displayLogin(HWND hHotel);
void RegisterLoginClass(HINSTANCE hInst);
void menus(HWND hHotel);
void buttons(HWND hHotel);
void RegisterReservationClass(HINSTANCE hInst);
void displayReservation(HWND hHotel);
void displayAdminWindow(HWND hHotel);
void RegisterAdminWindowClass(HINSTANCE hInst);


LRESULT CALLBACK LoginProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK HotelProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ReservationProcedure(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AdminWindowProcedure(HWND, UINT, WPARAM, LPARAM);

int ADMIN_ACCESS = 0;

HWND hHotelWindow, hUsername, hPassword, hReservationNew, hTypeRoom, hNumberStars, hDateArrival, hDateDeparture;
HMENU hMenuBar; 

enum AppMessages{
    LOGIN_BUTTON,
    RESERVATION_NEW,
    LOGOUT,
    SEARCH_RESERVATION_NEW,
    ADMIN_PART_ACCESS
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
        RegisterReservationClass(hInst);
        RegisterAdminWindowClass(hInst);

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
                    displayReservation(hHotel);
                    break;
                    break;
                case LOGOUT:
                    MessageBox(hHotel, "Info", "Log out", MB_OK | MB_ICONINFORMATION);
                    break;
                case ADMIN_PART_ACCESS:
                    if(!ADMIN_ACCESS){
                        MessageBoxW(hHotel, L"YOU DON'T HAVE ADMIN ACCESS", L"ERROR", MB_OK | MB_ICONERROR);
                    }else{
                        displayAdminWindow(hHotel);
                    }
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
                        if(login(username, password) == 2) ADMIN_ACCESS = 1;
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
    HMENU hUserMenu = CreateMenu();
    

    AppendMenu(hNewMenu, MF_STRING, RESERVATION_NEW, "New Reservation");

    AppendMenu(hUserMenu, MF_STRING, LOGOUT, "Logout");

    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR) hNewMenu, "New");
    AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR) hUserMenu, "User");
    AppendMenu(hMenuBar, MF_STRING, ADMIN_PART_ACCESS, "Admin");

    SetMenu(hHotel, hMenuBar);
}

void buttons(HWND hHotel){
    CreateWindowW(L"Button", L"New Reservation", WS_VISIBLE | WS_CHILD, 260, 60, 200, 50, hHotel, (HMENU)RESERVATION_NEW, NULL, NULL);
}






LRESULT CALLBACK ReservationProcedure(HWND hReserv, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_DESTROY:
            DestroyWindow(hReserv);
            break;

        case WM_COMMAND:
            switch(wp){
                case SEARCH_RESERVATION_NEW:;
                    query q;
                    q.nbParams = 4;
                    q.type = "searchReservation";
                    q.paramsName = malloc(sizeof(char*) * q.nbParams);
                    q.paramsValue = malloc(sizeof(char*) * q.nbParams);
                    for(int i = 0; i < q.nbParams; i++){
                        q.paramsValue[i] = malloc(sizeof(char) * 40);
                        q.paramsName[i] = malloc(sizeof(char) * 40);
                    }
                    q.paramsName[0] = "type_chambre";
                    GetWindowText(hTypeRoom, q.paramsValue[0], 40);
                    q.paramsName[1] = "nb_etoile";
                    GetWindowText(hNumberStars, q.paramsValue[1], 40);
                    q.paramsName[2] = "date_debut";
                    GetWindowText(hDateArrival, q.paramsValue[2], 40);
                    q.paramsName[3] = "date_fin";
                    GetWindowText(hDateDeparture, q.paramsValue[3], 40);
            }
            break;
        default:
            return DefWindowProcW(hReserv, msg, wp, lp);
    }
    return 0;
}

void RegisterReservationClass(HINSTANCE hInst){
        WNDCLASSW ReservationClass = {0};

	ReservationClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	ReservationClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	ReservationClass.hInstance = hInst;
	ReservationClass.lpszClassName = L"ReservationClass";
	ReservationClass.lpfnWndProc = ReservationProcedure;

    RegisterClassW(&ReservationClass);
}

void displayReservation(HWND hHotel){
    hReservationNew = CreateWindowW(L"ReservationClass", L"New Reservation", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 300, 800, hHotel, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Type of room (Basic, Luxurious, Suite)", WS_VISIBLE | WS_CHILD, 50, 50, 200, 30, hReservationNew, NULL, NULL, NULL);
    hTypeRoom = CreateWindowW(L"Edit", L"Basique", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 100, 200, 30, hReservationNew, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Number of stars (Between 0 and 5)", WS_VISIBLE | WS_CHILD, 50, 180, 200, 30, hReservationNew, NULL, NULL, NULL);
    hNumberStars = CreateWindowW(L"Edit", L"Simple", WS_VISIBLE | WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 200, 200, 30, hReservationNew, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Day of arrival (yyyy-mm-dd)", WS_VISIBLE | WS_CHILD, 50, 230, 200, 30, hReservationNew, NULL, NULL, NULL);
    hDateArrival = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 250, 200, 30, hReservationNew, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Day of departure (yyyy-mm-dd)", WS_VISIBLE | WS_CHILD, 50, 300, 200, 30, hReservationNew, NULL, NULL, NULL);
    hDateDeparture = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 320, 200, 30, hReservationNew, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Search", WS_VISIBLE | WS_CHILD, 100, 370, 100, 50, hReservationNew, (HMENU) SEARCH_RESERVATION_NEW, NULL, NULL);
    
}


LRESULT CALLBACK AdminWindowProcedure(HWND hAdmin, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_DESTROY:
            DestroyWindow(hAdmin);
            break;
        default:
            return DefWindowProcW(hAdmin, msg, wp, lp);
    }
}

void RegisterAdminWindowClass(HINSTANCE hInst){
    WNDCLASSW AdminWindowClass = {0};

	AdminWindowClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	AdminWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	AdminWindowClass.hInstance = hInst;
	AdminWindowClass.lpszClassName = L"AdminWindowClass";
	AdminWindowClass.lpfnWndProc = AdminWindowProcedure;

    RegisterClassW(&AdminWindowClass);
}

void displayAdminWindow(HWND hHotel){
    HWND hAdmin = CreateWindowW(L"AdminWindowClass", L"Admin Section", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 600, hHotel, NULL, NULL, NULL);
    CreateWindowW(L"Static", L"Add User", WS_VISIBLE | WS_CHILD, 100, 100, 100, 30, hAdmin, NULL, NULL, NULL);
    CreateWindowW(L"Edit", L"Username", WS_VISIBLE | WS_CHILD | WS_BORDER, 220, 100, 100, 30, hAdmin, NULL, NULL, NULL);
    CreateWindowW(L"Edit", L"Password", WS_VISIBLE | WS_CHILD | WS_BORDER, 340, 100, 100, 30, hAdmin, NULL, NULL, NULL);

}