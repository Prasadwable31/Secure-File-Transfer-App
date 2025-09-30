#include "pch.h"                    // pre compiler header

#include<windows.h>

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>   
#include<io.h>
#include <sys/stat.h>

#define MAX_SIZE 1024


// Caesar Cipher
extern "C" __declspec(dllexport) void Encrypt_Caesar_Cipher(char*, char*, int);

void Encrypt_Caesar_Cipher(char* Scr, char* Dest, int Key)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0;
    char Buffer[MAX_SIZE] = { '\0' };

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = (Buffer[i] + Key) % 256;
        }

        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

extern "C" __declspec(dllexport) void Decrypt_Caesar_Cipher(char*, char*, int);

void Decrypt_Caesar_Cipher(char* Scr, char* Dest, int Key)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0;
    char Buffer[MAX_SIZE] = { '\0' };

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = (Buffer[i] - Key) % 256;
        }

        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

// XOR Cipher
extern "C" __declspec(dllexport) void Encrypt_XOR_Cipher(char*, char*, char);

void Encrypt_XOR_Cipher(char* Scr, char* Dest, char Key)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0;
    char Buffer[MAX_SIZE] = { '\0' };

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }


    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = Buffer[i] ^ Key;
        }

        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

extern "C" __declspec(dllexport) void Decrypt_XOR_Cipher(char*, char*, char);

void Decrypt_XOR_Cipher(char* Scr, char* Dest, char Key)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0;
    char Buffer[MAX_SIZE] = { '\0' };

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }


    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = Buffer[i] ^ Key;
        }

        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

// Vigenere Cipher
extern "C" __declspec(dllexport) void Encrypt_Vigenere_Cipher(char*, char*, char*);

void Encrypt_Vigenere_Cipher(char* Scr, char* Dest, char* Key)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0, j = 0;
    int keyLen = strlen(Key);
    char Buffer[MAX_SIZE] = { '\0' };

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = (Buffer[i] + Key[j % keyLen]) % 256;
            j++;
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

extern "C" __declspec(dllexport) void Decrypt_Vigenere_Cipher(char*, char*, char*);

void Decrypt_Vigenere_Cipher(char* Scr, char* Dest, char* Key)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0, j = 0;
    int keyLen = strlen(Key);
    char Buffer[MAX_SIZE] = { '\0' };

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = (Buffer[i] - Key[j % keyLen]) % 256;
            j++;
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

// Vigenere XOR Cipher
extern "C" __declspec(dllexport) void Encrypt_Vigenere_XOR_Cipher(char*, char*, char*);

void Encrypt_Vigenere_XOR_Cipher(char* Scr, char* Dest, char* Key)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0, j = 0;
    int keyLen = strlen(Key);
    char Buffer[MAX_SIZE] = { '\0' };

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = Buffer[i] ^ Key[j % keyLen];
            j++;
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

extern "C" __declspec(dllexport) void Decrypt_Vigenere_XOR_Cipher(char*, char*, char*);

void Decrypt_Vigenere_XOR_Cipher(char* Scr, char* Dest, char* Key)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0, j = 0;
    int keyLen = strlen(Key);
    char Buffer[MAX_SIZE] = { '\0' };

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            Buffer[i] = Buffer[i] ^ Key[j % keyLen];
            j++;
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

// Reverse Cipher (Custom)
extern "C" __declspec(dllexport) void Encrypt_Reverse_Cipher(char*, char*);

void Encrypt_Reverse_Cipher(char* Scr, char* Dest)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0, j = 0;
    char ch = '\0';
    char Buffer[MAX_SIZE] = { '\0' };

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0, j = iRet-1; i < j; i++, j--)
        {   
            ch = Buffer[i];
            Buffer[i] = Buffer[j];
            Buffer[j] = ch;
        }
        _write(fdDest, Buffer, iRet);
    }


    _close(fdSrc);
    _close(fdDest);
}

extern "C" __declspec(dllexport) void Decrypt_Reverse_Cipher(char*, char*);

void Decrypt_Reverse_Cipher(char* Scr, char* Dest)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0, j = 0;
    char ch = '\0';
    char Buffer[MAX_SIZE] = { '\0' };

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0, j = iRet-1; i < j; i++, j--)
        {   
            ch = Buffer[i];
            Buffer[i] = Buffer[j];
            Buffer[j] = ch;
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

// Substitution Cipher
extern "C" __declspec(dllexport) void Encrypt_Substitution_Cipher(char*, char*);

void Encrypt_Substitution_Cipher(char* Scr, char* Dest)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0, j = 0;
    char Buffer[MAX_SIZE] = { '\0' };
    char Key[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }

    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            if (Buffer[i] >= 'A' && Buffer[i] <= 'Z')      // Uppercase
            {
                Buffer[i] = Key[Buffer[i] - 'A'];
            }
            else if (Buffer[i] >= 'a' && Buffer[i] <= 'z') // Lowercase
            {
                Buffer[i] = tolower(Key[Buffer[i] - 'a']);
            }
            // else keep as it is (digits, spaces, symbols)
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}

extern "C" __declspec(dllexport) void Decrypt_Substitution_Cipher(char*, char*);

void Decrypt_Substitution_Cipher(char* Scr, char* Dest)
{
    int fdSrc = 0, fdDest = 0;
    int iRet = 0, i = 0, j = 0;
    char Buffer[MAX_SIZE] = { '\0' };
    char RevKey[26] = {'\0'};
    char Key[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    if (_sopen_s(&fdSrc, Scr, _O_RDONLY | _O_BINARY, _SH_DENYNO, 0) != 0)
    {
        printf("Unable to open source file\n");
        _close(fdSrc);
        return;
    }

    if (_sopen_s(&fdDest, Dest, _O_WRONLY | _O_CREAT | _O_TRUNC | _O_BINARY, _SH_DENYNO, _S_IREAD | _S_IWRITE) != 0)
    {
        printf("Unable to open destination file\n");
        _close(fdDest);
        return;
    }

    for (i = 0; i < 26; i++)
    {
        RevKey[Key[i] - 'A'] = 'A' + i;
    }

    while ((iRet = _read(fdSrc, Buffer, MAX_SIZE)) > 0)
    {
        for (i = 0; i < iRet; i++)
        {
            if (Buffer[i] >= 'A' && Buffer[i] <= 'Z')
            {
                Buffer[i] = RevKey[Buffer[i] - 'A'];
            }
            else if (Buffer[i] >= 'a' && Buffer[i] <= 'z')
            {
                Buffer[i] = tolower(RevKey[Buffer[i] - 'a']);
            }
        }
        _write(fdDest, Buffer, iRet);
    }

    _close(fdSrc);
    _close(fdDest);
}