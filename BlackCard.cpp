#include "BlackCard.hpp"
#include <iostream>
using namespace std;


void BlackCard::hide()
{
  isRevealed=false;
}

void BlackCard::reveal()
{
  isRevealed=true;
}

bool BlackCard::IsRevealed()
{
  return isRevealed;
}
