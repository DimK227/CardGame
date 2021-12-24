#pragma once
#include "GreenCard.hpp"
#include <string>

//class GreenCard;

class Follower : public GreenCard {
  public:
    Follower(std::string new_name, int id);
    int getType();
    void print();
  private:
};
