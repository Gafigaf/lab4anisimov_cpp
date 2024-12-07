#include <windows.h>
#include <iostream>
#include <iomanip>
#include <aclapi.h>

void PrintFileAttributes(const wchar_t* filePath) {
    DWORD attributes = GetFileAttributes(filePath);
    if (attributes == INVALID_FILE_ATTRIBUTES) {
        std::wcerr << L"Failed to get file attributes" << std::endl;
        return;
    }

    std::wcout << L"Attributes: " << attributes << std::endl;
    std::wcout << ((attributes & FILE_ATTRIBUTE_HIDDEN) ? L"Hidden " : L"") << ((attributes & FILE_ATTRIBUTE_SYSTEM) ? L"System " : L"")
        << ((attributes & FILE_ATTRIBUTE_READONLY) ? L"Read-only " : L"") << std::endl;

    HANDLE hFile = CreateFile(filePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        std::wcerr << L"Failed to open file" << std::endl;
        return;
    }

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize)) {
        std::wcerr << L"Failed to get file size" << std::endl;
        CloseHandle(hFile);
        return;
    }
    std::wcout << L"Size: " << fileSize.QuadPart << L" bytes" << std::endl;

    FILETIME creationTime, lastAccessTime, lastWriteTime;
    if (!GetFileTime(hFile, &creationTime, &lastAccessTime, &lastWriteTime)) {
        std::wcerr << L"Failed to get file times" << std::endl;
        CloseHandle(hFile);
        return;
    }

    SYSTEMTIME st;
    FileTimeToSystemTime(&creationTime, &st);
    std::wcout << L"Creation Time: " << st.wDay << L"/" << st.wMonth << L"/" << st.wYear << L" " << st.wHour << L":" << st.wMinute << L":" << st.wSecond << std::endl;

    FileTimeToSystemTime(&lastAccessTime, &st);
    std::wcout << L"Last Access Time: " << st.wDay << L"/" << st.wMonth << L"/" << st.wYear << L" " << st.wHour << L":" << st.wMinute << L":" << st.wSecond << std::endl;

    FileTimeToSystemTime(&lastWriteTime, &st);
    std::wcout << L"Last Write Time: " << st.wDay << L"/" << st.wMonth << L"/" << st.wYear << L" " << st.wHour << L":" << st.wMinute << L":" << st.wSecond << std::endl;

    PSECURITY_DESCRIPTOR pSD = NULL;
    PSID pOwnerSID = NULL;
    BOOL bOwnerDefaulted = FALSE;
    if (GetSecurityInfo(hFile, SE_FILE_OBJECT, OWNER_SECURITY_INFORMATION, &pOwnerSID, NULL, NULL, NULL, &pSD) == ERROR_SUCCESS) {
        WCHAR ownerName[256];
        DWORD ownerNameSize = sizeof(ownerName) / sizeof(ownerName[0]);
        WCHAR domainName[256];
        DWORD domainNameSize = sizeof(domainName) / sizeof(domainName[0]);
        SID_NAME_USE eUse;
        if (LookupAccountSid(NULL, pOwnerSID, ownerName, &ownerNameSize, domainName, &domainNameSize, &eUse)) {
            std::wcout << L"Owner: " << domainName << L"\\" << ownerName << std::endl << "\n";
        }
        LocalFree(pSD);
    }

    CloseHandle(hFile);
}

int main() {
    PrintFileAttributes(L"text1.txt");
    PrintFileAttributes(L"text2.txt");
    PrintFileAttributes(L"100mb.txt");
    return 0;

}
