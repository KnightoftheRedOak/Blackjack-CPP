#pragma once
#include <vector>
#include <string>
#include "Player.h"

using namespace std;

class GameManager
{
private:
    int numOfPlayers;           // number of AI players
    vector<Player> allPlayers;  // list of all players
    Player* user;               // pointer to user player
    Player* currentLeader;      // pointer to current round winner

    void anteUp(Player& currentPlayer); // handles hit/stand logic

public:
    void addUserToPlayerList(); // adds user to player list
    void getNames();            // gets players name
    void addToLedger();         // writes player names to file
    void playGame();            // main game loop

    void displayHandTotals(int handNumber); // shows round results
    void resetTotalHandForEachPlayer();     // resets hands
    void findWinner(int handNumber);        // finds winner
    void printFinalLedger();                // prints file results
};