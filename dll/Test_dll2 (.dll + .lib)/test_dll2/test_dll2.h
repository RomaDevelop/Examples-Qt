#ifndef TEST_DLL2_H
#define TEST_DLL2_H

#include "test_dll2_global.h"

class TEST_DLL2_EXPORT Test_dll2
{
public:
    Test_dll2();
    int data;

    int GetData() { return data; }
};

#endif // TEST_DLL2_H
