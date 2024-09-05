#include "SP_LB2-1.h";

SECURITY_ATTRIBUTES createBaseScurityAttributes()
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = nullptr;
	sa.bInheritHandle = FALSE;
	
	return sa;
}

void StartTestPocApp()
{
    SECURITY_ATTRIBUTES sap, sat;
    sap = createBaseScurityAttributes();
    sat = createBaseScurityAttributes();
    STARTUPINFO sti;
    ZeroMemory(&sti, sizeof(STARTUPINFO));
    sti.cb = sizeof(STARTUPINFO);
    sti.dwFlags = STARTF_USEPOSITION | STARTF_USESIZE;
    sti.dwX = 300;
    sti.dwY = 300;
    sti.dwXSize = 300;
    sti.dwYSize = 500;
    STARTUPINFO* lpSti = &sti;
    PROCESS_INFORMATION pi;
    LPCTSTR TestProcPath = TEXT("D:\\Learning\\programming\\c++_projects\\SP_LB2-1\\x64\\Debug\\TestProc.exe");
    if (!CreateProcess(TestProcPath, nullptr, &sap, &sat, FALSE, 0, nullptr, nullptr, lpSti, &pi))
    {
        MessageBox(NULL, TEXT("The \"TestProc\" thread was not created!"), TEXT("Error"), MB_OK);
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}
