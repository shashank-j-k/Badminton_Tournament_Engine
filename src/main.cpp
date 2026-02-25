#include <iostream>
#include "include/utils.h"

using namespace std;

int main()
{
    Singles_Doubles obj;
    Menu *pPtr = &obj;
    pPtr->DisplayMenu();

    return 0;
}