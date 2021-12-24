project: main.o GameBoard.o Player.o DeckBuilder.o Follower.o Card.o Personality.o Item.o Holding.o Stronghold.o GreenCard.o BlackCard.o TypeConverter.o
	g++ -std=c++11  main.o GameBoard.o Player.o DeckBuilder.o Follower.o Card.o Personality.o Item.o Holding.o Stronghold.o GreenCard.o BlackCard.o TypeConverter.o -o project
main.o : main.cpp GameBoard.hpp
	g++ -std=c++11 -c main.cpp
GameBoard.o : GameBoard.cpp GameBoard.hpp TypeConverter.hpp
	g++ -std=c++11 -c GameBoard.cpp
Player.o : Player.cpp Player.hpp GameBoard.hpp TypeConverter.hpp
	g++ -std=c++11 -c Player.cpp
DeckBuilder.o : DeckBuilder.cpp DeckBuilder.hpp
	g++ -std=c++11 -c DeckBuilder.cpp
Card.o : Card.cpp Card.hpp
	g++ -std=c++11 -c Card.cpp
BlackCard.o : BlackCard.cpp BlackCard.hpp
	g++ -std=c++11 -c BlackCard.cpp
GreenCard.o : GreenCard.cpp GreenCard.hpp
	g++ -std=c++11 -c GreenCard.cpp
Follower.o : Follower.cpp Follower.hpp DeckBuilder.hpp
	g++ -std=c++11 -c Follower.cpp
Personality.o : Personality.cpp Personality.hpp DeckBuilder.hpp
	g++ -std=c++11 -c Personality.cpp
Item.o : Item.cpp Item.hpp GreenCard.hpp DeckBuilder.hpp
	g++ -std=c++11 -c Item.cpp
Holding.o : Holding.cpp Holding.hpp DeckBuilder.hpp
	g++ -std=c++11 -c Holding.cpp
Stronghold.o : Stronghold.cpp Stronghold.hpp DeckBuilder.hpp
	g++ -std=c++11 -c Stronghold.cpp
TypeConverter.o: TypeConverter.cpp TypeConverter.hpp DeckBuilder.hpp
	g++ -std=c++11 -c TypeConverter.cpp

clean :
	rm project main.o GameBoard.o Player.o DeckBuilder.o Follower.o Card.o Personality.o Item.o Holding.o Stronghold.o GreenCard.o BlackCard.o TypeConverter.o
