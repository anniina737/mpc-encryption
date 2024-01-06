
#pragma once

#include <cwchar>
#include <iostream>


#define BufferSize 1024
class DoMediaDecrypt
{
public:
    // ��̬��������ȡ����ʵ��
    static DoMediaDecrypt* getInstance() {
        // ���ʵ�������ڣ�����һ����ʵ��
        if (instance == nullptr) {
            instance = new DoMediaDecrypt();
        }
        return instance;
    }

    void Init(LPCWSTR lpcwstrFileName);
    bool DoRevise(HANDLE hFile, LPVOID lpBuffer, DWORD dwSize);

private:    
    WCHAR szFileName[MAX_PATH];
    byte buffer[BufferSize];
    // ˽�й��캯����ȷ������ֱ��ʵ����
    DoMediaDecrypt() {
        // ��ʼ������
        std::cout << "Singleton instance created." << std::endl;
    }

    // ��̬��Ա�������洢Ψһʵ��
    static DoMediaDecrypt* instance;
};

// ��ʼ����̬��Ա����
DoMediaDecrypt* DoMediaDecrypt::instance = nullptr;
