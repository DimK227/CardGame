#include "Holding.hpp"
#pragma once

class Stronghold : public Holding {
  public:
    Stronghold(int m, int d, int h);
    int Get_initialMoney();
    int Get_initialDefense();
    int Get_startingHonour();
  private:
    int initialMoney;
    int initialDefense;
    int startingHonour;
};
