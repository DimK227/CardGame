#include "GreenCard.hpp"
#include <iostream>
using namespace std;

void GreenCard::Use_Bonus() //Via this method the bonus for the green card is used
{
  attackBonus+=effectBonus;
  defenceBonus+=effectBonus;
}

int GreenCard::get_Effect_cost()    //This method returns the effectCost
{
  return effectCost;
}

int GreenCard::get_defenseBonus()   //This method returns the defenceBonus
{
  return defenceBonus;
}

int GreenCard::get_attackBonus()    //This method returns the attackBonus
{
  return attackBonus;
}

int GreenCard::get_minimumHonour()  //This method returns the minimumHonour
{
  return minimumHonour;
}
