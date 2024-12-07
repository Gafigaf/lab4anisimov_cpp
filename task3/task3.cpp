#include <windows.h>
#include <iostream>
#include <vector>

#define FILE_COUNT 3
const wchar_t* fileNames[FILE_COUNT] = { L"text1.txt", L"text2.txt", L"100mb.txt" };

void async_read_files() {
    HANDLE hFiles[FILE_COUNT];
    OVERLAPPED overlapped[FILE_COUNT] = { 0 };
    char buffers[FILE_COUNT][1024];

    for (int i = 0; i < FILE_COUNT; ++i) {
        hFiles[i] = CreateFile(fileNames[i], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
        if (hFiles[i] == INVALID_HANDLE_VALUE) {
            std::wcerr << L"Failed to open file: " << fileNames[i] << std::endl;
            return;
        }

        overlapped[i].hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (!ReadFile(hFiles[i], buffers[i], sizeof(buffers[i]), NULL, &overlapped[i])) {
            if (GetLastError() != ERROR_IO_PENDING) {
                std::wcerr << L"Failed to start read operation" << std::endl;
                CloseHandle(hFiles[i]);
                return;
            }
        }
    }

    WaitForMultipleObjects(FILE_COUNT, reinterpret_cast<const HANDLE*>(&overlapped), TRUE, INFINITE);

    for (int i = 0; i < FILE_COUNT; ++i) {
        DWORD bytesRead;
        if (GetOverlappedResult(hFiles[i], &overlapped[i], &bytesRead, TRUE)) {
            std::wcout << L"Read " << bytesRead << L" bytes from " << fileNames[i] << std::endl;
        }
        else {
            std::wcerr << L"Failed to complete read operation" << std::endl;
        }
        CloseHandle(hFiles[i]);
    }
}

int main() {
    async_read_files();
    return 0;
}
