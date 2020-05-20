#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

int main()
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;
    int Count = 0;
    int CountAll = 0;
    char Name[] = { "only_one.exe " };
    Name[11] = 0;
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
    int flag = 0;
    do
    {
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
        if (hProcess != NULL) {
            int i = 0;
            while (pe32.szExeFile[i] != 0) {
                if (pe32.szExeFile[i] != Name[i]) {
                    break;
                }
                if (i == 10) {
                    flag += 1;

                }
                i++;
            }

            Count += 1;
        }
        CountAll += 1;


    } while (Process32Next(hProcessSnap, &pe32));
    if (flag > 1) {
        printf("No-no-no! Close this program right now!\n");
        getchar();
    }
    else {

        printf("Hello!\n");
        getchar();
    }
    CloseHandle(hProcessSnap);
    return 0;
}
