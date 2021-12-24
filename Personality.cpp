#include <iostream>
#include "Personality.hpp"
#include "DeckBuilder.hpp"
using namespace std;

Personality:: Personality(string new_name,int id) //This is the constructor of class Personality -- The stats are based on the .txt file that was given
{
  max=0;
  isRevealed=false;
  isDead = false;
  name=new_name;
  if (id==ATTACKER) {
    cost=5;
    attack=3;
    defense=2;
    honour=2;
  }
  else if (id==DEFENDER) {
    cost=5;
    attack=2;
    defense=3;
    honour=2;
  }
  else if (id==SHOGUN) {
    cost=15;
    attack=10;
    defense=5;
    honour=8;
  }
  else if (id==CHANCELLOR) {
   cost=15;
   attack=5;
   defense=10;
   honour=8;
  }
  else {
    cost=30;
    attack=20;
    defense=20;
    honour=12;
  }
}

void Personality::print()     //This method prints a Personality card
{
  if (isRevealed && !isDead) {
    cout << "name: " << name << ",  cost: " << cost << ",  attack: " << attack << ",  defense: " << defense << ",  honour: " << honour;
    if (isTapped) cout << "     (Tapped,";
    else cout << "      (Untapped,";
    if (isRevealed) cout << "Revealed)";
    else cout << "UnRevealed)";
    cout << endl;
  }
  else cout << "UnRevealed Card" << endl;
}

int Personality::getType()  //This method returns the type of this card (Personality)
{
  return PERSONALITY;
}

void Personality::Equip(GreenCard& greencard)     //Via this method a greencard gets equipped with personality
{
  max++;                          //Max shows how many times a personality has equipped (Remember 3 is the maximum)
  attack+=greencard.get_attackBonus();
                                                  //Apply the bonuses
  defense+=greencard.get_defenseBonus();
}

int Personality::get_honour()       //This method returns the honour of a personality
{
  return honour;
}

int Personality::get_max()        //This method returns how many times a personality has been equipped
{
  return max;
}

int Personality::get_attack()   //This method returns the attack of a personality
{
  return attack;
}

int Personality::get_defense()    //This method returns the defense of a personality
{
  return defense;
}

void Personality::die()       //This method "kills a personality"
{
  isDead=true;
}

bool Personality::IsDead()    //This method if a personality is dead
{
  return isDead;
}

void Personality::set_ItemList(Item* item)      //This method inserts an item to the ItemList (a vector that has all items which have equipped a personality)
{
  ItemList.push_back(item);
}

void Personality::set_FollowerList(Follower* follower)    //This method inserts an item to the FollowerList (a vector that has all followers who have equipped a personality)
{
  FollowerList.push_back(follower);
}

void Personality::Tap_Followers()               //This method taps followers
{
  for (int i=0; i<FollowerList.size(); i++) {
    FollowerList[i]->Tap();
  }
}

void Personality::Decrease_Durability_Items()   //This method decreases the durability of all items
{
  for (int i=0; i<ItemList.size(); i++) {   //For all items
    ItemList[i]->Decrease_Durability();     //Decrease the durability
    if (ItemList[i]->get_durability()==0){    //If its durability is 0 delete it
     ItemList.erase(ItemList.begin()+i);
     max--;
     attack-=ItemList[i]->get_attackBonus();
     defense-=ItemList[i]->get_defenseBonus();
    }
  }

}

void Personality::Decrease_Honour()   //This method decreases the honour of a personality by one
{
  honour--;
}

void Personality::performSeppuku()    //Via this methoid a personality performs Seppuku (a.k.a He commits suiside to save his family honour)
{
  cout << "I, " << name << ", must save my family honour" << endl;
  this->die();
}

int Personality::get_ItemList_size()    //This function returns how many items have equipped the personality
{
  return ItemList.size();
}

int Personality::get_FollowerList_size()    //This function returns how many followers have equipped the personality
{
  return FollowerList.size();
}

Follower* Personality::get_FollowerList_j(int j)      //This function returns a specific item that has equipped the personality
{
  return FollowerList[j];
}

Item* Personality::get_ItemList_j(int j)          //This function returns a specific item follower has equipped the personality
{
  return ItemList[j];
}
