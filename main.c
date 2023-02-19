#include <windows.h>

LRESULT CALLBACK HotelProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow){
	
    WNDCLASSW HotelClass = {0};

	HotelClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	HotelClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	HotelClass.hInstance = hInst;
	HotelClass.lpszClassName = L"HotelClass";
	HotelClass.lpfnWndProc = HotelProcedure;

	if (!RegisterClassW(&HotelClass)) return -1;

		CreateWindowW(L"HotelClass", L"Hotel Manager", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 720, 576, NULL, NULL, NULL, NULL);

	    MSG msg = {0};

    while(GetMessage(&msg, NULL, NULL, NULL)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}

LRESULT CALLBACK HotelProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp){
    switch(msg){
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}