#include "MyString.h"
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

#define MYSTRING_FORMAT_BUFFER_SIZE 0x1000



int MyString::s_count = 1;

MyString& MyString::Copy(const char *pszBuf, int length)
{
    if (GetBufSize() <= length)
    {
        if (c_str() != nullptr && s_count == 0)
        {
            delete[] m_pszBuf;
            SetBuf(nullptr);
        }
        SetBuf(new char[length + 1]);
        SetLength(length);
        SetBufSize(length + 1);
    }
    strcpy(GetBuf(), pszBuf);
    return *this;
}

MyString& MyString::Append(const char *pszBuf, int length)
{
    length = length + GetLength();
    char* pBuf = nullptr;
    if (GetBufSize() <= length)
    {
        if (c_str() != nullptr && s_count == 0)
        {
            pBuf = new char[length + 1];
            strcpy(pBuf, GetBuf());
            delete[] m_pszBuf;
            SetBuf(nullptr);
        }
        SetBuf(pBuf);
        SetLength(length);
        SetBufSize(length + 1);
    }
    strcat(GetBuf(), pszBuf);
    return *this;
}

int MyString::IndexOf(const char* pszBuf, int length)
{
    for (int i = 0; i < GetLength(); i++)
    {
        if (strncmp(c_str() + i, pszBuf, length) == 0)
            return i;
    }
    return -1;
}



int MyString::GetBufSize()
{
    return m_bufSize;
}

void MyString::SetBufSize(int bufSize)
{
    m_bufSize = bufSize;
}

char* MyString::GetBuf()
{
    return m_pszBuf;
}

void MyString::SetBuf(char *pszBuf)
{
    m_pszBuf = pszBuf;
}

void MyString::SetLength(int length)
{
    m_length = length;
}



MyString::MyString()
{
    SetBuf("");
    SetLength(0);
    SetBufSize(1);
}

MyString::MyString(const char *pszBuf)
{
    int length = strlen(pszBuf);
    SetBuf(new char[length + 1]);
    strcpy(GetBuf(), pszBuf);
    SetLength(length);
    SetBufSize(length + 1);
}

MyString::MyString(MyString& obj)
{
    SetBuf(obj.GetBuf());
    SetLength(obj.GetLength());
    SetBufSize(obj.GetBufSize());
    s_count++;
}

MyString::~MyString()
{
    s_count--;
    if (c_str() != nullptr && s_count == 0)
    {
        delete[] m_pszBuf;
        SetBuf(nullptr);
    }
}



int MyString::GetLength()
{
    return m_length;
}

int MyString::Length()
{
    return GetLength();
}

const char* MyString::c_str()
{
    return GetBuf();
}



MyString& MyString::Copy(MyString& obj)
{
    return Copy(obj.c_str(), obj.GetLength());
}

MyString& MyString::Copy(const char *pszBuf)
{
    return Copy(pszBuf, strlen(pszBuf));
}

MyString& MyString::Append(MyString& obj)
{
    return Append(obj.c_str(), obj.GetLength());
}

MyString& MyString::Append(const char *pszBuf)
{
    return Append(pszBuf, strlen(pszBuf));
}

int MyString::Split(char *pszBuf, const char *pszDelimiter, char* pszOutStrings[], int count)
{
    int i = 0;
    char *pszToken = strtok(pszBuf, pszDelimiter);
    for (i = 0; pszToken != NULL && i < count; i++)
    {
        strcpy(pszOutStrings[i], pszToken);
        pszToken = strtok(NULL, pszDelimiter);
    }
    return i;
}

int MyString::Split(const char *pszDelimiter, MyString pOutStrings[], int count)
{
    int i = 0;
    char *pszToken = strtok(GetBuf(), pszDelimiter);
    for (i = 0; pszToken != NULL && i < count; i++)
    {
        (pOutStrings + i)->Copy(pszToken);
        pszToken = strtok(NULL, pszDelimiter);
    }
    return i;
}

void MyString::Format(const char* pszFormat, ...)
{
    char szBuff[MYSTRING_FORMAT_BUFFER_SIZE] = "";
    va_list args;
    va_start(args, pszFormat);
    vsnprintf(szBuff, sizeof(szBuff), pszFormat, args);
    va_end(args);
    Copy(szBuff);
}

int MyString::IndexOf(MyString& obj)
{
    return IndexOf(obj.c_str(), obj.GetLength());
}

int MyString::IndexOf(const char* pszBuf)
{
    return IndexOf(pszBuf, strlen(pszBuf));
}

bool MyString::Equal(MyString& obj)
{
    return Equal(obj.c_str());
}

bool MyString::Equal(const char *pszBuf)
{
    return strcmp(c_str(), pszBuf) == 0;
}



MyString MyString::operator+ (MyString &obj)
{
    MyString str(c_str());
    return str.Append(obj);
}

MyString& MyString::operator= (MyString &obj)
{
    return Copy(obj);
}

MyString & MyString::operator=(const char * pszBuf)
{
    Copy(pszBuf);
    return *this;
}

MyString& MyString::operator+= (MyString &obj)
{
    return Append(obj);
}

MyString & MyString::operator<<(const char * pszBuf)
{
    Copy(pszBuf);
    return *this;
}

bool MyString::operator== (MyString &obj)
{
    return Equal(obj);
}

bool MyString::operator!= (MyString &obj)
{
    return !Equal(obj);
}

//bool MyString::operator> (MyString &obj)
//{
//    return false;
//}

char MyString::operator[] (int index)
{
    return c_str()[index];
}
