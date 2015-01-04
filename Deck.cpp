#include "Deck.h"
#include <unistd.h>

using namespace std;

Deck::Deck(){
	PlayingCard deck[52];
	int incrementer = 0;
	Suit temp = H;
	int tempval = 0;
	for(tempval = 2; tempval < 15; tempval++){
		deck[incrementer] = PlayingCard(temp, tempval);
		incrementer++;
	}
	temp = S;
	for(tempval = 2; tempval < 15; tempval++){
		deck[incrementer] = PlayingCard(temp, tempval);
		incrementer++;
	}
	temp = C;
	for(tempval = 2; tempval < 15; tempval++){
		deck[incrementer] = PlayingCard(temp, tempval);
		incrementer++;
	}
	temp = D;
	for(tempval = 2; tempval < 15; tempval++){
		deck[incrementer] = PlayingCard(temp, tempval);
		incrementer++;
	}
	myDeck = vector<PlayingCard>(deck, deck + (sizeof(deck)/sizeof(deck[0])));
}

void Deck::shuffle(){
	random_shuffle(myDeck.begin(), myDeck.end());
	/*for(vector<PlayingCard>::iterator it = myDeck.begin(); it != myDeck.end(); ++it){
		cout << *it << endl;
	}
	cout << "================================================" << endl;*/
}

void Deck::halves(deque<PlayingCard>& d1, deque<PlayingCard>& d2){
	PlayingCard deck1[26];
	PlayingCard deck2[26];
	int half = myDeck.size()/2;
	int j=0;
	for(int i=0; i<half; i++){
		deck1[i] = myDeck[i];
	}
	for(int i=half; i<myDeck.size(); i++){
		deck2[j] = myDeck[i];
		j++;
	}
	d1 = deque<PlayingCard>(deck1, deck1 + sizeof(deck1)/sizeof(deck1[0]));
	d2 = deque<PlayingCard>(deck2, deck2 + sizeof(deck2)/sizeof(deck2[0]));
}
