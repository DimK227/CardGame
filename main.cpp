#include "GameBoard.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;




int main()
{
  vector<Player*> players;
  int number,i;
  string name;
  srand((time(NULL)));
  GameBoard gameboard;
  gameboard.initializeGameBoard();      //Prepare the game
  gameboard.printGameStatistics();      //Print the statistics
  gameboard.gameplay();                 //PLAY
  return 0;
}
