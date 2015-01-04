#include "Deck.h"
#include <string>

class Player{
	public:
		Player(deque<PlayingCard> dq, string name);
		Player();
		string playerName;
		deque<PlayingCard> warHand;
		int battleCount;
		int deficit;
		int numRounds;
		int largestDeficit;
};