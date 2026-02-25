#include <iostream>
#include <string>
#include "utils.h"

using std :: string;

// extern class Singles_Doubles;

struct set
{
    int iScore1;
    int iScore2;
};

class MatchHistory : public Singles_Doubles
{
    int iNo;
    string Player1;
    string Player2;
    string Player3;
    string Player4;
    struct set S1;
    struct set S2;
    struct set S3;
    MatchHistory *pNext;
    friend class Singles_Doubles;
public : 
    MatchHistory();
    ~MatchHistory();
    void DisplayMatchHistory(MatchHistory*);
};
