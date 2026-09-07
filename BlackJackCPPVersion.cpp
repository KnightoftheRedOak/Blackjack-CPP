// Heather Roys
// IT-312
// Card Game Score Tracker
// Date: 4/9/26
//
// I made a blackjack style game after watching Michael Jordan talk
// about playing blackjack even though, yeah, I don't gamble at all.
// This felt like a good excuse to try. Of course, I had to set it in
// a backroom, Jersey style mafia game, aka Fat Tony's.
//
// I start by asking for the user's name and putting that into the
// vector of allPlayers. I then add the rest of the crew by looping
// through however many "crew members" the user says they have.
// I add those names to allPlayers as well. In addToLedger, I loop
// through allPlayers and write each name to ledger.txt.
//
// For the game, I pick random cards from a string vector called deck
// in the Player class. Each player gets two cards and a total.
// The user can hit or stay. After each hand, results are written
// to the ledger file.
//
// The main game loop is in GameManager and loops through allPlayers.
// I added a feature to press space between turns, and the user can
// choose to hit or stay during their turn.
//
// At the end of each round, I call resetTotalHandForEachPlayer to
// reset totals back to zero for the next round.
//
// One thing this helped me understand better was the difference
// between passing by pointer and passing by reference.
// I found that if I needed something that can change,
// like the current leader, I used a pointer since the leader
// updates over time. If I just needed access to existing data,
// like a player's total card sum, I used pass by reference
// to work with the original data in the class.

#include "GameManager.h"

int main()
{
    GameManager game;

    game.addUserToPlayerList();
    game.getNames();
    game.addToLedger();
    game.playGame();

    return 0;
}