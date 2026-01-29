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
            game.main_loop();
            break;

        case 2:
            std::cout << "\n[Historia gier] — w trakcie implementacji.\n";
            break;

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