#include <iostream>
#include <string>
#include "utils.h"

using std :: string;
// extern class Singles_Doubles;

class Scheduled_Matches_Singles : protected Singles_Doubles
{
    int MatchNo;
    CPlayer *Player1;
    CPlayer *Player2;    
    Scheduled_Matches_Singles *pNext;
public :
    Scheduled_Matches_Singles();  
    Scheduled_Matches_Singles(string, string);
    ~Scheduled_Matches_Singles();
    void DisplayScheduledMatches();
    friend class Singles_Doubles;
};

class Scheduled_Matches_Doubles : protected Singles_Doubles
{
    int MatchNo;
    CPlayer *Player1;
    CPlayer *Player2;    
    CPlayer *Player3;    
    CPlayer *Player4;    
    Scheduled_Matches_Doubles *pNext;
public :
    Scheduled_Matches_Doubles();  
    Scheduled_Matches_Doubles(string, string);
    ~Scheduled_Matches_Doubles();
    void DisplayScheduledMatches();
    friend class Singles_Doubles;
};