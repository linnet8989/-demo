#include "..\MyString\MyString.h"
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "MyString.lib")

int main()
{
    MyString str;
    str.Copy("123");
    printf("%s\n", str.c_str());

    system("pause");
    return 0;
}