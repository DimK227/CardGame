#include "Player.hpp"

#pragma once

class GameBoard {
  public:
    void initializeGameBoard();
    void printGameStatistics();
    void gameplay();
    bool checkWinningCondition();
  private:

    void startingPhase();
    void equipPhase();
    void battlePhase();
    void economyPhase();
    void finalPhase();
    std::vector<Player*> player;
    int diffCards;
};
