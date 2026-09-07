#pragma once
#include <string>
#include <vector>

using namespace std;

class Player
{
private:
    string name;          // player's name
    vector<string> deck;  // list of possible cards
    int numberOfWins;     // tracks wins
    int totalForHand;     // current hand total
    bool isPlayer;        // true if user

    string getRandomCard();   // returns random card
    int getCardsValue(string card); // converts card to value

public:
    Player(string name, bool isPlayer); // constructor for Player class

    string getName();        // returns name
    bool getIsPlayer();      // checks if user

    void increaseScore();    // adds win
    int getScore();          // returns wins

    void dealHand();         // deals cards
    void setTotalHand();     // resets hand
    int getTotalForHand();   // returns hand total

    void hit();              // draws another card
    int allAs();             // handles Ace value
};