#include <iostream>
#include <algorithm>
#include "GameBoard.hpp"
#include "TypeConverter.hpp"
using namespace std;


struct more_than_key
{
    inline bool operator() (const Player* p1, const Player* p2)
    {
        return (p1->Get_honour() >= p2->Get_honour());
    }
};



void GameBoard::initializeGameBoard()  //This method prepares the GameBoard
{
  int number;
  string name;
  cout << "How many players are going to play?" << endl;
  cin >> number;
  cin.ignore(256, '\n');
                                                        //Create the players
  for (int i=0; i<number; i++) {
    cout << "Type the name of player number " << i + 1 << endl;
    getline(cin,name);
    player.push_back(new Player{name});
  }
  sort(player.begin(), player.end(), more_than_key());
  diffCards=4;
}

void GameBoard::printGameStatistics()         //This method prints all the important statistcis for the game
{
  cout << endl << endl << "//-------------------------------------------------------------------------//" << endl
<< "//------------------------GameStatistics--------------------------------------//" << endl
<< "//-----------------------------------------------------------------------//" << endl << endl;
  for (int i=0; i<player.size(); i++) {
    cout << "Player " <<  i+1 << ": " << (player[i]->Get_name()) << endl;
                                                                                //Print how many provinces have left
    cout << player[i]->Get_numberOfProvinces() << " provinces left " << endl;

    cout << "Money: " << player[i]->Get_money() << endl;          //Print the money of each player
    cout << "Honour: " << player[i]->Get_honour() << endl << endl;  //Print the honour of each player
  }
}

void GameBoard::gameplay()      //This method allow us to play the game
{
  int i,cnt=0;
  for (i=0; i<player.size(); i++) {     //for each player
    player[i]->set_Hand();            //Draw card for the hand
    player[i]->hide_provinces();      //Hide the provinces
    player[i]->Untap_Everything();    //Untap all the cards
  }
  while (!checkWinningCondition()) {    //While there is no winner
    startingPhase();
    if (cnt >= 1) {                   //equipPhase and battlePhase only happen after the first round because in the first round the players have no army
      equipPhase();
      battlePhase();
    }
    economyPhase();
    finalPhase();
    for (i=0; i<player.size(); i++) player[i]->take_harvestValue();       //At the end of every round the players take the money from their holdings
    cnt++;
  }
}

void GameBoard::startingPhase()   //The first phase of the game
{
  cout << endl << endl << "//-------------------------------------------------------------------------//" << endl
<< "//------------------------startingPhase-----------------------------------//" << endl <<
"//-----------------------------------------------------------------------//" << endl << endl;
  for (int i=0; i<player.size(); i++) { //For each player
    player[i]->Untap_Everything();    //Untap all cards
    player[i]->drawFateCard();        //Draw a fate card
    player[i]->revealProvinces();     //Reveal all provinces
    player[i]->printHand();           //Print his current hand
    player[i]->printProvinces();      //Print the provinces
  }
}

void GameBoard::equipPhase()      //The second phase of the game
{
  cout << endl << endl << "//-------------------------------------------------------------------------//\n"
<< "//------------------------equipPhase--------------------------------------//\n"
<< "//-----------------------------------------------------------------------//\n" << endl;
  int personalities,money,number,number1,bonus;
  string card,answer,answer1;
  GreenCard *greencard;
  Personality *blackcard;
  Holding *holding;
  TypeConverter t;
  Follower *f;
  Item* it;
  for (int i=0; i<player.size(); i++) {     //For each player
    money=player[i]->Get_money();
    if (player[i]->get_army()!=0) {     //A player can equip his army only if he has army (Duuuuh Vol1)
        player[i]->printHand(); player[i]->printArmy(); player[i]->printHoldings();   //Print the hand, the army and the holdings
        cout << player[i]->Get_name() << " do you want to equip your army? - Type yes or no" << endl;
        getline(cin,answer);
        while (answer=="yes") {
          bonus=0;
          player[i]->printHand();
          cout << "You have " << player[i]->Get_money() << "$ Choose a card from your hand to equip one of your personalities-Type the number" << endl;
          cin >> number1;
                                                                        //Select which card of your hand you will use as equipment
          cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
          greencard=player[i]->get_hand_i(number1);
          if (money < greencard->get_cost()) {        //If you do not have enough money
              //cout << money << " and " << greencard->get_cost() << endl;
             cout << "You don't have enough money. You have to tap some holdings to take the harvestValue" << endl;
             player[i]->Tap_cards();    //Tap some holdings to take the harvestValue
             if (player[i]->Get_money() < greencard->get_cost()) {
               cout << "Even after the tapping you do not have enough money to buy the chosen card-Do you want to choose another?" << endl;
               getline(cin,answer);
               continue;
             }
          }
          player[i]->Pay(greencard->get_cost());    //Pay
          money=player[i]->Get_money();
          cout << "You chose "; greencard->print(); cout << endl;
          cout << "You have " << player[i]->Get_money() << "$ Do you want to buy the bonus as well? - Type yes or no" << endl;    //Check if the player wants the bonus
          getline(cin,answer1);
          if (answer1=="yes") {
            if (money >= greencard->get_Effect_cost()){     //If you have the money
              bonus=1;
              money-=greencard->get_Effect_cost();
              player[i]->Pay(greencard->get_Effect_cost());   //Use the bonus and pay for it
              greencard->Use_Bonus();
            }
            else {    //else
              cout << "You don't have enough money. You have to tap some holdings to take the harvestValue" << endl;
              player[i]->Tap_cards();   //Tap some cards to take the harvestValue
            }
          }
          while(1) {
              cout << "Choose a card from your army to equip-Type the right number" << endl;
              player[i]->printArmy();
              cin >> number;                                                           //Choose a card from your army to equip
              blackcard=player[i]->get_army_i(number);
              cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
              if (greencard->get_minimumHonour() <= blackcard->get_honour()) {        //If the chosen card from army is honoured enough to be equipped with the chosen card from the hand
                cout << "You chose "; blackcard->print();
                if (blackcard->get_max() < 3)  {      //Every card from army must be equiopped with 3 greencards at most
                  blackcard->Equip(*greencard);
                  player[i]->throw_handCard(number1); //Throw the card that you use as equippment from your hand;
                  cout << "You equipped the card and now it is: "; blackcard->print();
                  t.getCorrectType(greencard,&f,&it);       //Check the type of the chosen card from hand to insert it in the appropriate vector (Item or Follower)
                  if (f!=NULL)  blackcard->set_FollowerList(f);
                  else blackcard->set_ItemList(it);
                  break;
                }
                else {
                    cout << "Equipment Failed-The chosen personality cannot be equipped any more. Please choose other personality" << endl;
                    cout << "Do you want to?" << endl;
                                                        //The chosen personality has already equipped 3 times - Do you wnat to choose another card?
                    if (bonus==1) player[i]->Pay(  -( greencard->get_cost() + greencard->get_Effect_cost() )   );   //This basically returns the money because the purchase did not happen
                    else player[i]->Pay(-greencard->get_cost());
                    money += greencard->get_cost() + greencard->get_Effect_cost();
                    getline(cin,answer1);
                    if (answer1=="yes") continue;
                    else break;
                }
              }
              else {
                if (bonus==1) player[i]->Pay(  -( greencard->get_cost() + greencard->get_Effect_cost() )   );   //This basically returns the money because the purchase did not happen
                else player[i]->Pay(-greencard->get_cost());
                money += greencard->get_cost() + greencard->get_Effect_cost();
                cout << "Equipment Failed-Not enough honour. Please choose other card" << endl;
                cout << "Do you want to?" << endl;
                getline(cin,answer1);                     //The chosen personality has not enough honour - Do you wnat to choose another card?
                if (answer1=="yes") break;
                else break;
              }

            }
            cout << "Do you want to equip more?" << endl;
            getline(cin,answer);
        }

    }
    else cout << player[i]->Get_name() << " You cannot equip you army since you don't have any" << endl;

  }
}

void GameBoard::battlePhase()   //The third phase of the game
{
  cout << endl << endl << "//-------------------------------------------------------------------------//" << endl
  << "//------------------------battlePhase--------------------------------------//" << endl
  << "//-----------------------------------------------------------------------//" << endl << endl;
  int number,i,j,att,def,attack=0,defense=0,defense_of_province=0,diff,f=0;
  string answer;
  Personality *ArmyCard, *p;
  TypeConverter t;
  Holding* h;
  BlackCard *province;
  string card;
  for (i=0; i<player.size(); i++) {
    vector<Personality *> defenders,attackers;
      if (player[i]->get_army()!=0) {   //If a player hos no army he cannot attack (Duuuuh Vol2)
      att=i;        //att is the attacker player
      cout << player[i]->Get_name() << " Choose a player to attack-Type the number" << endl;
      for (int k=0; k<player.size(); k++) {
          if (k!=i) cout << k << ": " << player[k]->Get_name() << endl;
      }
      cin >> def;   //def is the defenfer player
          while (1) {
          //Choose attacker
          cout << player[att]->Get_name() << " Choose a personality from your army to attack-Type the right number" << endl;
          //Let's assume that you will not choose the same player more than once
          player[i]->printArmy();
          cin >> number;
          ArmyCard=player[att]->get_army_i(number);
          cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
          if (!ArmyCard->IsTapped()) {    //Only untapped cards can be used
            ArmyCard->print();
            attack+=ArmyCard->get_attack();   //Total attack
            attackers.push_back(ArmyCard);    //attackers are all t he personalities that have been chosen for attack
            cout << player[att]->Get_name() << " Do you need another attacker? - Type yes or no" << endl;
            getline(cin,answer);
            if (answer!="yes") {
              //cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
              break;
            }
          }
          else cout << player[att]->Get_name() << " The card you chose is tapped. Choose another" << endl;
        }
        //Choose the province that you want to attack
        cout << player[att]->Get_name() << " Which province from your opponent do you want to attack to? - Type the right number" << endl;
        player[def]->printProvinces();
        cin >> number;
        province=player[def]->get_province_i(number);
        cin.ignore(256, '\n');
        cout << player[att]->Get_name() << " You will attack to:  ";
        province->print();
        t.getCorrectType(province,&p,&h);
        if (p!=NULL) defense_of_province = p->get_defense();     //If the province is personality get its defene
        if (player[def]->get_army()!=0) {     //A player can choose personalities to defend only if he has army (Duuuuh Vol3)
          while (1) {
            cout << player[def]->Get_name() << " Choose a personality from your army to use for defense - Type the right number" << endl;
            player[def]->printArmy();
            cin >> number;                                //Choose defenders
            ArmyCard=player[def]->get_army_i(number);
            cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
            if (!ArmyCard->IsTapped()) {
              if (j==0) cout << player[def]->Get_name() << " You chose:" << endl;
              ArmyCard->print();
              defense+=ArmyCard->get_defense();   //defense is the total defense of all the defenders
              defenders.push_back(ArmyCard);
              cout << player[def]->Get_name() << " Do you need another defender? - Type yes or no" << endl;
              getline(cin,answer);
              if (answer!="yes") break;
            }
            else cout << player[def]->Get_name() << " The card you chose is tapped. Choose another" << endl; //Only untapped card can be used
          }
        }
        else cout << player[def]->Get_name() << " sorry you do not have any army to defend" << endl;
        defense+=player[def]->get_initial_defense();    //In the total defense we should add the denfense of the Stronghold
        defense_of_province+=player[def]->get_initial_defense();    //In the province's defense we should add the denfense of the Stronghold


        //Let's examine the different subcases to determine the winner of the battles or the loses of each player
        if (attack-defense > defense_of_province) {
            cout << player[att]->Get_name() << " You won the battle!" << endl;
            player[def]->destroy_province(province);     //In this case the we have an absolute winner-the player who defends loses his province and all his defenders
            for (int i=0; i<defenders.size(); i++) player[def]->kill_personality(i);//defenders[def]->die();
        }
        else {    //Another case
          if (attack > defense) {
            f=1;              //f equals to 1 when the player who attacked survives (but not as an winner)
            diff=attack-defense;
            for (int i=0; i<defenders.size(); i++) {
              player[def]->kill_personality(i);   //The player who defends looses all his defenders
            }
            while (diff>=0 && attackers.size()!=0) {    //Loop stops if the player who attacks sucrifices all needed attackers or if he runs out of them
              for (int i=0; i<attackers.size(); i++) {cout << i << ":   "; attackers[i]->print();}
              cout << player[att]->Get_name() << " Choose an attacker to be killed - Type the right number" << endl;
              cin >> number;
              diff-=attackers[number]->get_attack();
              player[att]->kill_personality(number);
              attackers.erase(attackers.begin()+number);
              cin.ignore(256, '\n');
            }
            for (int i=0; i<attackers.size(); i++) {
              if (!attackers[att]->IsDead()) attackers[i]->Decrease_Honour();   //Every alive attacker looses a point of honour
              if (attackers[att]->get_honour()==0) {
                attackers[i]->performSeppuku(); //If an attacker's honour becomes 0 the attacker commits suicide to save his family honour
                player[att]->kill_personality(i);
              }
            }
          }
          else if (attack==defense) {   //Another case
              cout << "We have a draw in this battle. All attackers and defenders are going to die" << endl;
              for (int i=0; i<defenders.size(); i++) {
                player[def]->kill_personality(i);
              }
              //The player who defeded looses all his defenders and the one who attacked looses all his attackers
              for (int i=0; i<attackers.size(); i++) {
                player[att]->kill_personality(i);
              }

            }
          else {
              for (int i=0; i<attackers.size(); i++) player[att]->kill_personality(i);
              while (diff>=0 && defenders.size()!=0) { //Loop stops if the player who defends sucrifices all needed defenders or if he runs out of them
                for (int i=0; i<defenders.size(); i++) {cout << i << ":   "; defenders[i]->print();}
                cout << player[def]->Get_name() << " Choose a defender to be killed - Type the right number" << endl;
                cin >> number;
                diff-=defenders[number]->get_attack();
                player[def]->kill_personality(number);
                defenders.erase(defenders.begin()+number);
                cin.ignore(256, '\n');
                for (int i=0; i<defenders.size(); i++) {
                  if (!defenders[att]->IsDead()) defenders[i]->Decrease_Honour();   //Every alive defender looses a point of honour
                  if (defenders[att]->get_honour()==0) {
                    defenders[i]->performSeppuku(); //If an defender's honour becomes 0 the attacker commits suicide to save his family honour
                    player[def]->kill_personality(i);
                  }
                }
              }
            }
            if (f==1) {       //If the player who attacked survived but he did not win the battle
                for (int i=0; i<attackers.size(); i++) {  //Each of his alive attackers
                  if (!attackers[att]->IsDead()){
                    attackers[att]->Tap();        //gets tapped
                    attackers[att]->Tap_Followers();    //his followers get tapped
                    attackers[att]->Decrease_Durability_Items(); //Each of his items loose one point of durability
                  }
                }
            }
        }

    }
  }
}

void GameBoard::economyPhase()    //The fourth phase of the game
{
  cout << endl << endl << "//-------------------------------------------------------------------------//" << endl
<< "//------------------------economyPhase--------------------------------------//" << endl
<< "//-----------------------------------------------------------------------//" << endl << endl;
    int provinces,number;
    string card,answer1,answer;
    BlackCard* province;
    Holding *holding;
    for (int i=0; i<player.size(); i++) {   //For all players
      player[i]->revealProvinces();   //Reveal all of their provinces
      player[i]->printProvinces();    //Print them
      cout << player[i]->Get_name() << " you have " << player[i]->Get_money() << "$. Do you want to buy a province?" << endl;
      getline(cin,answer);          //See if the player wants to buy a province
      while (answer=="yes") {
        player[i]->printProvinces();
        cout << player[i]->Get_name() << " Which province do you want to buy?-Choose the number" << endl;
        cin >> number;
        cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );     //Choose the province that you want to buy
        province=player[i]->get_province_i(number);
        cout << player[i]->Get_name() << " You chose: "; province->print();
        if (player[i]->Get_money() < province->get_cost()) {      //If you do not have enough money
          cout << player[i]->Get_name() << " You don't have enough money. You have to tap some holdings to take the harvestValue" << endl;
          player[i]->Tap_cards();     //You have to tap some of your holdings to take the harvestValue
        }
      if (player[i]->Get_money() >= province->get_cost()){   //If you can afford
          player[i]->Buy_a_province(province);    //Buy it
          TypeConverter t;
          Personality *p;
          Holding* h;
          t.getCorrectType(province,&p,&h);
          if (h!=NULL) player[i]->Check_for_connection(h);      //And if it is a holding check for upperHoldings or subHoldings
      }
      else cout << player[i]->Get_name() << ",Purchase impossible. Not enough money" << endl;
      cout << player[i]->Get_name() << " you have " << player[i]->Get_money() << "$. Do you want to buy another province?" << endl;
      getline(cin,answer);    //Check if the player wants to buy another province
    }
  }
}

void GameBoard::finalPhase()   //The fifth an final phase of the game
{
  cout << endl << endl << "//-------------------------------------------------------------------------//\n"
<< "//------------------------finalPhase--------------------------------------//\n"
<< "//-----------------------------------------------------------------------//\n" << endl;
  for (int i=0; i<player.size(); i++) {   //For all players
    if (player[i]->get_handSize() >= HAND) {    //If the players have more cards in their hand than the limit
      player[i]->discardSurplusFateCards();   //They have to throw away some of them
    }
  }
  printGameStatistics();    //Print the statistics of the game
  for (int i=0; i<player.size(); i++) {   //For all players
      player[i]->printHand();   //Print their hand
      player[i]->printArena();    //Print thei arena
      player[i]->printProvinces();    //Print their provinces
      player[i]->printHoldings();     //Print their holdings
    }
}

bool GameBoard::checkWinningCondition()
{
    for (int i=0; i<player.size(); i++) {
        if (player[i]->Get_numberOfProvinces()==/*0*/3) {
          player.erase(player.begin()+i);
        }
    }
    if (player.size()==1) {
      cout << player[0]->Get_name() << " congratulations you are the big winner!!!!" << endl;
      return true;
    }
    else if (player.size()==0){
       cout << "It's a draw" << endl;
       return true;
    }
    return false;
}
