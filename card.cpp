#include "card.h"

void Card::set_value(int value){
    this->value = value;
}
int Card::get_value(){
    return this->value;
}

void Card::set_color(std::string& color){
    this->color = color;
}
std::string Card::get_color(){
    return this->color;
}

void Card::set_figure(std::string& figure){
    this->figure = figure;
}
std::string Card::get_figure(){
    return this-> figure;
}

Card::Card(int value, std::string& color, std::string& figure)
    : value(value),
      color(color),
      figure(figure)
{}
Card::Card(){}