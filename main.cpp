#include "game.h"
#include <iostream>
#include <limits>
#include <thread>
#include <chrono>

void clear_input() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void print_menu() {
    std::cout << "\n=========================\n";
    std::cout << "        BLACKJACK        \n";
    std::cout << "=========================\n";
    std::cout << "1. Nowa gra\n";
    std::cout << "2. Historia gier\n";
    std::cout << "3. Statystyki\n";
    std::cout << "4. Wyczyść dane\n";
    std::cout << "5. Wyjście\n";
    std::cout << "-------------------------\n";
    std::cout << "Wybierz opcję: ";
}

void main_menu(Game& game) {
    bool running = true;

    while (running) {
        print_menu();

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            clear_input();
            std::cout << "Nieprawidłowy wybór.\n";
            continue;
        }

        clear_input();

        switch (choice) {

        case 1:
            game.startNewGame();
            game.main_loop();
            game.finishSession();
            break;

        case 2: {
            bool inHistory = true;

            while (inHistory) {
                std::cout << "\n=== HISTORIA GIER ===\n";
                std::cout << "1. Wyświetl gry\n";
                std::cout << "2. Sortowanie i filtrowanie\n";
                std::cout << "3. Powrót\n";
                std::cout << "Wybierz opcję: ";

                int subChoice;
                std::cin >> subChoice;
                clear_input();

                if (subChoice == 3)
                    break;

                std::string orderBy = "id";
                bool ascending = true;
                int minRounds = 0;
                int minBalance = -1000000;

                if (subChoice == 2) {
                    std::cout << "\nSortuj po:\n";
                    std::cout << "1. ID\n";
                    std::cout << "2. Bilans\n";
                    std::cout << "3. Liczba rund\n";
                    std::cout << "Wybór: ";

                    int s;
                    std::cin >> s;
                    clear_input();

                    if (s == 2) orderBy = "balance";
                    else if (s == 3) orderBy = "rounds_count";

                    std::cout << "Kolejność (1 = rosnąco, 2 = malejąco): ";
                    int o;
                    std::cin >> o;
                    clear_input();
                    ascending = (o == 1);

                    std::cout << "Minimalna liczba rund (0 = brak): ";
                    std::cin >> minRounds;
                    clear_input();

                    std::cout << "Minimalny bilans (np. 0): ";
                    std::cin >> minBalance;
                    clear_input();
                }

                auto history = game.getDatabase().getGameHistorySorted(
                    orderBy, ascending, minRounds, minBalance
                );

                if (history.empty()) {
                    std::cout << "Brak gier spełniających kryteria.\n";
                    continue;
                }

                for (const auto& h : history) {
                    std::cout << "Gra ID: " << h.id
                              << " | Rundy: " << h.rounds
                              << " | Bilans: " << h.balance << "\n";
                }

                std::cout << "\nPodaj ID gry (0 = powrót): ";
                int id;
                std::cin >> id;
                clear_input();

                if (id == 0)
                    continue;

                std::cout << "\n1. Usuń grę z historii\n";
                std::cout << "2. Pokaż rundy\n";
                std::cout << "3. Edytuj wynik rundy\n";
                std::cout << "4. Dodaj nową rundę\n";
                std::cout << "5. Powrót\n";
                std::cout << "Wybierz opcję: ";

                int opt;
                std::cin >> opt;
                clear_input();

                if (opt == 1) {
                    std::cout << "Czy na pewno usunąć grę ID " << id << "? (t/n): ";
                    char c;
                    std::cin >> c;
                    clear_input();

                    if (c == 't' || c == 'T')
                        game.getDatabase().deleteGameById(id);
                }

                else if (opt == 2) {
                    auto rounds = game.getDatabase().getRoundsForGame(id);
                    for (const auto& r : rounds) {
                        std::cout << "Runda " << r.roundNumber << " | "
                                  << (r.result == 1 ? "Wygrana" :
                                      r.result == 0 ? "Remis" : "Przegrana")
                                  << "\n";
                    }
                }

                else if (opt == 3) {
                    int roundNr, newResult;

                    std::cout << "Numer rundy: ";
                    std::cin >> roundNr;
                    clear_input();

                    std::cout << "Nowy wynik (-1 przegrana, 0 remis, 1 wygrana): ";
                    std::cin >> newResult;
                    clear_input();

                    if (newResult < -1 || newResult > 1) {
                        std::cout << "Nieprawidłowa wartość.\n";
                    } else {
                        game.getDatabase().updateRoundResult(id, roundNr, newResult);
                        std::cout << "Runda zaktualizowana.\n";
                    }
                }

                else if (opt == 4) {
                    int roundNr, result;

                    std::cout << "Numer nowej rundy: ";
                    std::cin >> roundNr;
                    clear_input();

                    std::cout << "Wynik (-1 przegrana, 0 remis, 1 wygrana): ";
                    std::cin >> result;
                    clear_input();

                    if (result < -1 || result > 1) {
                        std::cout << "Nieprawidłowy wynik.\n";
                    } else {
                        game.getDatabase().addManualRound(id, roundNr, result);
                        std::cout << "Runda dodana.\n";
                    }
                }
            }
            break;
        }

        case 3:
            game.startStatsThread();
            std::cout << "Liczenie statystyk w tle...\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(200));

            {
                auto stats = game.getCachedStats();
                std::cout << "\n=== STATYSTYKI ===\n";
                std::cout << "Liczba gier: " << stats.gamesCount << "\n";
                std::cout << "Liczba rund: " << stats.roundsCount << "\n";
                std::cout << "Najlepsze saldo: " << stats.maxBalance << "\n";
                std::cout << "Najgorsze saldo: " << stats.minBalance << "\n";
                std::cout << "Winrate: " << stats.winRate << "%\n";
            }
            break;

        case 4: {
            std::cout << "Czy na pewno usunąć WSZYSTKIE dane? (t/n): ";
            char c;
            std::cin >> c;
            clear_input();

            if (c == 't' || c == 'T') {
                game.getDatabase().clearDatabase();
                std::cout << "Dane zostały usunięte.\n";
            } else {
                std::cout << "Anulowano.\n";
            }
            break;
        }

        case 5:
            std::cout << "Kończenie programu.\n";
            running = false;
            break;

        default:
            std::cout << "Nie ma takiej opcji.\n";
        }
    }
}

int main() {
    Game game;
    main_menu(game);
    return 0;
}
