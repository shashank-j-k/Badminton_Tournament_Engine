#include <iostream>
#include "utils.h"

// extern class Singles_Doubles;
// extern class CPlayer;

class CPointsTable : public Singles_Doubles
{
    CPointsTable *pPrev;
    CPlayer *pPlayer;
    CPointsTable *pNext;
public :
    CPointsTable();
    ~CPointsTable();

    friend class Singles_Doubles;
};