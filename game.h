#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include "dealer.h"
#include "database.h"

class Game {
private:
    Deck deck;
    Player player;
    Dealer dealer;
    Database database;
    int gameId;
    int roundCounter;

public:
    Game();
    void main_loop();
    ~Game();
    Database& getDatabase();
    void finishSession();
    void startNewGame();
};



#endif
