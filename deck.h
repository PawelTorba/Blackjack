#ifndef DECK_H
#define DECK_H
#include <vector>
#include "card.h"

class Deck{

    private:
        std::vector<Card> cards;
    public:
        Deck();
        std::vector<Card>& get_cards();
        void generate_deck();
        void shuffle_cards();
        Card pop_card();
};

#endif