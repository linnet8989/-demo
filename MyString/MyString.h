#pragma once	
#ifdef MYSTRING_EXPORTS 
#  define DLL_API __declspec(dllexport)
#else
#  define DLL_API __declspec(dllimport)
#endif
//todo£ºÐ´Ê±¿½±´
class DLL_API MyString
{
private:
    char* m_pszBuf;
    int m_length;
    int m_bufSize;
    static int s_count;
    MyString& Copy(const char* pszBuf, int length);
    MyString& Append(const char* pszBuf, int length);
    int IndexOf(const char* pszBuf, int length);

protected:
    int GetBufSize();
    void SetBufSize(int bufSize);
    char* GetBuf();
    void SetBuf(char* pszBuf);
    void SetLength(int length);

public:
    MyString();
    MyString(const char* pszBuf);
    MyString(MyString& obj);
    virtual ~MyString();

    int GetLength();
    int Length();
    const char* c_str();

    MyString& Copy(MyString& obj);
    MyString& Copy(const char* pszBuf);
    MyString& Append(MyString& obj);
    MyString& Append(const char* pszBuf);
    int Split(char* pszBuf, const char* pszDelimiter, char* pszOutStrings[], int count);
    int Split(const char* pszDelimiter, MyString pOutStrings[], int count);
    void Format(const char* pszFormat, ...);
    int IndexOf(MyString& obj);
    int IndexOf(const char* pszBuf);
    bool Equal(MyString& obj);
    bool Equal(const char* pszBuf);

    MyString operator+ (MyString &obj);
    MyString& operator= (MyString &obj);
    MyString& operator= (const char* pszBuf);
    MyString& operator+= (MyString &obj);
    MyString& operator<< (const char* pszBuf);
    bool operator== (MyString &obj);
    bool operator!= (MyString &obj);
    //bool operator> (MyString &obj);
    virtual char operator[] (int index);
};