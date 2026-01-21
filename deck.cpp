#include "deck.h"
#include <algorithm>
#include <random>

Deck::Deck(){}

void Deck::generate_deck(){
    /*GENERATES A STANDARD 54 CARD DECK - NOT RANDOM*/
    cards.clear();
    std::string colors[4] = {"clubs", "diamonds", "hearts", "spades"};
    
    std::string figures[13] = {"ace", "2", "3", "4", "5",  "6", 
    "7", "8", "9", "10", "jack", "queen", "king"};

    int i = 0;
    for(int j = 0; j < 4; j++){
        for (int x = 0; x < 13; x++){
            int value;
            if(x < 10){
                value = x+1;
            }
            else 
            {
                value = 10;
            }
            cards.emplace_back(value, colors[j], figures[x]);
            i++;
        }
    }
}

std::vector<Card>& Deck::get_cards(){
    return this->cards;   
}

void Deck::shuffle_cards(){
    /*RANDOMIZES GENERATED DECK*/
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::shuffle(cards.begin(), cards.end(), gen);

}
Card Deck::pop_card(){
    /*POPS LAST CARD FROM THE DECK*/
    Card card_temp = this->cards.back();
    this->cards.pop_back();
    return card_temp;
}