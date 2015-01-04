#include "Player.h"

using namespace std;

Player::Player(deque<PlayingCard> dq, string name){
	warHand = dq;
	playerName = name;
	battleCount = 0;
	deficit = 0;
	numRounds = 0;
	largestDeficit = 0;
}

Player::Player(){
	playerName = "death";
}