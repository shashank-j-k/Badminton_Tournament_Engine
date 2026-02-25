#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include "include/player.h"
#include "include/utils.h"
#include "include/matches.h"
#include "include/history.h"
#include "include/pointstable.h"

using namespace std;

Singles_Doubles ::Singles_Doubles()
{
    pSinglesHead = NULL;
    pDoublesHead = NULL;
    pHistoryHead = NULL;
    pMatchesHead = NULL;
    pMatchesHeadD = NULL;
    pPointerHead = NULL;
    pFirst = NULL;
    pLast = NULL;
}

Singles_Doubles ::~Singles_Doubles()
{
    pSinglesHead = NULL;
    pDoublesHead = NULL;
    pHistoryHead = NULL;
    pMatchesHead = NULL;
    pMatchesHeadD = NULL;
}

void Menu ::DisplayMenu()
{
    short int iChoice;
    while (1)
    {
        cout << "********** RBA TOURNAMENT ***********\n"
             << endl;
        // cout << "---------Registration--------" << endl;
        cout << "1. Add new players" << endl;
        cout << "2. Remove a player" << endl;
        cout << "3. List all players" << endl;
        cout << "4. Player Statistics" << endl;
        // cout << "------------Matches----------" << endl;
        cout << "5. Schedule matches manually" << endl;
        cout << "6. Auto schedule matches" << endl;
        cout << "7. Display Scheduled matches" << endl;
        cout << "71. Clear Scheduled matches" << endl;
        cout << "8. Display finished matches history" << endl;
        cout << "9. Start a match" << endl;
        cout << "10. Points Table" << endl;
        cout << "11. Declare Winner" << endl;
        cout << "12. End tournament" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Enter your choice : ";
        cin >> iChoice;

        switch (iChoice)
        {
        case 1:
            AddNewPlayers();
            break;

        case 2:
            RemoveAPlayer();
            break;

        case 3:
            ListAllPlayers();
            break;

        case 4:
            PlayerStatistics();
            break;

        case 5:
            ScheduleMatchesManually();
            break;

        case 6:
            AutoScheduleMatches();
            break;

        case 7:
            ScheduledMatches();
            break;

        case 71:
            ClearScheduledMatches();
            break;

        case 8:
            FinishedMatchesHistory();
            break;

        case 9:
            StartAMatch();
            break;

        case 10:
            PointsTable();
            break;

        case 11:
            DeclareWinner();
            break;

        case 12:
            EndTournament();
            break;

        default:
            cout << "Invalid input. Try Again...";
        }
    }
}


