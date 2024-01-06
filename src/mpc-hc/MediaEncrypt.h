
#pragma once

#include <cwchar>
#include <iostream>


#define BufferSize 1024
class DoMediaDecrypt
{
public:
    // 静态方法，获取单例实例
    static DoMediaDecrypt* getInstance() {
        // 如果实例不存在，创建一个新实例
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
    // 私有构造函数，确保不能直接实例化
    DoMediaDecrypt() {
        // 初始化代码
        std::cout << "Singleton instance created." << std::endl;
    }

    // 静态成员变量，存储唯一实例
    static DoMediaDecrypt* instance;
};

// 初始化静态成员变量
DoMediaDecrypt* DoMediaDecrypt::instance = nullptr;
