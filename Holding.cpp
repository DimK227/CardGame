#include "DeckBuilder.hpp"
#include "Holding.hpp"
#include <iostream>
using namespace std;

Holding::Holding(string new_name,int id)    //This is the constructor of a Holding. The stats are based on the data of the .txt that was given
{
  isRevealed=false;
  isSubFree=true;
  isUpperFree=true;
  name=new_name;
  if (id==SOLO) {
    cost=2;
    harvestValue=2;
  }
  else if (id==PLAIN) {
    cost=2;
    harvestValue=2;
  }
  else if (id==FARMS) {
    cost=3;
    harvestValue=4;
  }
  else if (id==MINE) {
    cost=5;
    harvestValue=3;
  }
  else if (id==GOLD_MINE) {
    cost=7;
    harvestValue=3;
  }
  else if (id==CRYSTAL_MINE) {
    cost=12;
    harvestValue=6;
  }
  else {
    harvestValue=5;
  }
}

void Holding::print()   //This method prints a Holding card
{
  if (isRevealed==true) {
    cout << "name: " << name << ",  cost: " << cost << ",  harvestValue: " << harvestValue;
    if (isTapped) cout << "     (Tapped,";
    else cout << "      (Untapped,";
    if (isRevealed) cout << "Revealed)" << endl;
    else cout << "UnRevealed)" << endl;
  }
  else cout << "UnRevealed Card" << endl;
}

int Holding::getType()    //This method returns the type of this card (Holding)
{
  return HOLDING;
}

int Holding::Get_harvestValue()   //This method returns the harvestValue
{
  return harvestValue;
}

void Holding::set_upperHolding(Holding* new_upperHolding) //This method connects 2 holdings
{
  upperHolding=new_upperHolding;
  isUpperFree=false;
}

void Holding::set_subHolding(Holding* new_subHolding)   //This method connects 2 holdings
{
  subHolding=new_subHolding;
  isSubFree=false;
}

void Holding::Increase_harvestValue(int bonus)        //This method increases harvestValue by the bonus
{
  harvestValue+=bonus;
}


bool Holding::IsSubFree()       //This method returns if a holding has been connected with subHolding
{
  return isSubFree;
}

bool Holding::IsUpperFree()   //This method returns if a holding has been connected with upperHolding
{
  return isUpperFree;
}
