#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include "dealer.h"

class Game {
private:
    Deck deck;
    Player player;
    Dealer dealer;

public:
    Game();
    void main_loop();
};

#endif
