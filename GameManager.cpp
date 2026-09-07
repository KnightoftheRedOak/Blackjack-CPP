#include "GameManager.h"
#include <iostream>
#include <fstream>
#include <conio.h> 

using namespace std;

// Gets users info(name)
// Adds them to the allPlayers list
// set pointer for location of player
void GameManager::addUserToPlayerList()
{
    cout << "==================================\n";
    cout << "      WELCOME TO FAT TONY'S\n";
    cout << "==================================\n";

    cout << "What's your name, boss?\n";

    string name;
    getline(cin, name);

    Player player(name, true);
    allPlayers.push_back(player);

    user = &allPlayers[0];
}

// Asks user for number of players
void GameManager::getNames()
{
    cout << "\nHey, Fat Tony wants to know how many are in your group today?\n";
    cout << "Don't count yourself, wise guy.\n";

    while (true)
    {
        string answer;
        getline(cin, answer);

        try
        {
            numOfPlayers = stoi(answer);

            cout << "Good. I'll let the boss know.\n";
            cout << "Game's in the back.\n\n";
            break;
        }
        catch (...)
        {
            cout << "Wise guy, eh?\n";
            cout << "Try that again… see what happens.\n";
        }
    }
}

// Writes all players name to text file named ledger
// will prompt user for names based on number of players
void GameManager::addToLedger()
{
    cout << "\nHey, how you doin', " << user->getName() << "?\n";
    cout << "Take a seat. Write your crew's names in the ledger.\n";
    cout << "We don't want any problems later.\n";

    ofstream file("ledger.txt");
    file << "Players:\n";
    file.close();

    for (int i = 0; i < numOfPlayers; i++)
    {
        cout << "NAME: ";
        string name;
        getline(cin, name);

        allPlayers.push_back(Player(name, false));

        ofstream append("ledger.txt", ios::app);
        append << name << "\n";
        append.close();
    }
}

// Asks user for number of rounds they want to play
void GameManager::playGame()
{
    cout << "\n----------------------------------\n";
    cout << "Alright...business is settled.\n";
    cout << "How many hands we playing?\n";
    cout << "----------------------------------\n";

    int numOfRounds = 0;
    int index = 0;

    while (true)
    {
        string answer;
        getline(cin, answer);

        try
        {
            numOfRounds = stoi(answer);
            cout << "Good. Dealing " << numOfRounds << " hands.\n";
            break;
        }
        catch (...)
        {
            cout << "Enter a number.\n";
        }
    }

    while (index < numOfRounds)
    {
        for (int i = 0; i < allPlayers.size(); i++)
        {
            Player& currentPlayer = allPlayers[i];

            system("cls");

            cout << "==================================\n";
            cout << "            HAND " << (index + 1) << "\n";
            cout << "==================================\n";

            cout << "\n==================================\n";
            cout << "        " << currentPlayer.getName() << "'S TURN\n";
            cout << "==================================\n";

            // Checks if current player is  user or not
            if (currentPlayer.getIsPlayer())
            {
                currentPlayer.dealHand();
                anteUp(currentPlayer);
            }
            else
            {
                currentPlayer.dealHand();

                cout << "\n[Press SPACE to continue]";

                // Will loop until user presses space bar
                while (_getch() != ' ')
                {
                }
            }
        }

        findWinner(index + 1);
        displayHandTotals(index + 1);

        // Sets starter hand to 0 for each player
        resetTotalHandForEachPlayer();
        index++;
    }

    printFinalLedger();
}

// loops allPlayers and prints their current hand
// finds winner by compairing hand amount and ruling out

void GameManager::displayHandTotals(int handNumber)
{
    system("cls");

    cout << "==================================\n";
    cout << "        HAND " << handNumber << " RESULTS\n";
    cout << "==================================\n\n";

    for (int i = 0; i < allPlayers.size(); i++)
    {
        Player& player = allPlayers[i];
        cout << player.getName() << ": " << player.getTotalForHand() << endl;
    }

    cout << "WINNER: " << currentLeader->getName() << endl;

    cout << "\n[Press SPACE to continue]";

    while (_getch() != ' ') 
    {
    }
}


// sets starter hand for each player to 0
void GameManager::resetTotalHandForEachPlayer()
{
    for (int i = 0; i < allPlayers.size(); i++)
    {
        allPlayers[i].setTotalHand();
    }
}

// Asks user if they want another card
// yes, will call hit method from players class
void GameManager::anteUp(Player& currentPlayer)
{
    while (true)
    {
        cout << "You want another card, boss?\n";
        cout << "[Y] Hit   [N] Stand\n";

        string answer;
        getline(cin, answer);

        if (answer == "Y" || answer == "y")
        {
            currentPlayer.hit();
        }
        else if (answer == "N" || answer == "n")
        {
            break;
        }
    }
}

// loops through allPlayers and compares hand totals
// decides winner fom largest sum not over 21
// loops through all players and writes each hand total to the ledger
void GameManager::findWinner(int handNumber)
{
    currentLeader = &allPlayers[0];

    for (int i = 0; i < allPlayers.size(); i++)
    {
        if (allPlayers[i].getTotalForHand() <= 21 &&
            (currentLeader->getTotalForHand() > 21 ||
                allPlayers[i].getTotalForHand() > currentLeader->getTotalForHand()))
        {
            currentLeader = &allPlayers[i];
        }
    }

    currentLeader->increaseScore();

    ofstream append("ledger.txt", ios::app);
    append << "\nHand " << handNumber << ":\n";

    for (int i = 0; i < allPlayers.size(); i++)
    {
        Player& player = allPlayers[i];

        // writing each player's hand to the ledger
        append << player.getName() << ": " << player.getTotalForHand() << "\n";
    }

    append.close();
}

// prints finial ledger for game
void GameManager::printFinalLedger()
{
    system("cls");

    cout << "==================================\n";
    cout << "          FINAL LEDGER\n";
    cout << "==================================\n\n";

    ifstream file("ledger.txt");
    string line;

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();

    cout << "\n==================================\n";
    cout << "        OVERALL WINNER\n";
    cout << "==================================\n";

    Player* finalWinner = &allPlayers[0];

    for (int i = 0; i < allPlayers.size(); i++)
    {
        if (allPlayers[i].getScore() > finalWinner->getScore())
        {
            finalWinner = &allPlayers[i];
        }
    }

    cout << finalWinner->getName() << " with "
        << finalWinner->getScore() << " wins.\n";
}
