#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <string>

using namespace std;

void error_text_output() {

    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0,
        NULL
    );
    _tprintf(_T("Error is:%d-%s\n"), dw, (LPTSTR)lpMsgBuf);

    LocalFree(lpMsgBuf);
}

int _tmain(int argc, _TCHAR* argv[])
{
    HANDLE fh;
    string fileName;
    cout << "Enter file's name: ";
    getline(cin, fileName);
    fileName = fileName + ".txt";

    // string to LPCWSTR
    wstring stemp = wstring(fileName.begin(), fileName.end());
    LPCWSTR sw = stemp.c_str();


    fh = CreateFile(
        sw,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );


    if (fh == INVALID_HANDLE_VALUE) {
        error_text_output();
    }
    else {
        string content;
        DWORD w;

        cout << "Enter file's content: ";
        getline(cin, content);

        // string to char*
        const char* cContent = content.c_str();

        WriteFile(fh, cContent, content.length(), &w, NULL);
    }

    CloseHandle(fh);
    system("pause");
    return 0;
}