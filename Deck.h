#include "PlayingCard.h"
#include <algorithm>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <deque>

using namespace std;

class Deck{
	public:
		Deck();
		void shuffle();
		void halves(deque<PlayingCard>& d1, deque<PlayingCard>& d2);

	private:
		vector<PlayingCard> myDeck;
};