#pragma once

#include "resource.h"
#include <Windows.h>

// Для дескрипторов процессов;
extern HANDLE ProcHandle[4]; 

//Для идентификаторов процессов;
extern DWORD ProcId[4]; 

//Для дескрипторов потоков;
extern HANDLE ThreadHandle[4]; 

//Для идентификаторов потоков;
extern DWORD ThreadId[4];  

//Для указателей строк, идентифицирущих файлы запускаемых программ;
extern LPCTSTR ProcImage[4];

//Для строк c параметрами запускаемых программ.
extern TCHAR CmdParam[4][260];  

/// <summary>/// 
/// Возвращает объект структуры SECURITY_ATTRIBUTES,
/// инициализированный с базовыми значениями по умолчанию. 
/// </summary>///
/// <returns>
/// SECURITY_ATTRIBUTES
/// </returns>
SECURITY_ATTRIBUTES createBaseScurityAttributes();