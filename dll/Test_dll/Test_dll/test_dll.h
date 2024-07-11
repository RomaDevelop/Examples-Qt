#ifndef TEST_DLL_H
#define TEST_DLL_H

#include "Test_dll_global.h"

class TEST_DLL_EXPORT Test_dll
{
public:
    Test_dll();
    int data;

    int GetData() { return data; }
};

#endif // TEST_DLL_H
