#include "BlackCard.hpp"
#include "GreenCard.hpp"
#include <list>
#pragma once

class Personality : public BlackCard {
  public:
    Personality(std::string new_name,int id);
    void print();
    int getType();
    void Equip(GreenCard& greencard);
    int get_honour();
    int get_max();
    int get_attack();
    int get_defense();
    void kill();
    bool IsDead();
    void die();
    void set_ItemList(Item* item);
    void set_FollowerList(Follower* Follower);
    void Tap_Followers();
    void Decrease_Durability_Items();
    void Decrease_Honour();
    void performSeppuku();
    int get_ItemList_size();
    int get_FollowerList_size();
    Follower* get_FollowerList_j(int j);
    Item* get_ItemList_j(int j);
  private:
    int max;
    int attack;
    int defense;
    int honour;
    bool isDead;
    std::vector <Item*> ItemList;   //A vector that contains all the items that have equipped a personality
  	std::vector <Follower*> FollowerList;    //A vector that contains all the followers that have equipped a personality
};
