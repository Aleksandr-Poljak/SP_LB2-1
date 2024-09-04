﻿#include "framework.h"
#include "SP_LB2-1.h"
#include "Windows.h"

#define MAX_LOADSTRING 256

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

HANDLE ProcHandle[4] = { nullptr, nullptr, nullptr, nullptr };
DWORD ProcId[4] = { 0, 0, 0, 0 };
HANDLE ThreadHandle[4] = { nullptr, nullptr, nullptr, nullptr };
DWORD ThreadId[4] = { 0, 0, 0, 0 };
LPCTSTR ProcImage[4] = {
    nullptr,
    _T("C:\\Windows\\notepad.exe"),
    nullptr,
    TEXT("C:\\Windows\\System32\\calc.exe")
};
TCHAR CmdParam[4][260] = {
    TEXT(""),
    TEXT(""),
    _T("Notepad C:\\Users\\Alex\\Downloads\\GitHubLinks.txt"),
    TEXT("")
};



// Отправить объявления функций, включенных в этот модуль кода:
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

    wcscpy_s(szTitle, TEXT("SP-LB2-1 Poliak A. A. Gr. 30331-14"));
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SPLB21, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPLB21));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPLB21));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPLB21);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        switch (wmId)
        {
        case ID_PROCESSES_NOTEPAD:
        {
            SECURITY_ATTRIBUTES sap, sat;
            sat = createBaseScurityAttributes();
            sap = createBaseScurityAttributes();
            STARTUPINFO sti;
            ZeroMemory(&sti, sizeof(STARTUPINFO));
            sti.cb = sizeof(STARTUPINFO);
            STARTUPINFO* lpSti = &sti;
            PROCESS_INFORMATION pi;
            if (CreateProcess(ProcImage[1], nullptr, &sap, &sat, FALSE, 0, nullptr, nullptr, lpSti, &pi))
            {
                ProcHandle[1] = pi.hProcess;
                ProcId[1] = pi.dwProcessId;
                ThreadHandle[1] = pi.hThread;
                ThreadId[1] = pi.dwThreadId;
                /*CloseHandle(ProcHandle[1]);
                CloseHandle(ThreadHandle[1]);*/
            }
            else
            {
                MessageBox(NULL, _T("The \"Notepad\" thread was not created!"), _T("Error"), MB_OK);
            }
            break;
        }

        case ID_PROCESSES_NOTEPADWITHTEXT:
        {
            SECURITY_ATTRIBUTES sap, sat;
            sap = createBaseScurityAttributes();
            sat = createBaseScurityAttributes();
            STARTUPINFO sti;
            ZeroMemory(&sti, sizeof(STARTUPINFO));
            sti.cb = sizeof(STARTUPINFO);
            STARTUPINFO* lpSti = &sti;
            PROCESS_INFORMATION pi;
            if (CreateProcess(ProcImage[2], CmdParam[2], &sap, &sat, FALSE, 0, nullptr, nullptr, lpSti, &pi))
            {
                ProcHandle[2] = pi.hProcess;
                ProcId[1] = pi.dwProcessId;
                ThreadHandle[2] = pi.hThread;
                ThreadId[2] = pi.dwThreadId;
            }
            else
            {
                MessageBox(NULL, _T("The \"Notepad with text\" thread was not created!"), _T("Error"), MB_OK);
            }

            break;
        }

        case ID_PROCESSES_CALCULATOR:
        {
            SECURITY_ATTRIBUTES sap, sat;
            sap = createBaseScurityAttributes();
            sat = createBaseScurityAttributes();
            STARTUPINFO sti;
            ZeroMemory(&sti, sizeof(STARTUPINFO));
            sti.cb = sizeof(STARTUPINFO);
            STARTUPINFO* lpSti = &sti;
            PROCESS_INFORMATION pi;
            if (CreateProcess(ProcImage[3], nullptr, &sap, &sat, FALSE, 0, nullptr,
                nullptr, lpSti, &pi))
            {
                ProcHandle[3] = pi.hProcess;
                ProcId[3] = pi.dwProcessId;
                ThreadHandle[3] = pi.hThread;
                ThreadId[3] = pi.dwThreadId;
            }
            else
            {
                MessageBox(NULL, TEXT("The \"Calculator\" thread was not created!"), _T("Error"), MB_OK);
            }

            break;
        }

        case ID_PROCESSES_CLOSENOTEPAD:
        {
            if (ProcHandle[1] == NULL)
            {
                MessageBox(NULL, _T("Process handle is invalid!"), _T("Error"), MB_OK);
                break;
            }

            BOOL flag = TerminateProcess(ProcHandle[1], 0);
            if (!flag)
            {
                DWORD error = GetLastError();
                TCHAR msg[256];
                _stprintf_s(msg, _T("TerminateProcess failed with error code: %lu"), error);
                MessageBox(NULL, msg, _T("Error"), MB_OK);
            }
            else
            {
                MessageBox(NULL, _T("Process terminated successfully."), _T("Success"), MB_OK);
            }

            CloseHandle(ProcHandle[1]);
            ProcHandle[1] = NULL;
            break;
            
        }

        case IDM_ABOUT:
        {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        }

        case IDM_EXIT:
        {
            DestroyWindow(hWnd);
            break;
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);

        }
        break;
    }


    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);           
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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
