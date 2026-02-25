#include <iostream>
#include <iomanip>
#include "include/utils.h"
#include "include/player.h"
#include "include/history.h"

using namespace std;

MatchHistory ::MatchHistory()
{
    iNo = 0;
    Player1 = " ";
    Player2 = " ";
    Player3 = " ";
    Player4 = " ";
    S1.iScore1 = 0;
    S1.iScore2 = 0;
    S2.iScore1 = 0;
    S2.iScore2 = 0;
    S3.iScore1 = 0;
    S3.iScore2 = 0;
    pNext = NULL;
}

MatchHistory ::~MatchHistory()
{
    if (pHistoryHead != NULL)
    {
        MatchHistory *pTemp = NULL;

        while (pHistoryHead != NULL)
        {
            pTemp = pHistoryHead;
            pHistoryHead = pHistoryHead->pNext;
            delete pTemp;
        }
        pTemp = NULL;
    }
}

void MatchHistory ::DisplayMatchHistory(MatchHistory *pPtr)
{
    cout << endl;
    cout << "Match No : "
         << ++iNo << endl;
    if (pPtr->Player3 != " " && pPtr->Player4 != " ")
    {
        cout << left << setw(20) << pPtr->Player1 << " & " << pPtr->Player2 << " vs "
             << right << setw(20) << pPtr->Player3 << " & " << pPtr->Player4 << endl
             << endl;
    }
    cout << left << setw(20) << pPtr->Player1 << " vs " << right << setw(20) << pPtr->Player2 << endl
         << endl;
    cout << left << setw(20) << "Set 1" << " : " << S1.iScore1 << " - " << S1.iScore2 << endl;
    if (S2.iScore1 != 0 && S2.iScore2 != 0)
        cout << left << setw(20) << "Set 2" << " : " << S2.iScore1 << " - " << S2.iScore2 << endl;
    if (S3.iScore1 != 0 && S3.iScore2 != 0)
        cout << left << setw(20) << "Set 3" << " : " << S3.iScore1 << " - " << S3.iScore2 << endl
             << endl;
}

void Singles_Doubles ::FinishedMatchesHistory()
{
    MatchHistory *pTemp = pHistoryHead;

    if (pHistoryHead == NULL)
    {
        cout << "Match History Empty\n";
        return;
    }

    while (pTemp != NULL)
    {
        pTemp->DisplayMatchHistory(pTemp);
        pTemp = pTemp->pNext;
    }

    cin.get();
}


MatchHistory *Singles_Doubles ::CreateNewMatchRecord()
{
    MatchHistory *pNewNode = NULL;

    pNewNode = new MatchHistory;
    if (NULL == pNewNode)
    {
        cout << " Memory Allocation Failed\n";
        return NULL;
    }

    pNewNode->pNext = pHistoryHead;
    pHistoryHead = pNewNode;
    return pNewNode;
}