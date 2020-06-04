#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>

int main()
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;
    int Count = 0;
    int CountAll = 0;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        _tprintf(TEXT("\nWARNING: CreateToolhelp32Snapshot (of processes) failed with error %d ()"), GetLastError());
        exit(1);
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32))
    {
        _tprintf(TEXT("\nWARNING: Process32First failed with error %d ()"), GetLastError());
        CloseHandle(hProcessSnap);
        exit(1);
    }
    do
    {
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
        if (hProcess != NULL) {
            int what;
            WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), pe32.szExeFile, wcslen(pe32.szExeFile), &what, 0);
            printf("\n");
            //_tprintf(TEXT("\nProcess ID = %d\t%s"), pe32.th32ProcessID, pe32.szExeFile);

            Count += 1;
        }
        else {
            //_tprintf(TEXT("\n%s"), pe32.szExeFile);
            _tprintf(TEXT("Process ID = %d\tWARNING: OpenProcess failed with error %d ()\n"), pe32.th32ProcessID, GetLastError());
        }
        CountAll += 1;

    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    printf("\nGet access to %d  from %d processes...", Count, CountAll);
    system("pause");
    return 0;
}
