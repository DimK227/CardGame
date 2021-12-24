#include "Player.hpp"
#include "TypeConverter.hpp"
#include "DeckBuilder.hpp"
#include <iostream>
#include <vector>
using namespace std;


Player::Player(string new_name)   //The constructor of class Player
{
  name=new_name;
  numberOfProvinces=4/*4*/;   //The amount of provinces that the player will possess
  decks = new DeckBuilder();
  decks->Create_decks();      //Create his decks
  decks->deckShuffler();      //Shuffle them
  for (int i=0; i<numberOfProvinces; i++) province.push_back(&(decks->getDynastyCard()));   //The player takes his provinces
  stronghold=new Stronghold{10,5, 5};      //Create th stronghold
  money=stronghold->Get_initialMoney();   //His starting money is the money of the Stronghold
  honour=stronghold->Get_startingHonour();  //His starting honour is the money of the Stronghold
}

int Player::Get_numberOfProvinces()   //This method returns the current number of player's provinces
{
  return numberOfProvinces;
}

int Player::Get_money()  //This method returns the current money of the player
{
  return money;
}

int Player::Get_honour() const //This method returns the honour of the player
{
  return honour;
}

string  Player::Get_name()//This method returns the name of the player
{
  return name;
}

int Player:: get_army()  //This method returns the current size of the player's army
{
  int i,s=0;
  for (i=0; i<army.size(); i++) {
    if (!(army[i]->IsDead())) s++;
  }
  return s;
}

int Player::get_initial_defense()  //This method returns the initial defense of the player
{
  return stronghold->Get_initialDefense();
}

void Player::harvest(string name) //This method gives the harvestValue of the holding named "name" to the player
{
  for (int i=0; i<holdings.size(); i++) {   //Search all holdings
      if (holdings[i]->get_name() == name) {    //When you find the right one
        money+=holdings[i]->Get_harvestValue(); //Get the harvestValue
        holdings[i]->Tap();           //Tap it
      }
  }
}

void Player::take_harvestValue()    //This method gives to the player the harvest value of all of his holdings
{
  for (int i=0; i<holdings.size(); i++) money+=holdings[i]->Get_harvestValue();
}

void Player::set_Hand()     //THis method creates the hand of the player
{
  for (int i=0; i<HAND; i++) hand.push_back(&(decks->getFateCard()));
}

void Player::hide_provinces()   //This method hides all player's provinces
{
  for (int i=0; i<province.size(); i++) province[i]->hide();
}

void Player::revealProvinces()
{
  for (int i=0; i<province.size(); i++) province[i]->reveal();
}


void Player::Untap_Everything()
{
  int i;
  for (i=0; i<province.size(); i++) province[i]->Untap();
  for (i=0; i<army.size(); i++) army[i]->Untap();
  for (i=0; i<holdings.size(); i++) holdings[i]->Untap();

}

void Player::drawFateCard()
{
  hand.push_back(&(decks->getFateCard()));
}

void Player::Pay(int new_money)   //Via this function a player pays new_money$
{
  money=money-new_money;
}


void Player::kill_personality(int number)
{
  army.erase(army.begin()+number);
}

void Player::throw_handCard(int number)
{
  hand.erase(hand.begin()+number);
}

void Player::printHand()       //This method prints all the cards that the player holds in his hand
{
  cout <<"\n\nHAND of " << name << ":"<< endl;
  for (int i=0; i<hand.size(); i++){
    cout << i << ":     "; hand[i]->print();
  }
  cout << endl;
}

void Player::printProvinces()      //This method prints all the holdings of the player
{
    if (province.size()==0) cout << "No provinces" << endl;
    else cout << "PROVINCES of " << name << ":"<< endl;
    for (int i=0; i<province.size(); i++) {cout << i << ":     "; province[i]->print();}
}

void Player::printArmy()    //This method prints the army of the player
{
  if (army.size()==0) cout << "No army" << endl;
  else cout << "army of " << name << ":"<< endl;
  for (int i=0; i<army.size(); i++) {
    if (army[i]->IsRevealed()){
        cout << i << ":     "; army[i]->print();
    }
  }
  cout << endl;
}

void Player::printArena()   //This method prints the arena of a player
{
  Item* itemcard;
  this->printArmy();    //Print the army

  //And now print the items and the followers of each member of the army

  for (int i=0; i<army.size(); i++) {
    cout << "Items of " << army[i]->get_name() << " are:" << endl;
    for (int j=0; j < army[i]->get_ItemList_size(); j++) {
      cout << j << endl;
      itemcard=army[i]->get_ItemList_j(j);
      itemcard->print();
    }
    cout << "Followers of " << army[i]->get_name() << " are:" << endl;
    for (int j=0; j < army[i]->get_FollowerList_size(); j++) army[i]->get_FollowerList_j(j)->print();
  }

}

void Player::printHoldings()    //This method prints all the holdings of a player
{
  if (holdings.size()==0) cout << "No holdings";
  else cout << "HOLDINGS of " << name << ":" << endl;
  for (int i=0; i<holdings.size(); i++) {
        cout << i << ":     "; holdings[i]->print();
  }
   cout << endl;
}

GreenCard* Player::get_hand_i(int number)    //This method returns a specific card from the hand
{
  return hand[number];
}

int Player::get_handSize()    //This method return the amount of cards that the player holds in his hand
{
  return hand.size();
}

BlackCard* Player::get_province_i(int number)  //This method returns a specific province
{
  return province[number];
}

Personality* Player::get_army_i(int number)  //This method returns a specific personality card
{
  return army[number];
}


void Player::Buy_a_province(BlackCard* new_province)      //Via this method the player buys the province named "new_province"
{
  TypeConverter t;
  Personality *p;
  Holding* h;
  t.getCorrectType(new_province,&p,&h);   //Find if it is personality or holding
  if (p!=NULL) army.push_back(p);
                                      //Insert it to the right vector
  else holdings.push_back(h);
  destroy_province(new_province);     //Now there is no such province
  numberOfProvinces++;            //The player has one more province
  province.push_back(&(decks->getDynastyCard()));       //Replace it
  Pay(new_province->get_cost());
  cout << "Purchase completed" << endl;
}

bool Player::All_cards_tapped()  //This method checks if all the holdings of a player are tapped
{
  for (int i=0; i<holdings.size(); i++) {
    if (!holdings[i]->IsTapped()) return false;     //If you find at least on that it is not return false
  }
  return true;
}

void Player::destroy_province(BlackCard* new_province)    //Via this method a province gets destoryed
{
  numberOfProvinces--;        //Now player has one less province (Too bad.....)
  for (int i=0; i < province.size(); i++) {
    if (province[i]->get_name() == new_province->get_name()){     //Find the right province
      province.erase(province.begin() + i);           //and delete it
      break;
    }
  }
}

void Player::Tap_cards()      //Via this method the player tap cards(holdings) so as to take their harvest value
{
  string card,answer1;
  Holding* holding;
  int number;
  this->printHoldings();      //Print all holdings
  if (this->All_cards_tapped()){      //If are all tapped there is no solution
      cout << "Sorry since you have all your cards tapped and you do not have enough money you cant perform this purchase" << endl;
      return;
  }
  cout << "Choose a holding to tap-Type the number" << endl;
  cin >> number;                                      //Pick the holding that you want to tap
  cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
  holding=holdings[number];
  if (!holding->IsTapped()) this->harvest(holding->get_name()); //If it is not tapped
  else cout << "This card is already tapped. Choose another" << endl;
  cout << "Do you want to tap another holding" << endl;     //Do you want to tap more?
  getline(cin,answer1);
  while (answer1=="yes") {
    this->printHoldings(); cout << "Choose the number" << endl;
    cin >> number;
    holding=holdings[number];       //Pick the holding
    cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
    cout << "You chose "; holding->print(); cout << endl;
    if (!holding->IsTapped()) this->harvest(holding->get_name());
    else {
      cout << "This card is already tapped. Choose another" << endl;
      continue;
    }
    cout << "Do you want to tap another holding" << endl;
    getline(cin,answer1);
  }
}

void Player::Check_for_connection(Holding* new_holding)
{
  int kind1 = new_holding->get_cost(),kind2;  //The costs show us the kind of a mine. Explenation in DeckBuilder.hpp file and in README
  int i,k=0;
  vector<Holding*> m,gm,cm;
  if (kind1 >= mine) {    //If the new_holding is some kind of mine. If it son there is no point in looking for possible connections with other mines
    for (i=0; i<holdings.size(); i++) {
        kind2 = holdings[i]->get_cost();
        if (kind2==mine) m.push_back(holdings[i]);
                                                        //Find and save all mines, all glod mines and all crystal mines.
        else if (kind2==7) gm.push_back(holdings[i]);
        else cm.push_back(holdings[i]);
    }
    if (kind1==mine) {        //If the new_holding is mine
        new_holding->set_subHolding(NULL);      //It cannot have subHolding
        if (gm.size()==0) new_holding->set_upperHolding(NULL);  //If there is no gold mines then it cannot have upperholding either
        else if (gm.size()==1) {                    //If there is one gold mine
          if (gm[0]->IsSubFree()) {                 //If the gold mine has no subholding
            new_holding->set_upperHolding(gm[0]);
                                                    //Connect them
            gm[0]->set_subHolding(new_holding);
            new_holding->Increase_harvestValue(2);
                                                          //Increase the harvest values
            gm[0]->Increase_harvestValue(4);
            new_holding->print(); cout << "connected with:" << endl; gm[0]->print();
          }
        }
        else {                              //If there are more than one gold mine choose one randomnly and do the same process
          k=rand()%gm.size();
          if (gm[k]->IsSubFree()) {
            new_holding->set_upperHolding(gm[k]);
            gm[k]->set_subHolding(new_holding);
            new_holding->Increase_harvestValue(2);
            gm[0]->Increase_harvestValue(4);
            new_holding->print(); cout << "connected with:" << endl; gm[k]->print();
          }
        }
    }
    else if (kind1==gold_mine) {      //If the new_holding is a gold mine
        int s=0,u=0;        //s will be 1 when we have a subholding connection and 0 if we do not. u will be 1 when we have upperHolding connection and 0 if we don't
        if (m.size()==0) new_holding->set_subHolding(NULL);   //If there are no mines the gold mine can't have a subholding
        else if (m.size()==1){          //If there is only one
          if (m[0]->IsUpperFree()){       //If the mine has no upperHolding connect them
            new_holding->set_subHolding(m[0]);
            m[0]->set_upperHolding(new_holding);
            s++;
            new_holding->print(); cout << "connected with:" << endl; m[0]->print();
          }
        }
        else {            //If we have more than one mine choose randomly
          k=rand()%m.size();
          if (m[k]->IsUpperFree()){
            new_holding->set_subHolding(m[k]);
            m[k]->set_upperHolding(new_holding);
            s++;
            new_holding->print(); cout << "connected with:" << endl; m[k]->print();
          }
        }

        if (cm.size()==0) new_holding->set_upperHolding(NULL);   //If there are no crystal mines the gold mine can't have a subholding
        else if (cm.size()==1){                         //If there is only one
          if (cm[0]->IsSubFree()) {           //If the crystal mine has not subHolding connect them
            new_holding->set_upperHolding(cm[0]);
            cm[0]->set_subHolding(new_holding);
            u++;
            new_holding->print(); cout << "connected with:" << endl; cm[0]->print();
          }
        }
        else {        //If there are more than one crystal mines choose one randomnly
          k=rand()%cm.size();
          if (cm[k]->IsSubFree()){
            new_holding->set_upperHolding(cm[k]);
            cm[k]->set_upperHolding(new_holding);
            u++;
            new_holding->print(); cout << "connected with:" << endl; gm[k]->print();
          }
        }
        //Now increase the harvestValue accordinf to the connections we had
        if (s==1 && u==0) {
          new_holding->Increase_harvestValue(4);
          m[k]->Increase_harvestValue(2);
        }
        else if (s==0 && u==1) {
          new_holding->Increase_harvestValue(5);
          cm[k]->Increase_harvestValue(2*cm[k]->Get_harvestValue());
        }
        else if (s==1 && u==1) {
          new_holding->Increase_harvestValue(2*new_holding->Get_harvestValue());
          cm[k]->Increase_harvestValue(2*cm[k]->Get_harvestValue());
          m[k]->Increase_harvestValue(2);
        }
    }
    else {    //else if the new_holding is crystal mine
      new_holding->set_upperHolding(NULL);  //It can't have upperholding
      if (gm.size()==0) new_holding->set_subHolding(NULL);      //If there are no gold mines it can't have subholding either
      else if (gm.size()==1) {        //If there is only one connect the two
        if (gm[0]->IsUpperFree()) {
          new_holding->set_subHolding(gm[0]);
          gm[0]->set_upperHolding(new_holding);
          new_holding->Increase_harvestValue(2*new_holding->Get_harvestValue());
          gm[0]->Increase_harvestValue(5);
          new_holding->print(); cout << "connected with:" << endl; gm[0]->print();
          if (!(gm[0]->IsSubFree())) new_holding->Increase_harvestValue(3*new_holding->Get_harvestValue());
        }
      }
      else {    //If there is more than one choose one randomly
        k=rand()%gm.size();
        if (gm[k]->IsUpperFree()){
          new_holding->set_subHolding(gm[k]);
          gm[k]->set_upperHolding(new_holding);
          new_holding->Increase_harvestValue(2*new_holding->Get_harvestValue());
          gm[0]->Increase_harvestValue(5);
          new_holding->print(); cout << "connected with:" << endl; gm[k]->print();
          if (!(gm[0]->IsSubFree())) new_holding->Increase_harvestValue(3*new_holding->Get_harvestValue());
        }
     }
   }
  }
}

void Player::discardSurplusFateCards()    //Via this method the player throws away some of his hand cards
{
  int number;
  printHand();
  while (hand.size()>HAND) {    //Loop stops when the player has the appropriate amount of cards in his hand
    cout << "Choose a card from your hand to throw away - Type the number" << endl;
    cin >> number;                                //Which card do you want to throw away?
    hand.erase(hand.begin()+number);
    cin.ignore(256, '\n');
  }
}
