#pragma once
#include "Card.hpp"
#include <string>

class GreenCard : public Card {
  public:
    virtual void print()=0;
    virtual int getType()=0;
    int get_Effect_cost();
    void Use_Bonus();
    int get_attackBonus();
    int get_defenseBonus();
    int get_minimumHonour();
  protected:
    int attackBonus;
    int defenceBonus;
    int effectBonus;
    int minimumHonour;
    std::string CardText;
    int effectCost;
};
