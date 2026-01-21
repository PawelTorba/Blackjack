#ifndef PLAYER_H
#define PLAYER_H

#include "dealer.h"

class Player : public Dealer{
    private:
        int balance;
    public:
        void update_balance(int value);
        void double_down(); //TO DO
        void surrender(); //TO DO
        int get_balance(); 
        Player(int balance);
        Player();
        int bet();
        bool hit(Deck& deck);
    };

#endif