#ifndef PLAYING_CARD
#define PLAYING_CARD

#include <iostream>
#include <fstream>


using namespace std;

enum Suit{H, C, S, D}; //Hearts, Clubs, Spades, Diamonds

class PlayingCard{
	public:
		PlayingCard(Suit suit, int cval);
		PlayingCard();
		friend ostream& operator<<(ostream& out, const PlayingCard& card);
		bool operator<(const PlayingCard& card);
		bool operator>(const PlayingCard& card);
		//bool isLess(const PlayingCard& card2);

	private:
		Suit thisSuit;
		int val;
};

#endif