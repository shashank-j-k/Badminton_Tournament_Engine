#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "include/player.h"
#include "include/utils.h"

using namespace std;

int g_iMatchNoS = 0;
int g_iMatchNoD = 0;

CPlayer ::CPlayer()
{
    char chChoice;
    while (1)
    {
        cout << "Player Category :\n1. Singles\t2. Doubles\tEnter your choice : ";
        cin >> chChoice;
        if (chChoice == '1')
        {
            Flag = '1';
            break;
        }
        else if (chChoice == '2')
        {
            Flag = '2';
            break;
        }
        else
        {
            cout << "Invalid choice. Try Again\n";
            cin.get();
        }
    }
    cin.get();
    cout << "\nEnter Player Name : ";
    getline(cin, szPlayerName);
    szGroup.clear();

    while (1)
    {
        cout << "\nPlayer Group :\n1. Beginner\t2. Intermediate\t\t3. Advanced\tEnter your choice : ";
        cin >> chChoice;
        if (chChoice == '1')
        {
            szGroup = "Beginner";
            iPriority = 1;
            break;
        }
        else if (chChoice == '2')
        {
            szGroup = "Intermediate";
            iPriority = 2;
            break;
        }
        else if (chChoice == '3')
        {
            szGroup = "Advanced";
            iPriority = 3;
            break;
        }
        else
            cout << "Invalid choice. Try Again\n";
    }

    Fix = 'N';
    MatchesPlayed.iDoubles = 0;
    MatchesPlayed.iSingles = 0;
    Wins.iDoubles = 0;
    Wins.iSingles = 0;
    Lost.iSingles = 0;
    Lost.iDoubles = 0;
    pPartner = NULL;
    pNext = NULL;
}

CPlayer ::CPlayer(int iNo)
{
    cin.get();
    cout << "\nEnter Partner Name : ";
    getline(cin, szPlayerName);
    szGroup.clear();

    if (iNo == 1)
    {
        szGroup = "Beginner";
        iPriority = 1;
    }
    else if (iNo == 2)
    {

        szGroup = "Intermediate";
        iPriority = 2;
    }
    else
    {
        szGroup = "Advanced";
        iPriority = 3;
    }

    Fix = 'N';
    MatchesPlayed.iDoubles = 0;
    MatchesPlayed.iSingles = 0;
    Wins.iDoubles = 0;
    Wins.iSingles = 0;
    Lost.iSingles = 0;
    Lost.iDoubles = 0;
    pPartner = NULL;
    pNext = NULL;
    cout << "\nLeaving constructor\n";
}

void CPlayer ::DisplayPlayerDetails(CPlayer *pTemp)
{
    cout << endl;
    cout << pTemp->szPlayerName << "\t" << "(" << pTemp->szGroup << ")" << endl;
    cout << setw(22) << " " << setw(15) << "Singles" << setw(15) << "Doubles" << endl;
    cout << setw(20) << "Matches played" << setw(2) << ":" << setw(15) << pTemp->MatchesPlayed.iSingles << setw(15) << pTemp->MatchesPlayed.iDoubles << endl;
    cout << setw(20) << "Wins" << setw(2) << ":" << setw(15) << pTemp->Wins.iSingles << setw(15) << pTemp->Wins.iDoubles << endl;
    cout << setw(20) << "Lost" << setw(2) << ":" << setw(15) << pTemp->Lost.iSingles << setw(15) << pTemp->Lost.iDoubles << endl;
    cout << endl;
}

CPlayer ::~CPlayer()
{
    CPlayer *pPtr = NULL;

    if (pSinglesHead != NULL)
    {
        while (pSinglesHead != NULL)
        {
            pPtr = pSinglesHead;
            pSinglesHead = pSinglesHead->pNext;
            delete pPtr;
        }
        pPtr = NULL;
    }

    if (pDoublesHead != NULL)
    {
        while (pDoublesHead != NULL)
        {
            pPtr = pDoublesHead;
            pDoublesHead = pDoublesHead->pNext;
            delete pPtr;
        }
        pPtr = NULL;
    }
}

void Singles_Doubles ::AddNewPlayers()
{
    int iChoice;
    CPlayer *pNewNode = NULL;
    cout << "-------------Adding New Player Entry-------------\n";
    pNewNode = new CPlayer;
    if (NULL == pNewNode)
    {
        cout << "Memory Allocation Failed\n";
        return;
    }

    pNewNode->pNext = NULL;
    CPlayer *pTemp = NULL;

    if (pNewNode->Flag == '1') // singles player
    {
        pTemp = pSinglesHead;
        pNewNode->pPartner = NULL; // no partner

        if (pSinglesHead == NULL || pNewNode->iPriority <= pSinglesHead->iPriority)
        {
            pNewNode->pNext = pSinglesHead;
            pSinglesHead = pNewNode;
        }
        else
        {
            while (pTemp->pNext != NULL)
            {
                if (pTemp->pNext->iPriority >= pNewNode->iPriority)
                    break;
                pTemp = pTemp->pNext;
            }
            pNewNode->pNext = pTemp->pNext;
            pTemp->pNext = pNewNode;
        }
    }
    else if (pNewNode->Flag == '2') // doubles player
    {
        pTemp = pDoublesHead;

        if (pDoublesHead == NULL || pNewNode->iPriority <= pDoublesHead->iPriority)
        {
            pNewNode->pNext = pDoublesHead;
            pDoublesHead = pNewNode;
        }
        else
        {
            while (pTemp->pNext != NULL)
            {
                if (pTemp->pNext->iPriority >= pNewNode->iPriority)
                    break;
                pTemp = pTemp->pNext;
            }
            pNewNode->pNext = pTemp->pNext;
            pTemp->pNext = pNewNode;
        }

        CPlayer *pNewNode1 = new CPlayer(pNewNode->iPriority);
        pNewNode->pPartner = pNewNode1;
        pNewNode1->pPartner = pNewNode;
    }
    cout << "\nPlayer entry added succesfully!!!\n\n";
}

void Singles_Doubles ::ListAllPlayers()
{
    cout << "-------------Singles Players-------------" << endl;

    int iCount = 0;
    CPlayer *pTemp = pSinglesHead;

    while (pTemp != NULL)
    {
        iCount++;
        cout << left << setw(5) << iCount << setw(20) << pTemp->szPlayerName << setw(20) << pTemp->szGroup << endl;
        pTemp = pTemp->pNext;
    }
    if (pSinglesHead == NULL)
    {
        cout << "No entries yet\n";
    }
    cout << "\nTotal Singles Entries : " << iCount << endl;

    cout << "-------------Doubles Players-------------" << endl;

    iCount = 0;

    pTemp = pDoublesHead;
    while (pTemp != NULL)
    {
        iCount++;
        cout << left << setw(5) << iCount << setw(20) << pTemp->szPlayerName << setw(10) << " & " << setw(20) << pTemp->pPartner->szPlayerName << setw(10) << " " << setw(20) << pTemp->szGroup << endl;

        pTemp = pTemp->pNext;
    }
    if (pDoublesHead == NULL)
    {
        cout << "No entries yet\n";
        return;
    }
    cout << "\nTotal Doubles Entries : " << iCount << endl;
    cin.get();
}

void Singles_Doubles ::RemoveAPlayer()
{
    char chChoice;
    string Name;
    CPlayer *pTemp = NULL;
    CPlayer *pTemp1 = NULL;
    cout << "**********Removing a player************\n";
    cout << "Choose Category:\n1. Singles\n2. Doubles\nEnter your choice : ";
    cin >> chChoice;

    cin.get();
    cout << "Enter name of player : ";
    getline(cin, Name);

    if (chChoice == '1')
    {
        if (pSinglesHead == NULL)
        {
            cout << "\nNo player entries recorded\n";
            return;
        }
        pTemp1 = pSinglesHead;

        if (pTemp1->szPlayerName == Name)
        {
            pSinglesHead = pTemp1->pNext;
            delete pTemp1;
            cout << "\nPlayer " << Name << " removed successfully!!!\n";
        }
        else
        {
            pTemp = pSinglesHead;
            pTemp1 = pSinglesHead->pNext;
            while (pTemp1 != NULL)
            {
                if (pTemp1->szPlayerName == Name)
                {
                    pTemp->pNext = pTemp1->pNext;
                    pTemp1->pNext = NULL;
                    delete pTemp1;
                    cout << "\nPlayer " << Name << " removed successfully!!!\n";
                    return;
                }
                else
                {
                    pTemp = pTemp1;
                    pTemp1 = pTemp1->pNext;
                }
            }
            cout << "No entries found by that name. Try again...\n";
        }
    }

    if (chChoice == '2') ///////////////////////////////////////////////////////////////
    {
        if (pDoublesHead == NULL)
        {
            cout << "No player entries recorded\n";
            return;
        }

        cout << "\n***Removing entry of a doubles player will result in removal of his partner also***\n";

        pTemp1 = pDoublesHead;

        if (pTemp1->szPlayerName == Name || pTemp1->pPartner->szPlayerName == Name)
        {
            cout << "Players " << pTemp1->szPlayerName << " & " << pTemp1->pPartner->szPlayerName << " removed successfully\n";
            delete pTemp1->pPartner;
            pDoublesHead = pTemp1->pNext;
            delete pTemp1;
            return;
        }
        else
        {
            pTemp = pDoublesHead;
            pTemp1 = pDoublesHead->pNext;
            while (pTemp1 != NULL)
            {
                if (pTemp1->szPlayerName == Name)
                {
                    pTemp->pNext = pTemp1->pNext;
                    cout << "Players " << pTemp1->szPlayerName << " & " << pTemp1->pPartner->szPlayerName << " removed successfully\n";
                    delete pTemp1->pPartner;
                    delete pTemp1;
                    return;
                }
                else
                {
                    pTemp = pTemp1;
                    pTemp1 = pTemp1->pNext;
                }
            }
            cout << "Player entry not found. Try again...\n";
        }
    }
}

void Singles_Doubles ::PlayerStatistics()
{
    cout << "-----------------Player Statistics-----------------\n";

    CPlayer *pTemp = NULL;
    pTemp = pSinglesHead;
    while (pTemp != NULL)
    {
        pTemp->DisplayPlayerDetails(pTemp);
        pTemp = pTemp->pNext;
    }

    pTemp = pDoublesHead;
    while (pTemp != NULL)
    {
        if (pTemp->Flag != '1')
            pTemp->DisplayPlayerDetails(pTemp);
        if (pTemp->pPartner->Flag != '1')
            pTemp->DisplayPlayerDetails(pTemp->pPartner);
        pTemp = pTemp->pNext;
    }
}

