#include "dealer.h"
#include "deck.h"

Dealer::Dealer():current_points(0){}
Dealer::~Dealer(){}
bool Dealer::hit(Deck& deck){

    Card popped_card = deck.pop_card();

    update_points(popped_card.get_value());

    std::cout<<"Dealer otrzymał kartę: " << popped_card.get_color() << ", " << popped_card.get_figure() << ", " << std::endl;
    std::cout<<"Aktualne punkty dealera: " << get_points() << std::endl;

    return bust();
}
bool Dealer::stand(){
    return false;
}

bool Dealer::bust() {
    return current_points > 21;
}

void Dealer::update_points(int value){
    this->current_points = current_points + value;
}

void Dealer::reset_points(){
    this->current_points = 0;
}

int Dealer::get_points(){
    return this->current_points;
}

Dealer::Action Dealer::getDecision() {
        if (this->current_points < 17) {
        return Dealer::Action::Hit;
    }
    return Dealer::Action::Stand;
}