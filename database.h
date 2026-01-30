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

    bool updateRoundResult(int gameId, int roundNumber, int newResult);
    bool addManualRound(int gameId, int roundNumber, int result);   

    std::vector<GameSessionInfo> getGameHistory();
    std::vector<RoundInfo> getRoundsForGame(int gameId);
    std::vector<GameSessionInfo> getGameHistorySorted(
        const std::string& orderBy,
        bool ascending,
        int minRounds,
        int minBalance);

    void addRound(int gameId, int roundNumber, int result);

    void clearDatabase();
    bool deleteGameById(int gameId);

    Stats getStats();
};
