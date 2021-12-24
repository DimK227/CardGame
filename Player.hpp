#include "DeckBuilder.hpp"
#include "Stronghold.hpp"
#include "vector"
#pragma once

class Player {
  public:
    Player(std::string new_name);
    string Get_name();
    int Get_money();
    int Get_honour() const;
    int Get_numberOfProvinces();
    int get_army();
    void set_Hand();
    void hide_provinces();
    void revealProvinces();
    void Untap_Everything();
    void drawFateCard();
    void kill_personality(int number);
    void throw_handCard(int number);
    void printHand();
    void printArena();
    void printArmy();
    void printHoldings();
    void printProvinces();
    void harvest(std::string name);
    void take_harvestValue();
    BlackCard* get_province_i(int number);
    Personality* get_army_i(int number);
    GreenCard* get_hand_i(int number);
    int get_handSize();
    int get_initial_defense();
    void destroy_province(BlackCard* new_province);
    void Pay(int new_money);
    void Buy_a_province(BlackCard* province);
    bool All_cards_tapped();
    void Check_for_connection(Holding* new_holding);
    void Tap_cards();
    void discardSurplusFateCards();
  private:
    std::string name;
    DeckBuilder *decks;
    std::vector<BlackCard *> province;
    int numberOfProvinces;
    std::vector<GreenCard *> hand;
    std::vector<Personality *> army;
    std::vector<Holding *> holdings;
    Stronghold* stronghold;
    int money;
    int honour;
};
