#pragma once
#include <string>

class Card {
  public:
    int get_cost();
    void Tap();
    void Untap();
    bool IsTapped();
    std::string get_name();
  protected:
    std::string name;
    int cost;
    bool isTapped;

};
