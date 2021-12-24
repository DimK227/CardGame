#include "Follower.hpp"
#include "DeckBuilder.hpp"
#include <iostream>
using namespace std;

Follower::Follower(string new_name, int id) //This is the constructor of class Follower -- The stats ar based on the .txt file tha was given
{
  name=new_name;
  if (id==FOOTSOLDIER) {
    cost=0;
    attackBonus=2;
    defenceBonus=0;
    minimumHonour=1;
    effectBonus=1;
    effectCost=2;
  }
  else if (id==ARCHER) {
    cost=0;
    attackBonus=0;
    defenceBonus=2;
    minimumHonour=1;
    effectBonus=1;
    effectCost=2;
  }
  else if (id==SIEGER) {
    cost=5;
    attackBonus=3;
    defenceBonus=3;
    minimumHonour=2;
    effectBonus=2;
    effectCost=3;
  }
  else if (id==CAVALRY) {
    cost=3;
    attackBonus=4;
    defenceBonus=2;
    minimumHonour=3;
    effectBonus=3;
    effectCost=4;
  }
  else if (id==NAVAL) {
    cost=3;
    attackBonus=2;
    defenceBonus=4;
    minimumHonour=3;
    effectBonus=3;
    effectCost=4;
  }
  else {
    cost=8;
    attackBonus=8;
    defenceBonus=8;
    minimumHonour=6;
    effectBonus=3;
    effectCost=8;
  }
}

int Follower::getType()   //This method returns the type of this card (Follower)
{
  return FOLLOWER;
}

void Follower::print()    //This method prints a follower card
{
    cout << "name: " << name << ",  cost: " << cost << ",  attackBonus: " << attackBonus << ",  defenceBonus: " << defenceBonus << ",  minimumHonour: " << minimumHonour
    << ", effectBonus: " << effectBonus << ",  effectCost: " << effectCost;
    if (isTapped) cout << "     (Tapped)";
    else cout << "      (Untapped)";
    cout << endl;
}
