#include "framework.h"
#include "SP_LB2-1.h"
#include "Windows.h"

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


INT_PTR CALLBACK DlgInfo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // Информация о образе
        if (lParam == 0)
        {
            SetDlgItemText(hDlg, IDC_EDIT_ProcImage, _T("Current Proc"));
        }
        else
        {
            SetDlgItemText(hDlg, IDC_EDIT_ProcImage, ProcImage[lParam]);
        }

        // Дескриптор  
        TCHAR buff[200];
        wsprintf(buff, TEXT("(0x%08X)h (%d)d"),
            ProcHandle[lParam],
            ProcHandle[lParam]);
        SetDlgItemText(hDlg, IDC_EDIT_ProcHandle, buff);

        // Идентификатор 
        wsprintf(buff, TEXT("(0x%08X)h (%d)d"), ProcId[lParam], ProcId[lParam]);
        SetDlgItemText(hDlg, IDC_EDIT_ProcId, buff);

        // Код завершения процесса
        DWORD dwExitCode;
        if (!GetExitCodeProcess(ProcHandle[lParam], &dwExitCode))
            lstrcpy(buff, TEXT("Error! Invalid descriptor!"));
        else
        {
            if (dwExitCode == STILL_ACTIVE)
            {
                lstrcpy(buff, TEXT("Status – \"Active\""));
            }
            else
            {
                wsprintf(buff, TEXT("(0x%08X)h (%d) d"), dwExitCode, dwExitCode);
            }
        }
        SetDlgItemText(hDlg, IDC_EDIT_ExitCodeProc, buff);

        // Код завершения потока
        DWORD dwExitCodeThread;
        if (!GetExitCodeThread(ThreadHandle[lParam], &dwExitCodeThread))
            lstrcpy(buff, TEXT("Error! Invalid descriptor!"));
        else
        {
            if (dwExitCodeThread == STILL_ACTIVE)
            {
                lstrcpy(buff, TEXT("Status – \"Active\""));
            }
            else
            {
                wsprintf(buff, TEXT("(0x%08X)h (%d) d"), dwExitCodeThread, dwExitCodeThread);
            }
        }
        SetDlgItemText(hDlg, IDC_EDIT_ExitCodeThread, buff);

        // Идентификатор класса приоритета
        DWORD priorityClass = GetPriorityClass(ProcHandle[lParam]);
        wsprintf(buff, TEXT("(0x%08X)h"), priorityClass);
        SetDlgItemText(hDlg, IDC_EDIT_PropClass, buff);

        // а) время жизни процесса, время выполнения в режиме пользователя, 
        // время выполнения в режиме ядра, время простоя.
        FILETIME creationTime, exitTime, kernelTime, userTime;
        if (GetProcessTimes(ProcHandle[lParam], &creationTime, &exitTime, &kernelTime, &userTime))
        {
            SYSTEMTIME sysCreationTime;
            FileTimeToSystemTime(&creationTime, &sysCreationTime);
            wsprintf(buff, TEXT("%02d:%02d:%02d"), sysCreationTime.wHour, sysCreationTime.wMinute, sysCreationTime.wSecond);
            SetDlgItemText(hDlg, IDC_EDIT_CreationTime, buff);

            ULARGE_INTEGER userTimeMs;
            userTimeMs.LowPart = userTime.dwLowDateTime;
            userTimeMs.HighPart = userTime.dwHighDateTime;
            wsprintf(buff, TEXT("%lu ms"), userTimeMs.QuadPart / 10000);
            SetDlgItemText(hDlg, IDC_EDIT_ExitTime, buff);

            ULARGE_INTEGER kernelTimeMs;
            kernelTimeMs.LowPart = kernelTime.dwLowDateTime;
            kernelTimeMs.HighPart = kernelTime.dwHighDateTime;
            wsprintf(buff, TEXT("%lu ms"), kernelTimeMs.QuadPart / 10000);
            SetDlgItemText(hDlg, IDC_EDIT_KernelTime, buff);

            ULARGE_INTEGER idleTimeMs;
            idleTimeMs.QuadPart = userTimeMs.QuadPart + kernelTimeMs.QuadPart;
            wsprintf(buff, TEXT("%lu ms"), idleTimeMs.QuadPart / 10000);
            SetDlgItemText(hDlg, IDC_EDIT_UserTime, buff);
        }
        else
        {
            lstrcpy(buff, TEXT("Error when obtaining process time characteristics!"));
            SetDlgItemText(hDlg, IDC_EDIT_CreationTime, buff);
            SetDlgItemText(hDlg, IDC_EDIT_ExitTime, buff);
            SetDlgItemText(hDlg, IDC_EDIT_KernelTime, buff);
            SetDlgItemText(hDlg, IDC_EDIT_UserTime, buff);
        }

        return (INT_PTR)FALSE;
        break;
    }

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDOK:
            EndDialog(hDlg, wmId);
            return (INT_PTR)TRUE;
        case IDCANCEL:
            EndDialog(hDlg, wmId);
            return (INT_PTR)TRUE;
        default:
            break;
        }
        break;
    }
    }
    return (INT_PTR)FALSE;
}
