#include "stdafx.h"
#include "MediaEncrypt.h"

void DoMediaDecrypt::Init(LPCWSTR lpcwstrFileName)
{
    wcscpy(szFileName, lpcwstrFileName);
    lpcwstrFileName = L"d:\\prefix.bin";
    auto hFile = CreateFileW(lpcwstrFileName, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, (HANDLE)nullptr);
    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD n = 0;
        // TODO: decode from 
        ReadFile(hFile, this->buffer, 1024, &n, 0);
        CloseHandle(hFile);
    }

    return;
}

bool DoMediaDecrypt::DoRevise(HANDLE hFile, LPVOID lpBuffer, DWORD dwSize)
{
    // check filename of hFile
    WCHAR szFilePath[MAX_PATH];
    GetFinalPathNameByHandleW(hFile, (LPWSTR)&szFilePath, MAX_PATH, FILE_NAME_NORMALIZED);
    if (0 == wcscmp(szFilePath, this->szFileName)) {
        LARGE_INTEGER liDistanceToMove;
        LARGE_INTEGER liNewFilePointer;
        liDistanceToMove.QuadPart = 0;  // ����ڵ�ǰλ���ƶ�0�ֽ�
        if (SetFilePointerEx(hFile, liDistanceToMove, &liNewFilePointer, FILE_CURRENT)) {
            // �滻Ŀ�����Ǵ�0��ʼƫ��
            if (liNewFilePointer.QuadPart < BufferSize) {
                int reviseSize = dwSize;
                if (dwSize + liNewFilePointer.QuadPart > BufferSize) {
                    reviseSize = BufferSize - liNewFilePointer.QuadPart;
                }
                memcpy(lpBuffer, (byte*)(this->buffer) + liNewFilePointer.QuadPart, reviseSize);
                return true;
            }
        }
    }
    return false;
}
