#include "game.h"
#include <iostream>
#include <limits>


Game::Game() : player(1000), roundCounter(0) {}

void Game::main_loop() {
    bool play_again = true;
    player.update_balance(player.get_balance() * (-1) + 1000);

    std::cout << "=== BLACKJACK ===\n";

    while (play_again) {
        deck.generate_deck();
        deck.shuffle_cards();

        player.reset_points();
        dealer.reset_points();

        std::cout << "\n--- Nowa runda ---\n";
        std::cout << "Saldo gracza: " << player.get_balance() << "\n";

        int bet = player.bet();
        if (bet == 0) continue;

        std::cout << "\n--- Pierwsze rozdanie ---\n";
        player.hit(deck);
        dealer.hit(deck);
        player.hit(deck);

        std::cout << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (!player.bust()) {
            if (player.getDecision() == Dealer::Action::Stand)
                break;

            if (player.hit(deck))
                break;
        }

        if (!player.bust()) {
            std::cout << "\nRuch dealera...\n";
            while (dealer.getDecision() == Dealer::Action::Hit) {
                if (dealer.hit(deck))
                    break;
            }
        }

        int p = player.get_points();
        int d = dealer.get_points();

        int result = 0;
        std::cout << "\n--- WYNIK ---\n";
        std::cout << "Gracz: " << p << " | Dealer: " << d << "\n";

        if (p > 21) {
            std::cout << "Przegrana\n";
            result = -1;
        }
        else if (d > 21 || p > d) {
            std::cout << "Wygrana\n";
            player.update_balance(bet * 2);
            result = 1;
        }
        else if (p == d) {
            std::cout << "Remis\n";
            player.update_balance(bet);
            result = 0;
        }
        else {
            std::cout << "Dealer wygrywa\n";
        }
        roundCounter++;
        database.addRound(gameId, roundCounter, result);

        std::cout << "\nZagrać jeszcze raz? (t/n): ";
        char c;
        std::cin >> c;
        std::cin.ignore();

        play_again = (c == 't' || c == 'T');
    }
    
}

Game::~Game() {}

Database& Game::getDatabase() {
    return database;
}

void Game::finishSession() {
    if (gameId == -1) return;   

    database.finishGameSession(
        gameId,
        roundCounter,
        player.get_balance()
    );

    gameId = -1; 
}

void Game::startNewGame() {
    roundCounter = 0;
    player.update_balance(1000 - player.get_balance()); 
    gameId = database.createGameSession();
}