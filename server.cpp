#include "include.h"
int main()
{
    server test;
    for (int i = 0; i < 10; i++)
    {
        test.connect();
        test.writing("trash");
        test.closing();
    }

    return 0;
}