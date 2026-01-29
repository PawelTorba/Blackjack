#include "database.h"
#include <iostream>

Database::Database() : db(nullptr) {
    if (sqlite3_open("history.db", &db) != SQLITE_OK) {
        std::cerr << "Cannot open database\n";
    }
    createTables();
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::createTables() {
    const char* sql =
        "CREATE TABLE IF NOT EXISTS game_session ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "rounds_count INTEGER,"
        "balance INTEGER);"

        "CREATE TABLE IF NOT EXISTS round ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "game_id INTEGER,"
        "round_number INTEGER,"
        "result INTEGER,"
        "FOREIGN KEY(game_id) REFERENCES game_session(id));";

    char* errMsg = nullptr;
    sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (errMsg) {
        std::cerr << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int Database::createGameSession() {
    const char* sql = "INSERT INTO game_session (rounds_count, balance) VALUES (0, 0);";
    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);
    return static_cast<int>(sqlite3_last_insert_rowid(db));
}

void Database::finishGameSession(int gameId, int roundsCount, int balance) {
    std::string sql =
        "UPDATE game_session SET rounds_count = " +
        std::to_string(roundsCount) +
        ", balance = " + std::to_string(balance) +
        " WHERE id = " + std::to_string(gameId) + ";";

    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
}

void Database::addRound(int gameId, int roundNumber, int result) {
    std::string sql =
        "INSERT INTO round (game_id, round_number, result) VALUES (" +
        std::to_string(gameId) + ", " +
        std::to_string(roundNumber) + ", " +
        std::to_string(result) + ");";

    sqlite3_exec(db, sql.c_str(), nullptr, nullptr, nullptr);
}

std::vector<GameSessionInfo> Database::getGameHistory() {
    std::vector<GameSessionInfo> history;

    const char* sql = "SELECT id, rounds_count, balance FROM game_session;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            GameSessionInfo info;
            info.id = sqlite3_column_int(stmt, 0);
            info.rounds = sqlite3_column_int(stmt, 1);
            info.balance = sqlite3_column_int(stmt, 2);
            history.push_back(info);
        }
    }

    sqlite3_finalize(stmt);
    return history;
}

std::vector<RoundInfo> Database::getRoundsForGame(int gameId) {
    std::vector<RoundInfo> rounds;

    std::string sql =
        "SELECT round_number, result FROM round WHERE game_id = " +
        std::to_string(gameId) + ";";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            RoundInfo r;
            r.roundNumber = sqlite3_column_int(stmt, 0);
            r.result = sqlite3_column_int(stmt, 1);
            rounds.push_back(r);
        }
    }

    sqlite3_finalize(stmt);
    return rounds;
}
