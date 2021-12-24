//#ifndef _DECKBUILDER_HPP_
//#define _DECKBUILDER_HPP_
#pragma once
#include <list>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <ctime>
#include <cstdlib>

#include "GreenCard.hpp"
#include "BlackCard.hpp"
#include "Personality.hpp"
#include "Holding.hpp"
#include "Follower.hpp"
#include "Item.hpp"

//The numbers are the costs of the mine. Only mines have cost eqaul to 5, only gold mines have cost equal to 7 and only crystal mines have cost equal to 12
//So if a holding has cost equal to 5 is mine etc.
#define mine 5
#define gold_mine 7
#define crystal_mine 12


#define DECKSIZE          40
#define MAXDECKSIZE       60
#define HAND 6

#define NO_PERSONALITIES  25
#define NO_DEFENSIVE      10
#define NO_ATTACKING      10
#define NO_SHOGUN         2
#define NO_CHANCELLOR     2
#define NO_CHAMPION       1

#define NO_HOLDINGS       17
#define NO_PLAIN          3
#define NO_MINE           3
#define NO_GOLD_MINE      3
#define NO_CRYSTAL_MINE   3
#define NO_FARMS          3
#define NO_SOLO           2

#define NO_FOLLOWERS      28
#define NO_FOOTSOLDIER    6
#define NO_ARCHER         6
#define NO_SIEGER         4
#define NO_CAVALRY        5
#define NO_NAVAL          5
#define NO_BUSHIDO        2

#define NO_ITEMS          12
#define NO_KATANA         4
#define NO_SPEAR          3
#define NO_BOW            2
#define NO_NINJATO        2
#define NO_WAKIZASHI      1
using namespace std;


//Personalities:
	enum{ATTACKER, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION};
//Holdings:
	enum{PLAIN, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD};
//Followers:
	enum{FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO};
//Items:
	enum{KATANA, SPEAR, BOW, NINJATO, WAKIZASHI};

	enum{PERSONALITY = 1,HOLDING,FOLLOWER,ITEM};

class GreenCard;
class BlackCard;

class DeckBuilder
{
	private:
		list<GreenCard*>* green;
		list<BlackCard*>* black;
	public:
		DeckBuilder();
		~DeckBuilder();
		void Create_decks();
		list<BlackCard *> *get_black();
		list<GreenCard *> *get_green();
		list<GreenCard *>* createFateDeck();
	 	list<BlackCard *>* createDynastyDeck();

		GreenCard& getFateCard();
		BlackCard& getDynastyCard();

		void deckShuffler(list<BlackCard *> *black);
		void deckShuffler(list<GreenCard *> *green);
		void deckShuffler();
};

//#endif
