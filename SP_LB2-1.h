#pragma once

#include "resource.h"
#include <Windows.h>

// ��� ������������ ���������;
extern HANDLE ProcHandle[4]; 

//��� ��������������� ���������;
extern DWORD ProcId[4]; 

//��� ������������ �������;
extern HANDLE ThreadHandle[4]; 

//��� ��������������� �������;
extern DWORD ThreadId[4];  

//��� ���������� �����, ��������������� ����� ����������� ��������;
extern LPCTSTR ProcImage[4];

//��� ����� c ����������� ����������� ��������.
extern TCHAR CmdParam[4][260];  

/// <summary>/// 
/// ���������� ������ ��������� SECURITY_ATTRIBUTES,
/// ������������������ � �������� ���������� �� ���������. 
/// </summary>///
/// <returns>
/// SECURITY_ATTRIBUTES
/// </returns>
SECURITY_ATTRIBUTES createBaseScurityAttributes();

/// <summary>
/// ������� ��������� ����������� ���� � ���������.
/// </summary>
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

/// <summary>
/// ������� ��������� ����������� ���� ���������� � ���������
/// </summary>
INT_PTR CALLBACK DlgInfo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

/// <summary>
/// ������ ���������� TestProc
/// </summary>
void StartTestPocApp();