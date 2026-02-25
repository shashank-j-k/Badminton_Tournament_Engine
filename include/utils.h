#pragma once
#include <iostream>

#define FLAG_SINGLES 1
#define FLAG_DOUBLES 2
#define FLAG_BOTH 3

using std :: string;

class CPlayer;
class MatchHistory;
class Scheduled_Matches_Singles;
class Scheduled_Matches_Doubles;
class CPointsTable;

struct NextRound
{
    NextRound *pPrev;
    CPlayer *pPlayer;
    NextRound *pNext;
};

class Menu
{
public:
    void DisplayMenu();
    virtual void AddNewPlayers() = 0;
    virtual void ScheduleMatchesManually() = 0;
    virtual void AutoScheduleMatches() = 0;
    virtual void ScheduledMatches() = 0;
    virtual void ClearScheduledMatches() = 0;
    virtual void FinishedMatchesHistory() = 0;
    virtual void ListAllPlayers() = 0;
    virtual void RemoveAPlayer() = 0;
    virtual void PlayerStatistics() = 0;
    virtual void StartAMatch() = 0;
    virtual void PointsTable() = 0;
    virtual void DeclareWinner() = 0;
    virtual void EndTournament() = 0;
};

class Singles_Doubles : public Menu
{
protected:
    CPlayer *pSinglesHead;
    CPlayer *pDoublesHead;
    MatchHistory *pHistoryHead;
    Scheduled_Matches_Singles *pMatchesHead;
    Scheduled_Matches_Doubles *pMatchesHeadD;
    CPointsTable *pPointerHead;
    NextRound *pFirst;
    NextRound *pLast;
public :
    Singles_Doubles();
    ~Singles_Doubles();
    void AddNewPlayers();
    void ListAllPlayers();
    void ScheduleMatchesManually();
    void AutoScheduleMatches();
    void AddAMatch(CPlayer*, CPlayer*);
    void AddAMatch(CPlayer*, CPlayer*, CPlayer*, CPlayer*);
    void RemoveAMAtch();
    void RemoveAMAtchD();
    void ScheduledMatches();
    void ClearScheduledMatches();
    void FinishedMatchesHistory();
    MatchHistory* CreateNewMatchRecord();
    void RemoveAPlayer();
    void PlayerStatistics();
    void StartAMatch();
    void PointsTable();
    void AddEntry(CPlayer *pPtr);
    void DisplayPT(string, string, int, char);
    void DeclareWinner();
    void EndTournament();
};






