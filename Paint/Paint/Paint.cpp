// Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Paint.h"
#include"Shape.h"
#include<vector>
#include <windowsx.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")

#include <Objbase.h>
#pragma comment(lib, "Ole32.lib")
#include "RibbonFramework.h"
#include "RibbonIDs.h"
using namespace MyShape;
using namespace Gdiplus;
//using namespace std;
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

	CoInitialize(NULL);
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PAINT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	CoUninitialize();
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0;// CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PAINT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = 0;//MAKEINTRESOURCEW(IDC_PAINT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
POINT start, End;
bool keepMouse = false;
bool keepShift = false;
std::vector<CShape*> shapes;
int choose = 0;
CShape *Shape;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		InitializeFramework(hWnd);
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
		break;
	case WM_LBUTTONDOWN:
		{
			keepMouse = true;
			start.x = LOWORD(lParam);
			start.y = HIWORD(lParam);
			switch (choose) {
				case 1:
					Shape = new CRectangle();
					break;
				case 2:
					Shape = new CEllipse();
					break;
				default:
					Shape = new CLine();
					break;
			}
			break;
		}
	case WM_LBUTTONUP:														
		{
			End.x = LOWORD(lParam);
			End.y = HIWORD(lParam);
			Shape->SetData(start, End, keepShift);
			shapes.push_back(Shape);
			InvalidateRect(hWnd, NULL, TRUE);
			keepMouse = false;
			break;
		}
	case WM_MOUSEMOVE:
		{
			if (keepMouse) {
				
				End.x = LOWORD(lParam);
				End.y = HIWORD(lParam);
				Shape->SetData(start, End, keepShift);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			}
		}
	case WM_KEYDOWN:
		{
			if (0x8000 & GetKeyState(VK_SHIFT)) {
				keepShift = true;
			}
		}
	case WM_KEYUP:
		{
			if (!(0x8000 & GetKeyState(VK_SHIFT))) {
				keepShift = false;
			}
		}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case ID_SHAPE_LINE:
				choose = 0;
				break;
			case ID_SHAPE_RECTANGLE:
				choose = 1;
				break;
			case ID_SHAPE_ELLIPSE:
				choose = 2;
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			Gdiplus::Graphics* graphics = new Gdiplus::Graphics(hdc);
			int lineWidth = 3;
			Pen* pen = new Pen(Color(255, 0, 0, 0), lineWidth);
			for (int i = 0; i < shapes.size(); i++) {
				shapes[i]->Draw(hdc, graphics, pen);
			}

			if (keepMouse) {
				Shape->Draw(hdc, graphics, pen);
			}
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
		DestroyFramework();
		GdiplusShutdown(gdiplusToken);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
