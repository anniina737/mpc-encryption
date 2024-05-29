#pragma once

#include <windows.h>

#ifdef MEDIA_ENCRYPT_EXPORTS
#define MEDIA_ENCRYPT_API __declspec(dllexport)
#else
#define MEDIA_ENCRYPT_API __declspec(dllimport)
#endif

//
// #define BufferSize 1024
#define EncryptFlag 0x4F434E45
#define AesAlign 1024

class MEDIA_ENCRYPT_API Cmedia_encrypt {
public:
	Cmedia_encrypt() {
		this->setMaxCoverSize(2*1024*1024);
	}

	~Cmedia_encrypt() {
		if (this->ptrData != nullptr) {
			delete[] this->ptrData;
		}
	}

	int Init(LPCWSTR lpcwstrFileName, LPCSTR key);
	bool DoRevise(HANDLE hFile, int, LPVOID lpBuffer, DWORD dwSize);
	
	bool DoEncrypt(LPCWSTR lpcwstrFileName, LPCSTR key, LPCSTR new_key);
	bool DoEncryptFile(HANDLE hFile);
	bool getCoverInfo(HANDLE hFile, unsigned int* offsetData, unsigned int* dwData, unsigned int* keyLength);
	void setCoverInfo(unsigned char* coverMp4, int coverMp4Size);
	void setMaxCoverSize(int maxCoverSize);

private:
	WCHAR szFileName[MAX_PATH];
	unsigned char* coverMp4;
	int coverMp4Size;
	int maxCoverSize;
	char* ptrData = nullptr;
	unsigned int dwDataSize = 0;
	unsigned int offsetData = 0;
};

extern MEDIA_ENCRYPT_API int nmedia_encrypt;

MEDIA_ENCRYPT_API int fnmedia_encrypt(void);

Cmedia_encrypt* GlobalEncodeInst = nullptr;
