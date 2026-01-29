#pragma once
#include <sqlite3.h>
#include <string>
#include <vector>

struct GameSessionInfo {
    int id;
    int rounds;
    int balance;
};

struct RoundInfo {
    int roundNumber;
    int result;
};

struct Stats {
    int gamesCount;
    int roundsCount;
    int maxBalance;
    int minBalance;
    double winRate;
};


class Database {
private:
    sqlite3* db;

public:
    Database();
    ~Database();

    void createTables();

    int createGameSession();
    void finishGameSession(int gameId, int roundsCount, int balance);

    std::vector<GameSessionInfo> getGameHistory();
    std::vector<RoundInfo> getRoundsForGame(int gameId);

    void addRound(int gameId, int roundNumber, int result);

    void clearDatabase();
    bool deleteGameById(int gameId);

    Stats getStats();
};
