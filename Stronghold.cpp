#include "Stronghold.hpp"
#include "DeckBuilder.hpp"
#include <iostream>
using namespace std;

Stronghold::Stronghold(int m, int d, int h) :   //This is the constructor of Stronghold
    Holding("Stronghold",STRONGHOLD)
{
  initialMoney=m;
  initialDefense=d;
  startingHonour=h;
}

int Stronghold::Get_initialMoney()    //This function returns the initialMoney of a player
{
  return initialMoney;
}

int Stronghold::Get_initialDefense()    //This function returns the initialDefense of the Stronghold
{
  return initialDefense;
}

int Stronghold::Get_startingHonour()    //This function returns the startingHonour of a player
{
  return startingHonour;
}
