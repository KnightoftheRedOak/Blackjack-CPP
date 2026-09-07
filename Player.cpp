#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constructor for player class
// holds deck info 
Player::Player(string name, bool isPlayer)
{
    this->name = name;
    this->isPlayer = isPlayer;
    numberOfWins = 0;
    totalForHand = 0;

    deck = { "2","3","4","5","6","7","8","9","10","J","Q","K","A" };

    srand(time(0));
}

// returns players name
string Player::getName()
{
    return name;
}

// Check to see if user is player or not
bool Player::getIsPlayer()
{
    return isPlayer;
}

// Increases if player wins hand
void Player::increaseScore()
{
    numberOfWins++;
}

// returns number of wins
int Player::getScore()
{
    return numberOfWins;
}

// picks two random cards from deck stores them in cardOne and cardTwo
// finds sum of the two cards
void Player::dealHand()
{
    string cardOne = getRandomCard();
    string cardTwo = getRandomCard();

    int valueOfCardOne = getCardsValue(cardOne);
    int valueOfCardTwo = getCardsValue(cardTwo);

    totalForHand = valueOfCardOne + valueOfCardTwo;

    cout << "\n----------------------------------\n";
    cout << "Hand dealt:\n";
    cout << "Card One: " << cardOne << endl;
    cout << "Card Two: " << cardTwo << endl;
    cout << "Total: " << totalForHand << endl;
    cout << "----------------------------------\n";
}

// resets total for hand to 0 
// used at the start of each round
void Player::setTotalHand()
{
    totalForHand = 0;
}

// returns the sum of the players two cards
int Player::getTotalForHand()
{
    return totalForHand;
}

// picks one additional card for the player
void Player::hit()
{
    string card = getRandomCard();
    int num = getCardsValue(card);

    cout << "You draw: " << num << endl;

    totalForHand += num;

    cout << "New total: " << totalForHand << endl;

    if (totalForHand > 21)
    {
        cout << "You busted. That's rough.\n";
    }
}

// picks one random card for player
string Player::getRandomCard()
{
    int index = rand() % deck.size();
    return deck[index];
}

// uses switch to find cards actual numeric value
int Player::getCardsValue(string card)
{
    if (card == "2") return 2;
    if (card == "3") return 3;
    if (card == "4") return 4;
    if (card == "5") return 5;
    if (card == "6") return 6;
    if (card == "7") return 7;
    if (card == "8") return 8;
    if (card == "9") return 9;
    if (card == "10") return 10;

    if (card == "J" || card == "Q" || card == "K")
    {
        return 10;
    }

    if (card == "A")
    {
        if (isPlayer)
        {
            return allAs();
        }
        else
        {
            return 11;
        }
    }

    return 0;
}

// called if player get A
// asks if they want  A to be 1 or 11
// returns that value
int Player::allAs()
{
    cout << "Luck's on your side, you pulled an Ace.\n";
    cout << "Do you want it to count as 1 or 11?\n";

    while (true)
    {
        string answer;
        getline(cin, answer);

        try
        {
            int choice = stoi(answer);

            if (choice == 1 || choice == 11)
            {
                return choice;
            }
        }
        catch (...) {}

        cout << "Enter 1 or 11, boss.\n";
    }
}