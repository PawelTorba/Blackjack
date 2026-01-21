#include <iostream>
#include "player.h"
#include "dealer.h"
#include "deck.h"

void game_cli(std::string gamemode = ""){

    int bet = 0;
    Dealer dealer;
    Player player(1000);

    while(true)
    {

        std::cout << "==========================================" << std::endl;
        std::cout << "Current balance: " << player.get_balance() << std::endl;

        Deck deck;
        deck.generate_deck();
        deck.shuffle_cards();

        bet = player.bet();

        dealer.hit(deck);

        player.hit(deck);
        if(player.hit(deck) == false){
            break;
        }
        
        char action;

        while(true){
            std::cout<<std::endl;
            std::cout << "Select action: 'S' - stand; 'H' - hit: "; 
            std::cin>> action;
            if (action == 'S'){
                player.stand();
                break;
            }
            else if (action == 'H'){
                if(player.hit(deck) == false){
                    std::cout << "YOU LOST" << std::endl;
                    break;
                }
            } 
        }
        std::cout << "\n" << std::endl;
        //std::cout << "DEBUG: DEALER PKT: " << dealer.get_points() <<std::endl;
        
        while (dealer.get_points() <= 16 && dealer.get_points() < player.get_points() && player.bust() == true) {
                //std::cout << "DEBUG: PETLA DECYZJI DEALERA" << std::endl;
                if(dealer.hit(deck) == false){
                    player.update_balance(2 * bet);
                }
            }

        std::cout << "\n" << std::endl;

        if(player.get_points() > dealer.get_points() && player.bust() == true){
                std::cout << "YOU WON!" << std::endl;
                player.update_balance(2 * bet);
            }
        else if(player.get_points() == dealer.get_points() && player.bust() == true){
                std::cout << "DRAW" << std::endl;
                player.update_balance(bet/2);
        }
        else{
            std::cout << "YOU LOST" << std::endl;
        }

            bet = 0;
            player.update_points(player.get_points() * -1);
            dealer.update_points(dealer.get_points() * -1);
            if(player.get_balance() <= 0){
                std::cout << "NO MORE FUNDS - GAME OVER" << std::endl;
                break;
            }
        }
        
    }

int main(){
    //game_cli();
    
    
    return 0;
}
