#include <iostream>
#include <iomanip>
#include "include/utils.h"
#include "include/player.h"
#include "include/pointstable.h"

using namespace std;

CPointsTable ::CPointsTable()
{
    pPrev = NULL;
    pPlayer = NULL;
    pNext = NULL;
}

CPointsTable ::~CPointsTable()
{
    if(pPointerHead != NULL)
    {
        CPointsTable *pTemp = NULL;

        while(pPointerHead != NULL)
        {
            pTemp = pPointerHead;
            pPointerHead = pPointerHead->pNext;
            pTemp->pPrev = NULL;
            pTemp->pNext = NULL;
            delete pTemp;
        }
        pTemp = NULL;
    }
}

void Singles_Doubles ::PointsTable()
{
    int iRank = 1;

    if (pHistoryHead == NULL)
    {
        cout << "No match records found yet";
        return;
    }

    cout << "\n**********Points Table************\n";
    DisplayPT("Singles", "Beginner", 1, '1');                   // category, group, priority, flag
    DisplayPT("Singles", "Intermediate", 2, '1');
    DisplayPT("Singles", "Advanced", 3, '1');
    DisplayPT("Doubles", "Beginner", 1, '2');
    DisplayPT("Doubles", "Intermediate", 2, '2');
    DisplayPT("Doubles", "Advanced", 3, '2');
}

void Singles_Doubles ::AddEntry(CPlayer *pPtr)
{
    CPointsTable *pNewEntry = new CPointsTable;
    pNewEntry->pPlayer = pPtr;
    pNewEntry->pNext = NULL;
    pNewEntry->pPrev = NULL;

    if (pPointerHead == NULL)
    {
        pPointerHead = pNewEntry;
        return;
    }

    CPointsTable *pTemp = pPointerHead;

    while (pTemp != NULL)
    {
        if (pPtr->iPoints > pTemp->pPlayer->iPoints)
        {
            pNewEntry->pNext = pTemp;
            pNewEntry->pPrev = pTemp->pPrev;

            if (pTemp->pPrev != NULL)
                pTemp->pPrev->pNext = pNewEntry;
            else
                pPointerHead = pNewEntry;

            pTemp->pPrev = pNewEntry;
            return;
        }

        if (pTemp->pNext == NULL)
            break;

        pTemp = pTemp->pNext;
    }

    // Insert at end
    pTemp->pNext = pNewEntry;
    pNewEntry->pPrev = pTemp;
}

void Singles_Doubles ::DisplayPT(string category, string group, int iPri, char Flag)
{
    int iRank = 1;
    CPointsTable *pTemp = pPointerHead;
    cout << "---------------------------------------------------\n";
    cout << setw(15) << "Category" << ":" << setw(15) << category << endl;
    cout << setw(15) << "Group" << ":" << setw(15) << group << endl
         << endl;
    cout << "---------------------------------------------------\n";
    
    cout << setw(5) << "Rank" << setw(20) << "Player Name" 
         << setw(10) << "Points" << setw(5) << "Wins" 
         << setw(5) << "Lost" << endl << endl;

    if(Flag == '1')
        while (pTemp != NULL)
        {
            if(pTemp->pPlayer->iPriority == iPri && pTemp->pPlayer->Flag == Flag)
                cout << setw(5) << iRank++ << setw(20) << pTemp->pPlayer->szPlayerName 
                    << setw(10) << pTemp->pPlayer->iPoints << setw(5) << pTemp->pPlayer->Wins.iSingles
                    << setw(5) << pTemp->pPlayer->Lost.iSingles << endl;
            pTemp = pTemp->pNext;
        }
    else
        while (pTemp != NULL)
        {
            if(pTemp->pPlayer->iPriority == iPri && pTemp->pPlayer->Flag == Flag)
                cout << setw(5) << iRank++ << setw(9) << pTemp->pPlayer->szPlayerName << setw(2) << "&" 
                     << setw(9) << pTemp->pPlayer->pPartner->szPlayerName
                     << setw(10) << pTemp->pPlayer->iPoints << setw(5) << pTemp->pPlayer->Wins.iDoubles
                     << setw(5) << pTemp->pPlayer->Lost.iDoubles << endl;
            pTemp = pTemp->pNext;
        }
    cout << "**********************************************" << endl;
}
