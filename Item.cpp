#include "DeckBuilder.hpp"
#include "Item.hpp"
#include "GreenCard.hpp"
#include <iostream>
using namespace std;


Item::Item(string new_name, int id) //This is the constructor of class Item -- The stats are based on .txt file that was given
{
  name=new_name;
  if (id==KATANA) {
    cost=0;
    attackBonus=2;
    defenceBonus=0;
    minimumHonour=1;
    effectBonus=1;
    effectCost=2;
    durability=3;
  }
  else if (id==SPEAR) {
    cost=0;
    attackBonus=0;
    defenceBonus=2;
    minimumHonour=1;
    effectBonus=1;
    effectCost=2;
    durability=3;
  }
  else if (id==BOW) {
    cost=2;
    attackBonus=2;
    defenceBonus=2;
    minimumHonour=2;
    effectBonus=3;
    effectCost=4;
    durability=5;
  }
  else if (id==NINJATO) {
    cost=4;
    attackBonus=3;
    defenceBonus=3;
    minimumHonour=3;
    effectBonus=2;
    effectCost=2;
    durability=4;
  }
  else {
    cost=8;
    attackBonus=5;
    defenceBonus=5;
    minimumHonour=3;
    effectBonus=3;
    effectCost=3;
    durability=8;
  }
}

void Item::print()      //This method prints an item card
{
    cout << "name: " << name << ",  cost: " << cost << ",  attackBonus: " << attackBonus << ",  defenceBonus: " << defenceBonus << ",  minimumHonour: " << minimumHonour
    << ", effectBonus: " << effectBonus << ",  effectCost: " << effectCost << ",  durability: " << durability;
    if (isTapped) cout << "     (Tapped";
    else cout << "      (Untapped";
    cout << ")" << endl;
}

int Item::getType()   //This method returns the type of this card (Item)
{
  return ITEM;
}

void Item::Decrease_Durability()    //This method deacreases the durability by one
{
  durability--;
}

int Item::get_durability()    //This method returns the durability of an Item
{
  return durability;
}
