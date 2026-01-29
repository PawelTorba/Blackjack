#include "game.h"
#include <iostream>
#include <limits>

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
    std::cout << "4. Eksport danych\n";
    std::cout << "5. Wyczyść historie i statystyki\n";
    std::cout << "6. Wyjście\n";
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
                std::cout << "\n=== HISTORIA GIER ===\n";

                auto history = game.getDatabase().getGameHistory();

                if (history.empty()) {
                    std::cout << "Brak zapisanych gier.\n";
                    break;
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
                    break;

                std::cout << "\n1. Usuń grę z historii\n";
                std::cout << "2. Pokaż rundy\n";
                std::cout << "3. Powrót\n";
                std::cout << "Wybierz opcję: ";

                int option;
                std::cin >> option;
                clear_input();

                switch (option) {
                case 1: {
                    std::cout << "Czy na pewno chcesz usunąć grę ID "
                            << id << "? (t/n): ";
                    char c;
                    std::cin >> c;
                    clear_input();

                    if (c == 't' || c == 'T') {
                        if (game.getDatabase().deleteGameById(id))
                            std::cout << "Gra została usunięta.\n";
                        else
                            std::cout << "Błąd podczas usuwania gry.\n";
                    } else {
                        std::cout << "Anulowano.\n";
                    }
                    break;
                }

                case 2: {
                    auto rounds = game.getDatabase().getRoundsForGame(id);

                    if (rounds.empty()) {
                        std::cout << "Brak rund dla tej gry.\n";
                        break;
                    }

                    std::cout << "\nRundy gry " << id << ":\n";
                    for (const auto& r : rounds) {
                        std::cout << "Runda " << r.roundNumber << " | ";

                        if (r.result == 1) std::cout << "Wygrana";
                        else if (r.result == 0) std::cout << "Remis";
                        else std::cout << "Przegrana";

                        std::cout << "\n";
                    }
                    break;
                }

                case 3:
                    break;

                default:
                    std::cout << "Nieprawidłowa opcja.\n";
                }

                break;
            }

        case 3: {
            auto stats = game.getDatabase().getStats();

            std::cout << "\n=== STATYSTYKI ===\n";

            if (stats.gamesCount == 0) {
                std::cout << "Brak danych statystycznych.\n";
                break;
            }

            std::cout << "Liczba gier: " << stats.gamesCount << "\n";
            std::cout << "Liczba rund: " << stats.roundsCount << "\n";
            std::cout << "Najlepsze saldo: " << stats.maxBalance << "\n";
            std::cout << "Najgorsze saldo: " << stats.minBalance << "\n";
            std::cout << "Winrate: " << stats.winRate << "%\n";

            break;
        }

        case 4:
            std::cout << "\n[Eksport danych] — w trakcie implementacji.\n";
            break;

        case 5: {
            std::cout << "\nCzy na pewno chcesz usunąć WSZYSTKIE dane? (t/n): ";
            char c;
            std::cin >> c;
            clear_input();

            if (c == 't' || c == 'T') {
                game.getDatabase().clearDatabase();
                std::cout << "Dane zostały usunięte.\n";
            }
            else {
                std::cout << "Anulowano.\n";
            }
            break;
        }

        case 6:
            std::cout << "\nDo zobaczenia!\n";
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