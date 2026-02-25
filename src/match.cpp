#include <iostream>
#include <iomanip>
#include "include/utils.h"
#include "include/player.h"
#include "include/history.h"
#include "include/matches.h"

using namespace std;

int g_iMatchNoS = 0;
int g_iMatchNoD = 0;

Scheduled_Matches_Singles ::Scheduled_Matches_Singles()
{
    MatchNo = 0;
    Player1 = NULL;
    Player2 = NULL;
    pNext = NULL;
}

Scheduled_Matches_Singles ::~Scheduled_Matches_Singles()
{
    Scheduled_Matches_Singles *pTemp = NULL;

    if (pMatchesHead != NULL)
    {
        while (pMatchesHead != NULL)
        {
            pTemp = pMatchesHead;
            pMatchesHead = pMatchesHead->pNext;
            delete pTemp;
        }
        pTemp = NULL;
    }
}

Scheduled_Matches_Doubles ::Scheduled_Matches_Doubles()
{
    MatchNo = 0;
    Player1 = NULL;
    Player2 = NULL;
    Player3 = NULL;
    Player4 = NULL;
    pNext = NULL;
}

Scheduled_Matches_Doubles ::~Scheduled_Matches_Doubles()
{
    Scheduled_Matches_Doubles *pTemp = NULL;

    if (pMatchesHeadD != NULL)
    {
        while (pMatchesHeadD != NULL)
        {
            pTemp = pMatchesHeadD;
            pMatchesHeadD = pMatchesHeadD->pNext;
            delete pTemp;
        }
        pTemp = NULL;
    }
}

void Singles_Doubles ::AutoScheduleMatches()
{
    CPlayer *pTemp = pSinglesHead;
    CPlayer *pTemp1 = NULL; // scheduling singles matches

    // if (pMatchesHead != NULL && pMatchesHeadD != NULL)
    // {
    //     cout << "Matches scheduled already. Clear schedules matches and try again later...\n";
    //     return;
    // }
    ClearScheduledMatches();

    if (pSinglesHead == NULL)
    {
        cout << "\nNo Single player entries yet\n";
        // return;
    }
    else
    {
        while (pTemp != NULL)
        {
            if (pTemp->pNext != NULL)
                pTemp1 = pTemp->pNext;
            else
                break;

            if (pTemp1->iPriority == pTemp->iPriority)
            {
                if (pTemp1->Fix == 'N' && pTemp->Fix == 'N')
                {
                    AddAMatch(pTemp, pTemp1);
                    pTemp->Fix = 'Y';
                    pTemp1->Fix = 'Y';
                    if (pTemp1->pNext != NULL)
                        pTemp = pTemp1->pNext;
                    else
                        break;
                }
            }
            else if (pTemp1->iPriority != pTemp->iPriority)
            {
                cout << "No possible matches found for " << pTemp->szPlayerName << endl;
                pTemp = pTemp->pNext;
                ;
            }
        }
        if (pTemp->pNext == NULL)
        {
            cout << "No possible matches found for " << pTemp->szPlayerName << endl;
        }
    }
    // AUTOSCHEDULING Doubles matches
    if (pDoublesHead == NULL)
    {
        cout << "\nNo Doubles entries yet\n";
    }
    else
    {
        pTemp = pDoublesHead;
        pTemp1 = pTemp->pNext;

        while (pTemp != NULL)
        {
            if (pTemp->pNext != NULL)
                pTemp1 = pTemp->pNext;
            else
                break;

            if (pTemp1->iPriority == pTemp->iPriority)
            {
                if (pTemp1->Fix == 'N' && pTemp->Fix == 'N')
                {
                    AddAMatch(pTemp, pTemp->pPartner, pTemp1, pTemp1->pPartner);
                    pTemp->Fix = 'Y';
                    pTemp->pPartner->Fix = 'Y';
                    pTemp1->Fix = 'Y';
                    pTemp1->pPartner->Fix = 'Y';
                    if (pTemp1->pNext != NULL)
                        pTemp = pTemp1->pNext;
                    else
                        break;
                }
            }
            else if (pTemp1->szGroup != pTemp->szGroup)
            {
                cout << "No possible matches found for " << pTemp->szPlayerName << "&" << pTemp->pPartner->szPlayerName << endl;
                pTemp = pTemp->pNext;
            }
        }
        if (pTemp->pNext == NULL)
        {
            cout << "No possible matches found for " << pTemp->szPlayerName << "&" << pTemp->pPartner->szPlayerName << endl;
        }
    }

    if (pSinglesHead != NULL || pDoublesHead != NULL)
        cout << "\nMatches scheduled successfully!!!\n";

    ScheduledMatches();
    // char chChoice;
    // int iNo;
    // while(1)
    // {
    //     cout << "Do you want to do any changes in these slots? (Y/N) : " ;
    //     cin.get();
    //     cin >> chChoice;

    //     if(chChoice == 'N' || chChoice == 'n')
    //         return;
    //     else if(chChoice == 'Y' || chChoice =='y')
    //     {
    //         cout << "Enter match number : ";
    //         cin >> iNo;
    //         cout << "Shortly\n";
    //         break;
    //     }
    //     else
    //     {
    //         cout << "Invalid choice. Try Again...\n";
    //         continue;
    //     }
    // }
}

void Singles_Doubles ::ScheduleMatchesManually()
{
    // if (pMatchesHead != NULL || pMatchesHeadD != NULL)
    // {
    //     cout << "Matches scheduled already. Clear scheduled macthes and try again later...\n";
    //     return;
    // }
    if (pSinglesHead == NULL && pDoublesHead == NULL)
        return;

    ClearScheduledMatches();

    CPlayer *pTemp = NULL;
    CPlayer *pTemp1 = NULL;
    CPlayer *pTemp2 = NULL;

    int iCount;
    int iPos;
    int iSlot;

    cout << "***********Scheduling matches************\n";
    if(pSinglesHead != NULL)
    {
        cout << "Available players for singles:\n";
        ListAllPlayers();

        pTemp = pSinglesHead;
        pTemp1 = pSinglesHead;
        pTemp2 = NULL;

        iCount = 1;
        iPos = 0;
        iSlot = 0;

        while (pTemp != NULL)
        {
            if (pTemp->pNext != NULL)
                pTemp1 = pTemp->pNext;
            else
                break;

            if (pTemp->Fix == 'N' && pTemp1->iPriority == pTemp->iPriority)
            {
                cout << "Choose opponent for " << pTemp->szPlayerName << endl;
                pTemp->Fix = 'Y';
            }
            else if (pTemp->Fix == 'N' && pTemp1->Fix != 'N')
            {
                if (pTemp1->pNext != NULL)
                    pTemp1 = pTemp1->pNext;
                else
                    break;
            }
            else
            {
                // if(pTemp->Fix == 'N' && pTemp1->iPriority > pTemp->iPriority)
                //     cout << "[Alert]No free opponent found for " << pTemp->szPlayerName << endl;
                pTemp = pTemp->pNext;
                continue;
            }

            iCount = 0;
            iSlot = 0;
            pTemp2 = pSinglesHead;

            while (pTemp2->iPriority <= pTemp->iPriority)
            {
                iCount++;
                if (pTemp2->iPriority == pTemp->iPriority && pTemp2->Fix == 'N')
                {
                    cout << left << setw(10) << iCount << setw(20) << pTemp2->szPlayerName << endl;
                    iSlot++;
                }
                pTemp2 = pTemp2->pNext;
                if (pTemp2 == NULL)
                    break;
            }

            if (iSlot == 0)
            {
                cout << "No opponent found for " << pTemp->szPlayerName << endl;
                pTemp = pTemp->pNext;
                continue;
            }

            while (1)
            {
                cout << "Enter Opponent ID : ";
                cin >> iPos;

                if (iPos < 0 && iPos > iCount - 1)
                    cout << "Invalid ID. Try Again...\n";
                else
                    break;
            }

            iCount = 1;
            pTemp1 = pSinglesHead;
            while (iCount < iPos)
            {
                iCount++;
                pTemp1 = pTemp1->pNext;
            }
            pTemp1->Fix = 'Y';

            AddAMatch(pTemp, pTemp1);
            cout << "[DONE]Match scheduled successfully\n";
            pTemp = pTemp->pNext;
        }

        if (pTemp == NULL)
            cout << "[DONE]All matches scheduled successfully\n";
        else if (pTemp->pNext == NULL)
            cout << "[ALERT]No match found for " << pTemp->szPlayerName << endl;
        cout << "[DONE]Singles matches scheduled successfully\n";
    }
    // Scheduling Doubles matches
    if(pDoublesHead != NULL)
    {
        cout << "Available players for Doubles:\n";
        ListAllPlayers();

        pTemp = pDoublesHead;
        pTemp1 = NULL;
        pTemp2 = NULL;

        iCount = 1;
        iPos = 0;
        iSlot = 0;

        while (pTemp != NULL)
        {
            if (pTemp->pNext != NULL)
                pTemp1 = pTemp->pNext;
            else
                break;

            if (pTemp->Fix == 'N' && pTemp1->iPriority == pTemp->iPriority)
            {
                cout << "Choose opponent for " << pTemp->szPlayerName << " & " << pTemp->pPartner->szPlayerName << endl;
                pTemp->Fix = 'Y';
                pTemp->pPartner->Fix = 'Y';
            }
            else if (pTemp->Fix == 'N' && pTemp1->Fix != 'N')
            {
                if (pTemp1->pNext != NULL)
                    pTemp1 = pTemp1->pNext;
                else
                    break;
            }
            else
            {
                // if(pTemp->Fix == 'N' && pTemp1->iPriority > pTemp->iPriority)
                //     cout << "[Alert]No free opponent found for " << pTemp->szPlayerName << endl;
                pTemp = pTemp->pNext;
                continue;
            }

            iCount = 0;
            iSlot = 0;
            pTemp2 = pDoublesHead;

            while (pTemp2->iPriority <= pTemp->iPriority)
            {
                iCount++;
                if (pTemp2->iPriority == pTemp->iPriority && pTemp2->Fix == 'N')
                {
                    cout << left << setw(10) << iCount << setw(20) << pTemp2->szPlayerName << " & " << pTemp2->pPartner->szPlayerName << endl;
                    iSlot++;
                }
                pTemp2 = pTemp2->pNext;
                if (pTemp2 == NULL)
                    break;
            }

            if (iSlot == 0)
            {
                cout << "No opponent found for " << pTemp->szPlayerName << " & " << pTemp->pPartner->szPlayerName << endl;
                pTemp = pTemp->pNext;
                continue;
            }

            while (1)
            {
                cout << "Enter Opponent ID : ";
                cin >> iPos;

                if (iPos < 0 && iPos > iCount - 1)
                    cout << "Invalid ID. Try Again...\n";
                else
                    break;
            }

            iCount = 1;
            pTemp1 = pDoublesHead;
            while (iCount < iPos)
            {
                iCount++;
                pTemp1 = pTemp1->pNext;
            }
            pTemp1->Fix = 'Y';

            AddAMatch(pTemp, pTemp->pPartner, pTemp1, pTemp1->pPartner);
            cout << "[DONE]Match scheduled successfully\n";
            pTemp = pTemp->pNext;
        }

        if (pTemp == NULL)
            cout << "[DONE]All matches scheduled successfully\n";
        else if (pTemp->pNext == NULL)
            cout << "[ALERT]No match found for " << pTemp->szPlayerName << " & " << pTemp->pPartner->szPlayerName << endl;
        cout << "[DONE]Doubles matches scheduled successfully\n";
    }
}

void Singles_Doubles ::AddAMatch(CPlayer *pPlayer1, CPlayer *pPlayer2)
{
    Scheduled_Matches_Singles *pNewMatch = new Scheduled_Matches_Singles;
    if (NULL == pNewMatch)
    {
        cout << "Memory Allocation Failed\n";
        return;
    }

    pNewMatch->Player1 = pPlayer1;
    pNewMatch->Player2 = pPlayer2;
    pNewMatch->MatchNo = ++g_iMatchNoS;
    pNewMatch->pNext = NULL;

    if (NULL == pMatchesHead)
    {
        pMatchesHead = pNewMatch;
        return;
    }

    Scheduled_Matches_Singles *pPtr = pMatchesHead;

    while (pPtr->pNext != NULL)
        pPtr = pPtr->pNext;

    pNewMatch->pNext = pPtr->pNext;
    pPtr->pNext = pNewMatch;
}

void Singles_Doubles ::AddAMatch(CPlayer *pPlayer1, CPlayer *pPlayer2, CPlayer *pPlayer3, CPlayer *pPlayer4)
{
    Scheduled_Matches_Doubles *pNewMatch = new Scheduled_Matches_Doubles;

    if (NULL == pNewMatch)
    {
        cout << "Memory Allocation Failed";
        return;
    }

    pNewMatch->Player1 = pPlayer1;
    pNewMatch->Player2 = pPlayer2;
    pNewMatch->Player3 = pPlayer3;
    pNewMatch->Player4 = pPlayer4;
    pNewMatch->MatchNo = ++g_iMatchNoD;
    pNewMatch->pNext = NULL;

    if (NULL == pMatchesHeadD)
    {
        pMatchesHeadD = pNewMatch;
        return;
    }

    Scheduled_Matches_Doubles *pTemp = pMatchesHeadD;

    while (pTemp->pNext != NULL)
        pTemp = pTemp->pNext;

    pNewMatch->pNext = pTemp->pNext;
    pTemp->pNext = pNewMatch;
}

void Singles_Doubles ::ScheduledMatches()
{
    Scheduled_Matches_Singles *pTemp = pMatchesHead;
    cout << endl;
    if (pTemp == NULL)
    {
        cout << "\nNo Singles matches scheduled yet\n";
        // return;
    }

    while (pTemp != NULL)
    {
        cout << left << setw(5) << pTemp->MatchNo
             << setw(20) << pTemp->Player1->szPlayerName << setw(10) << " vs "
             << setw(20) << pTemp->Player2->szPlayerName << endl;
        pTemp = pTemp->pNext;
    }

    Scheduled_Matches_Doubles *pTemp1 = pMatchesHeadD;
    if (pTemp1 == NULL)
    {
        cout << "\nNo Doubles matches scheduled yet\n";
        return;
    }
    cout << endl;
    while (pTemp1 != NULL)
    {
        cout << left << setw(5) << pTemp1->MatchNo
             << setw(20) << pTemp1->Player1->szPlayerName << setw(10) << "&"
             << setw(20) << pTemp1->Player2->szPlayerName << setw(10) << "vs"
             << setw(20) << pTemp1->Player3->szPlayerName << setw(10) << "&"
             << setw(20) << pTemp1->Player4->szPlayerName << setw(10) << endl;
        pTemp1 = pTemp1->pNext;
    }
}

void Singles_Doubles ::ClearScheduledMatches()
{
    Scheduled_Matches_Singles *pSingles = NULL;
    CPlayer *pPtr = pSinglesHead;
    while (pMatchesHead != NULL)
    {
        pSingles = pMatchesHead;
        pMatchesHead = pMatchesHead->pNext;
        delete pSingles;
    }
    pSingles = NULL;
    while (pPtr != NULL)
    {
        pPtr->Fix = 'N';
        pPtr = pPtr->pNext;
    }
    g_iMatchNoS = 0;
    // Clearing Doubles matches
    Scheduled_Matches_Doubles *pDoubles = NULL;
    pPtr = pDoublesHead;

    while (pMatchesHeadD != NULL)
    {
        pDoubles = pMatchesHeadD;
        pMatchesHeadD = pMatchesHeadD->pNext;
        delete pDoubles;
    }
    pDoubles = NULL;
    while (pPtr != NULL)
    {
        pPtr->Fix = 'N';
        pPtr->pPartner->Fix = 'N';
        pPtr = pPtr->pNext;
    }
    g_iMatchNoD = 0;
    cout << "All scheduled matches cancelled successfully\n";
}


void Singles_Doubles ::RemoveAMAtch() // delete first match
{
    Scheduled_Matches_Singles *pTemp = pMatchesHead;

    if (pMatchesHead == NULL)
    {
        return;
    }

    if (pMatchesHead->pNext == NULL)
    {
        delete pTemp;
        pMatchesHead = NULL;
        return;
    }
    else
    {
        pMatchesHead = pTemp->pNext;
        pTemp->pNext = NULL;
        delete pTemp;
    }
}

void Singles_Doubles ::RemoveAMAtchD()
{
    Scheduled_Matches_Doubles *pTemp = pMatchesHeadD;

    if (pMatchesHeadD == NULL)
    {
        return;
    }

    if (pMatchesHeadD->pNext == NULL)
    {
        delete pTemp;
        pMatchesHeadD = NULL;
        return;
    }
    else
    {
        pMatchesHeadD = pTemp->pNext;
        pTemp->pNext = NULL;
        delete pTemp;
    }
}