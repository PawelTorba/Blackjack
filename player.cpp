#include "player.h"

Player::Player(int balance_a):balance(balance_a){}
Player::Player(){}

void Player::update_balance(int value){
    this->balance = this->balance + value;
}

int Player::get_balance(){
    return this->balance;
}

int Player::bet(){
    /*PLACES A BET AND SUBTRACTS THE BET VALUE FROM THE PLAYER'S BALANCE
    RETURNS BET VALUE AS INT*/
    /*ALSO CHECKS IF THERE IS ENOUGH CREDIT TO PLACE THE BET*/

    int bet_value = 0;
    //temporary question
    std::cout << "How much to bet?: " << std::endl;
    //
    std::cin >>  bet_value;
    if (bet_value <= this->balance ){
        this->balance = balance - bet_value;
        return bet_value;
    }
    else {
        std::cout << "Not enough funds for betting, lower the bet" << std::endl;
        return 0;
    }
    return 0;
}

bool Player::hit(Deck& deck){
    /*GETS THE LAST CARD FROM RANDOMIZED DECK, RETURNS "FALSE" IF SUM OF POIINTS IS 
    21 OR ABOVE*/

    Card popped_card = deck.pop_card();

    update_points(popped_card.get_value());

    std::cout<<"Otrzymana karta: " << popped_card.get_color() << ", " << popped_card.get_figure() << ", " << std::endl;
    std::cout<<"Aktualne punkty: " << get_points() << std::endl;

    return bust();
}

Player::Action getDecision() {
    while (true) {
        std::cout << "Wybierz akcję: (h)it lub (s)tand: ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "h" || input == "H") return Player::Action::Hit;
        if (input == "s" || input == "S") return Player::Action::Stand;
        std::cout << "Nieznana akcja — spróbuj jeszcze raz.\n";
    }
}
