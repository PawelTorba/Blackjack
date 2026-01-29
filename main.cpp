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
                std::cout << "\n=== HISTORIA GIER ===\n";

                auto history = game.getDatabase().getGameHistory();

                if (history.empty()) {
                    std::cout << "Brak zapisanych gier.\n";
                    break;
                }

                for (const auto& h : history) {
                    std::cout << "Gra ID: " << h.id
                            << " | Rundy: " << h.rounds
                            << " | Bilans końcowy: " << h.balance << "\n";
                }

                std::cout << "\nPodaj ID gry, aby zobaczyć rundy (0 = powrót): ";
                int id;
                std::cin >> id;
                clear_input();

                if (id == 0) break;

                auto rounds = game.getDatabase().getRoundsForGame(id);

                std::cout << "\nRundy gry " << id << ":\n";
                for (const auto& r : rounds) {
                    std::cout << "Runda " << r.roundNumber << " | Wynik: ";

                    if (r.result == 1) std::cout << "Wygrana";
                    else if (r.result == 0) std::cout << "Remis";
                    else std::cout << "Przegrana";

                    std::cout << "\n";
                }

                break;
            }

        case 3:
            std::cout << "\n[Statystyki] — w trakcie implementacji.\n";
            break;

        case 4:
            std::cout << "\n[Eksport danych] — w trakcie implementacji.\n";
            break;

        case 5:
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