#pragma once
#include <string>
#include "GreenCard.hpp"

class Item : public GreenCard {
  public:
    Item(std::string new_name, int id);
    void print();
    int getType();
    void Decrease_Durability();
    int get_durability();
  private:
    int durability;
};
