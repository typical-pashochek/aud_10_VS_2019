#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define MAX_FILENAME_LEN 260

int main(int argc, char* argv[])
{
    //setlocale(LC_ALL, "rus");
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;
    int Count = 0;
    int CountAll = 0;
    wchar_t* Name = (wchar_t*)malloc(MAX_FILENAME_LEN * sizeof(wchar_t));
    int Len = strlen(argv[0]);
    int i = Len;
    while (argv[0][i] != '\\') {
        i--;
    }
    for (int j = i + 1; j <= Len; j++) {
        Name[j - i - 1] = argv[0][j];
    }
    for (int i = 0; i < wcslen(Name); i++) {
        if ((int)Name[i] > 65472) {
            Name[i] = (wchar_t)((int)Name[i] - 65472 + 1040);
        }
    }
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
            if (!wcscmp(Name, pe32.szExeFile)) {
                flag++;
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
