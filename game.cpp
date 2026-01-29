#include "game.h"
#include <iostream>
#include <limits>

Game::Game() : player(1000) {}

void Game::main_loop() {
    bool play_again = true;
    player.update_balance(player.get_balance() * (-1) + 1000);

    std::cout << "=== BLACKJACK ===\n";

    while (play_again) {
        // przygotowanie rundy
        deck.generate_deck();
        deck.shuffle_cards();

        player.reset_points();
        dealer.reset_points();

        std::cout << "\n--- Nowa runda ---\n";
        std::cout << "Saldo gracza: " << player.get_balance() << "\n";

        int bet = player.bet();
        if (bet == 0) continue;

        // rozdanie początkowe
        std::cout << "\n--- Pierwsze rozdanie ---\n";
        player.hit(deck);
        dealer.hit(deck);
        player.hit(deck);

        // ====== RUCH GRACZA ======
        std::cout << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (!player.bust()) {
            if (player.getDecision() == Dealer::Action::Stand)
                break;

            if (player.hit(deck))
                break;
        }

        // ====== RUCH DEALERA ======
        if (!player.bust()) {
            std::cout << "\nRuch dealera...\n";
            while (dealer.getDecision() == Dealer::Action::Hit) {
                if (dealer.hit(deck))
                    break;
            }
        }

        // ====== WYNIK ======
        int p = player.get_points();
        int d = dealer.get_points();

        std::cout << "\n--- WYNIK ---\n";
        std::cout << "Gracz: " << p << " | Dealer: " << d << "\n";

        if (p > 21) {
            std::cout << "Przegrana\n";
        }
        else if (d > 21 || p > d) {
            std::cout << "Wygrana\n";
            player.update_balance(bet * 2);
        }
        else if (p == d) {
            std::cout << "Remis\n";
            player.update_balance(bet);
        }
        else {
            std::cout << "Dealer wygrywa\n";
        }

        // ====== KOLEJNA RUNDA ======
        std::cout << "\nZagrać jeszcze raz? (t/n): ";
        char c;
        std::cin >> c;
        std::cin.ignore();

        play_again = (c == 't' || c == 'T');
    }

    //std::cout << "\nDzięki za grę!\n";
}
