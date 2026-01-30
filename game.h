#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include "dealer.h"
#include "database.h"
#include <thread>
#include <mutex>

class Game {
private:
    Deck deck;
    Player player;
    Dealer dealer;
    Database database;
    int gameId;
    int roundCounter;

    Stats cachedStats;
    std::thread statsThread;
    std::mutex statsMutex;
    bool statsReady;

public:
    Game();
    void main_loop();
    ~Game();
    Database& getDatabase();
    void finishSession();
    void startNewGame();
    void startStatsThread();
    Stats getCachedStats();
};



#endif
