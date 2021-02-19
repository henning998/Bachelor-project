#include "include.h"
 
int main()
{
    client test;
    test.connecting();
    test.reader();
    test.writing("Dette er en test");
 
    return 0;
}