#include "BlackCard.hpp"
#pragma once

class Holding : public BlackCard {
  public:
    Holding(std::string new_name,int id);
    int Get_defense();
    void print();
    int getType();
    int Get_harvestValue();
    void set_upperHolding(Holding* new_upperHolding);
    void set_subHolding(Holding* new_subHolding);
    void Increase_harvestValue(int bonus);
    bool IsSubFree();
    bool IsUpperFree();
  private:
    int harvestValue;
    Holding* subHolding;
    Holding* upperHolding;
    bool isSubFree;
    bool isUpperFree;
};
