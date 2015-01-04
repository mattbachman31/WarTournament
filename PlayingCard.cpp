#include "PlayingCard.h"

using namespace std;

PlayingCard::PlayingCard(){

}

PlayingCard::PlayingCard(Suit suit, int cval){
	val = cval;
	thisSuit = suit;
}

ostream& operator<<(ostream& out, const PlayingCard& card){
	if((card.val <= 10) && (card.val >= 2)) {out << card.val;}
	else if(card.val == 11){out << 'J';}
	else if(card.val == 12){out << 'Q';}
	else if(card.val == 13){out << 'K';}
	else{out << 'A';}

	if(card.thisSuit == H){out << 'H';}
	else if(card.thisSuit == C){out << 'C';}
	else if(card.thisSuit == S){out << 'S';}
	else{out << 'D';}
	return out;
}

bool PlayingCard::operator<(const PlayingCard& card){
	bool ret = false;
	if(val < card.val) {ret = true;}
	return ret;
}

bool PlayingCard::operator>(const PlayingCard& card){
	bool ret = false;
	if(val > card.val) {ret = true;}
	return ret;
}

/*bool PlayingCard::isLess(const PlayingCard& card2){
	bool ret = false;
	if(val < card2.val){ret = true;}
	return ret;
}*/