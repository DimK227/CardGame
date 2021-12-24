#pragma once
#include "Card.hpp"
#include "Follower.hpp"
#include "Item.hpp"
#include <vector>
//class Card;

class BlackCard : public Card {
  public:
    void hide();
    void reveal();
    virtual void print()=0;
    virtual int getType()=0;
    bool IsRevealed();
  protected:
    bool isRevealed;
    std::vector<Follower> follower;
    std::vector<Item> item;

};
