#include "Card.hpp"
#include <iostream>
using namespace std;


int Card::get_cost()    //This method returns the cost of a card
{
  return cost;
}

void Card::Tap()    //This method taps a card
{
  isTapped=true;
}

void Card::Untap()   //This method untaps a card
{
  isTapped=false;
}

bool Card::IsTapped()     //This method checks if a card is tapped
{
  return isTapped;
}

string Card::get_name()   //This method returns the name of the card
{
  return name;
}
