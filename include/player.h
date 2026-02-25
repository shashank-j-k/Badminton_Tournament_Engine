#include <iostream>
#include "utils.h"

using std :: string;

struct record
{
    int iSingles;
    int iDoubles;
};
// extern class Singles_Doubles

class CPlayer  : protected Singles_Doubles
{
    string szPlayerName;
    string szGroup;
    struct record MatchesPlayed;
    struct record Wins;
    struct record Lost;
    char Flag;          // 1 - singles  // 2 - doubles
    char Fix;
    int iPriority;      // 1- beg 2-int 3- adv
    int iPoints;
    CPlayer *pPartner;
    CPlayer *pNext;

public:
    CPlayer();
    CPlayer(int);
    ~CPlayer();
    void DisplayPlayerDetails(CPlayer *);

friend class Singles_Doubles;
};