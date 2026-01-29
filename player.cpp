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

    int bet_value = 0;
    std::cout << "Wpisz stawke: ";
    //
    std::cin >>  bet_value;
    if (bet_value <= this->balance ){
        this->balance = balance - bet_value;
        return bet_value;
    }
    else {
        std::cout << "Brak wystarczających funduszy, zmniejsz stawke." << std::endl;
        return 0;
    }
    return 0;
}

bool Player::hit(Deck& deck){

    Card popped_card = deck.pop_card();

    update_points(popped_card.get_value());

    std::cout<<"Otrzymana karta: " << popped_card.get_color() << ", " << popped_card.get_figure() << ", " << std::endl;
    std::cout<<"Aktualne punkty: " << get_points() << std::endl;

    return bust();
}

Player::Action Player::getDecision() {
    while (true) {
        std::cout << "Wybierz akcję: (h)it lub (s)tand: ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "h" || input == "H") return Player::Action::Hit;
        if (input == "s" || input == "S") return Player::Action::Stand;
        std::cout << "Nieznana akcja — spróbuj jeszcze raz.\n";
    }
}
