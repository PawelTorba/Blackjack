#ifndef CARD_H
#define CARD_H
#include "string.h"
#include <iostream>

class Card{
    protected:
        int value;
        std::string color;
        std::string figure;
    public:
    Card();
    Card(int value, std::string& color, std::string& figure);

    void set_value(int value);
    int get_value();

    void set_color(std::string& color);
    std::string get_color();

    void set_figure(std::string& figure);
    std::string get_figure();

};


#endif