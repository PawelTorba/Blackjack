#ifndef DEALER_H
#define DEALER_H

#include "deck.h"
class Dealer{
    protected:
        int current_points;
    public:
        bool hit(Deck& deck);
        bool stand();
        bool bust();
        void update_points(int value);
        void reset_points();
        int get_points();

    Dealer();
    ~Dealer();
};

#endif