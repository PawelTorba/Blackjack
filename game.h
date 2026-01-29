#include "deck.h"
#include "player.h"

class Game {
private:
    Deck deck;
    Player player;
    Dealer dealer;

public:
    void main_loop();
};