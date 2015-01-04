#include "War.h"

using namespace std;

War::War(Player** array, int size){
	arr = array;
	arrSize = size;
}

bool War::Battle(ostream& out, Player** array){
	bool ret = true;
	if(preMatch){
		out << array[0]->playerName << " vs. " << array[1]->playerName << endl;
		preMatch = false;
	}
	PlayingCard p1;
	PlayingCard p2;
	if(battleCount == 10000){
		ret = false;
		out << "No winner today!" << endl;
		return ret;
	}
	if((array[0]->warHand.size() == 0) || (array[1]->warHand.size() == 0)){
		ret = false;
		if(firstWon){out << array[0]->playerName << " DEFEATED " << array[1]->playerName << " in " << battleCount << " Battles and " << warCount << " Wars." << endl;}
		else{out << array[1]->playerName << " DEFEATED " << array[0]->playerName << " in " << battleCount << " Battles and " << warCount << " Wars." << endl;}
	}
	else{
		battleCount++;
		PlayingCard p1 = array[0]->warHand[array[0]->warHand.size()-1];
		PlayingCard p2 = array[1]->warHand[array[1]->warHand.size()-1];
		array[1]->warHand.pop_back();
		array[0]->warHand.pop_back();
		if(p1 < p2){
			firstWon = false;
			array[1]->warHand.push_front(p1);
			array[1]->warHand.push_front(p2);
		}
		else if(p2 < p1){
			firstWon = true;
			array[0]->warHand.push_front(p1);
			array[0]->warHand.push_front(p2);
		}
		else{
			if((array[0]->warHand.size() == 0) || (array[1]->warHand.size() == 0)){
				ret = false;
				if(array[0]->warHand.size() == 0){
					array[1]->warHand.push_front(p1);
					array[1]->warHand.push_front(p2);
				}
				else{
					array[0]->warHand.push_front(p1);
					array[0]->warHand.push_front(p2);
				}
			}
			else{
				warCount++;
				out << '\t' << "Battle " << battleCount << ": "<< array[0]->playerName << " (" << p1 << ") tied " << array[1]->playerName << " (" << p2 << ")" << endl;
				inWar = true;
				wasInWar = true;
				bool oneLargeEnough = true;
				bool twoLargeEnough = true;
				int size1 = array[0]->warHand.size();
				int size2 = array[1]->warHand.size();
				if(size1 < 4) {oneLargeEnough = false;}
				if(size2 < 4) {twoLargeEnough = false;}
				if(oneLargeEnough && twoLargeEnough){
					PlayingCard oneTemp1 = array[0]->warHand[array[0]->warHand.size()-1];
					PlayingCard oneTemp2 = array[0]->warHand[array[0]->warHand.size()-2];
					PlayingCard oneTemp3 = array[0]->warHand[array[0]->warHand.size()-3];
					array[0]->warHand.pop_back();
					array[0]->warHand.pop_back();
					array[0]->warHand.pop_back();
					PlayingCard twoTemp1 = array[1]->warHand[array[1]->warHand.size()-1];
					PlayingCard twoTemp2 = array[1]->warHand[array[1]->warHand.size()-2];
					PlayingCard twoTemp3 = array[1]->warHand[array[1]->warHand.size()-3];
					array[1]->warHand.pop_back();
					array[1]->warHand.pop_back();
					array[1]->warHand.pop_back();
					bool recursive = War::Battle(out,array);
					if(firstWon){
						array[0]->warHand.push_front(oneTemp1);
						array[0]->warHand.push_front(oneTemp2);
						array[0]->warHand.push_front(oneTemp3);
						array[0]->warHand.push_front(twoTemp1);
						array[0]->warHand.push_front(twoTemp2);
						array[0]->warHand.push_front(twoTemp3);
						array[0]->warHand.push_front(p1);
						array[0]->warHand.push_front(p2);
					}
					else{
						array[1]->warHand.push_front(oneTemp1);
						array[1]->warHand.push_front(oneTemp2);
						array[1]->warHand.push_front(oneTemp3);
						array[1]->warHand.push_front(twoTemp1);
						array[1]->warHand.push_front(twoTemp2);
						array[1]->warHand.push_front(twoTemp3);
						array[1]->warHand.push_front(p1);
						array[1]->warHand.push_front(p2);
					}
				}
				else{
					int oneCount = 0;
					int twoCount = 0;
					PlayingCard arr[8];
					for(int i=0; i<array[0]->warHand.size()-1; i++){
						arr[i] = array[0]->warHand[array[0]->warHand.size()-1];
						array[0]->warHand.pop_back();
						oneCount++;
						if(oneCount == 4) {break;}
					}
					for(int j=0; j<array[1]->warHand.size()-1; j++){
						arr[j+oneCount] = array[1]->warHand[array[1]->warHand.size()-1];
						array[1]->warHand.pop_back();
						twoCount++;
						if(twoCount == 4) {break;}
					}
					bool recursive = War::Battle(out,array);
					if(firstWon){
						array[0]->warHand.push_front(p1);
						array[0]->warHand.push_front(p2);
						for(int k=0; k<(oneCount + twoCount); k++){
							array[0]->warHand.push_front(arr[k]);
						}
					}
					else{
						array[1]->warHand.push_front(p1);
						array[1]->warHand.push_front(p2);
						for(int m=0; m<(oneCount + twoCount); m++){
							array[1]->warHand.push_front(arr[m]);
						}
					}
				}
				inWar = false;
			}
		}
		if(!inWar){
			if(!wasInWar){
				if(firstWon){out << '\t' << "Battle " << battleCount << ": "<< array[0]->playerName << " (" << p1 << ") defeated " << array[1]->playerName << " (" << p2 << "): " << array[0]->playerName << " " << array[0]->warHand.size() << ", " << array[1]->playerName << " " << array[1]->warHand.size() << endl;}
				else{out << '\t' << "Battle " << battleCount << ": " << array[1]->playerName << " (" << p2 << ") defeated " << array[0]->playerName << " (" << p1 << "): " << array[0]->playerName << " " << array[0]->warHand.size() << ", " << array[1]->playerName << " " << array[1]->warHand.size() << endl;}
			}
			else{
				out << array[0]->playerName << " " << array[0]->warHand.size() << ", " << array[1]->playerName << " " << array[1]->warHand.size() << endl;
				wasInWar = false;
			}
		}
		else{
			battleCount--;
			if(firstWon){out << '\t' << "War " << warCount << ": "<< array[0]->playerName << " (" << p1 << ") defeated " << array[1]->playerName << " (" << p2 << "): ";} // << array[0]->playerName << " " << array[0]->warHand.size() << ", " << array[1]->playerName << " " << array[1]->warHand.size() << endl;}
			else{out << '\t' << "War " << warCount << ": " << array[1]->playerName << " (" << p2 << ") defeated " << array[0]->playerName << " (" << p1 << "): ";} // << array[0]->playerName << " " << array[0]->warHand.size() << ", " << array[1]->playerName << " " << array[1]->warHand.size() << endl;}
		}
	}
	return ret;
}

int War::getBattleCount(){
	return battleCount;
}

int War::getWarCount(){
	return warCount;
}

Player* War::Flip_Tournament(ostream& out, int battleArr[], int subSize, Player* array[]){
	if(subSize == 0){subSize = arrSize;}
	if(array == 0){array = arr;}
	//out << endl << "Entering a war tournament! Players: ";
	/*for(int i=0; i<subSize; i++){
		out << array[i]->playerName << "  ";
		array[i]->battleCount = 0;
		array[i]->deficit = 0;
		battleCount = 0;
		warCount = 0;
	}
	out << endl;*/
	if(subSize == 2){
		bool ret = true;
		War::resetDecks(array);
		while(ret){
			if(preMatch){
				out << "===" << endl;
				out << array[0]->playerName << " vs. " << array[1]->playerName << endl;
				array[0]->numRounds++;
				array[1]->numRounds++;
				battleCount = 0;
				preMatch = false;
			}
			PlayingCard p1;
			PlayingCard p2;
			if(battleCount == 10000){
				ret = false;
				out << "Too long, random winner" << endl;
				preMatch = true;
				battleArr[matchCount] = battleCount;
				battleArr[matchCount+1] = warCount;
				matchCount+=2;
				return array[0];
			}
			if((array[0]->warHand.size() == 0) || (array[1]->warHand.size() == 0)){
				ret = false;
				preMatch = true;
				battleArr[matchCount] = battleCount;
				battleArr[matchCount+1] = warCount;
				matchCount+=2;
				if(firstWon){
					out << array[0]->playerName << " (" << array[0]->numRounds << ") DEFEATED " << array[1]->playerName << " in " << battleCount << " Battles and " << warCount << " Wars." << endl;
					array[1]->largestDeficit = 0;
				}
				else{
					out << array[1]->playerName << " (" << array[1]->numRounds << ") DEFEATED " << array[0]->playerName << " in " << battleCount << " Battles and " << warCount << " Wars." << endl;
					array[0]->largestDeficit = 0;
				}
			}		
			else{
				battleCount++;
				PlayingCard p1 = array[0]->warHand[array[0]->warHand.size()-1];
				PlayingCard p2 = array[1]->warHand[array[1]->warHand.size()-1];
				array[1]->warHand.pop_back();
				array[0]->warHand.pop_back();
				//int p2size = 0;
				//int p1size = 0;
				if(p1 < p2){
					firstWon = false;
					array[1]->warHand.push_front(p1);
					array[1]->warHand.push_front(p2);
					int diff = ((array[1]->warHand.size())-(array[0]->warHand.size()));
					if(diff > array[0]->largestDeficit) {array[0]->largestDeficit = diff;}
				}
				else if(p2 < p1){
					firstWon = true;
					array[0]->warHand.push_front(p1);
					array[0]->warHand.push_front(p2);
					int diff = ((array[0]->warHand.size())-(array[1]->warHand.size()));
					if(diff > array[1]->largestDeficit) {array[1]->largestDeficit = diff;}
				}
				else{
					if((array[0]->warHand.size() == 0) || (array[1]->warHand.size() == 0)){
						ret = false;
						preMatch = true;
						battleArr[matchCount] = battleCount;
						battleArr[matchCount+1] = warCount;
						matchCount+=2;
						if(array[0]->warHand.size() == 0){
							array[1]->warHand.push_front(p1);
							array[1]->warHand.push_front(p2);
							out << array[1]->playerName << " (" << array[1]->numRounds << ") DEFEATED " << array[0]->playerName << " in " << battleCount << " Battles and " << warCount << " Wars." << endl;
							array[0]->largestDeficit = 0;
						}
						else{
							array[0]->warHand.push_front(p1);
							array[0]->warHand.push_front(p2);
							out << array[0]->playerName << " (" << array[0]->numRounds << ") DEFEATED " << array[1]->playerName << " in " << battleCount << " Battles and " << warCount << " Wars." << endl;
							array[1]->largestDeficit = 0;
						}
					}
					else{
						warCount++;
						out << '\t' << "Battle " << battleCount << ": "<< array[0]->playerName << " (" << p1 << ") tied " << array[1]->playerName << " (" << p2 << ")" << endl;
						inWar = true;
						wasInWar = true;
						bool oneLargeEnough = true;
						bool twoLargeEnough = true;
						int size1 = array[0]->warHand.size();
						int size2 = array[1]->warHand.size();
						if(size1 < 4) {oneLargeEnough = false;}
						if(size2 < 4) {twoLargeEnough = false;}
						if(oneLargeEnough && twoLargeEnough){
							PlayingCard oneTemp1 = array[0]->warHand[array[0]->warHand.size()-1];
							PlayingCard oneTemp2 = array[0]->warHand[array[0]->warHand.size()-2];
							PlayingCard oneTemp3 = array[0]->warHand[array[0]->warHand.size()-3];
							array[0]->warHand.pop_back();
							array[0]->warHand.pop_back();
							array[0]->warHand.pop_back();
							PlayingCard twoTemp1 = array[1]->warHand[array[1]->warHand.size()-1];
							PlayingCard twoTemp2 = array[1]->warHand[array[1]->warHand.size()-2];
							PlayingCard twoTemp3 = array[1]->warHand[array[1]->warHand.size()-3];
							array[1]->warHand.pop_back();
							array[1]->warHand.pop_back();
							array[1]->warHand.pop_back();
							bool recursive = War::Battle(out, array); //poor initial planning, need Lab5 function version for War
							if(firstWon){
								array[0]->warHand.push_front(oneTemp1);
								array[0]->warHand.push_front(oneTemp2);
								array[0]->warHand.push_front(oneTemp3);
								array[0]->warHand.push_front(twoTemp1);
								array[0]->warHand.push_front(twoTemp2);
								array[0]->warHand.push_front(twoTemp3);
								array[0]->warHand.push_front(p1);
								array[0]->warHand.push_front(p2);
							}
							else{
								array[1]->warHand.push_front(oneTemp1);
								array[1]->warHand.push_front(oneTemp2);
								array[1]->warHand.push_front(oneTemp3);
								array[1]->warHand.push_front(twoTemp1);
								array[1]->warHand.push_front(twoTemp2);
								array[1]->warHand.push_front(twoTemp3);
								array[1]->warHand.push_front(p1);
								array[1]->warHand.push_front(p2);
							}
						}
						else{
							int oneCount = 0;
							int twoCount = 0;
							PlayingCard arr[8];
							for(int i=0; i<array[0]->warHand.size()-1; i++){
								arr[i] = array[0]->warHand[array[0]->warHand.size()-1];
								array[0]->warHand.pop_back();
								oneCount++;
								if(oneCount == 4) {break;}
							}
							for(int j=0; j<array[1]->warHand.size()-1; j++){
								arr[j+oneCount] = array[1]->warHand[array[1]->warHand.size()-1];
								array[1]->warHand.pop_back();
								twoCount++;
								if(twoCount == 4) {break;}
							}
							bool recursive = War::Battle(out,array);
							if(firstWon){
								array[0]->warHand.push_front(p1);
								array[0]->warHand.push_front(p2);
								for(int k=0; k<(oneCount + twoCount); k++){
									array[0]->warHand.push_front(arr[k]);
								}
							}
							else{
								array[1]->warHand.push_front(p1);
								array[1]->warHand.push_front(p2);
								for(int m=0; m<(oneCount + twoCount); m++){
									array[1]->warHand.push_front(arr[m]);
								}
							}
						}
						inWar = false;
					}
				}
				if(!inWar){
					if(!wasInWar){
						if(firstWon){out << '\t' << "Battle " << battleCount << ": "<< array[0]->playerName << " (" << p1 << ") defeated " << array[1]->playerName << " (" << p2 << "): " << array[0]->playerName << " " << array[0]->warHand.size() << ", " << array[1]->playerName << " " << array[1]->warHand.size() << endl;}
						else{out << '\t' << "Battle " << battleCount << ": " << array[1]->playerName << " (" << p2 << ") defeated " << array[0]->playerName << " (" << p1 << "): " << array[0]->playerName << " " << array[0]->warHand.size() << ", " << array[1]->playerName << " " << array[1]->warHand.size() << endl;}
					}
					else{
						out << array[0]->playerName << " " << array[0]->warHand.size() << ", " << array[1]->playerName << " " << array[1]->warHand.size() << endl;
						wasInWar = false;
					}
				}
				else{
					battleCount--;
					if(firstWon){out << '\t' << "War " << warCount << ": "<< array[0]->playerName << " (" << p1 << ") defeated " << array[1]->playerName << " (" << p2 << "): ";} // << array[0]->playerName << " " << array[0]->warHand.size() << ", " << array[1]->playerName << " " << array[1]->warHand.size() << endl;}
					else{out << '\t' << "War " << warCount << ": " << array[1]->playerName << " (" << p2 << ") defeated " << array[0]->playerName << " (" << p1 << "): ";} // << array[0]->playerName << " " << array[0]->warHand.size() << ", " << array[1]->playerName << " " << array[1]->warHand.size() << endl;}
				}
			}
		}
		//return ret;
		if(array[0]->warHand.size() == 0) {return array[1];}
		else{return array[0];}
	}
	Player* finalArray[2];
	finalArray[0] = Flip_Tournament(out, battleArr, (subSize/2), array);
	finalArray[1] = Flip_Tournament(out, battleArr, (subSize/2), &(array[subSize/2]));
	return Flip_Tournament(out, battleArr, 2,finalArray);
}

void War::resetDecks(Player* array[]){
	Deck deck;
	deck.shuffle();
	deque<PlayingCard> firstDeck;
	deque<PlayingCard> secondDeck;
	deck.halves(firstDeck, secondDeck);
	array[0]->warHand = firstDeck;
	array[1]->warHand = secondDeck;
}

void War::showStatistics(int battleArr[], int playerCount, Player* array[]){
	int battleSum = 0;
	int warSum = 0;
	int largestBattles = 0;
	int deficit = 0;
	int defIndex = 0;
	for(int i=0; i < 2*(playerCount-1); i++){
		if(i%2 == 0){
			battleSum += battleArr[i];
			if(battleArr[i] > largestBattles){largestBattles = battleArr[i];}
		}
		else {warSum += battleArr[i];}
	}
	for(int j=0; j < playerCount; j++){
		if(array[j]->largestDeficit >= deficit) {
			deficit = array[j]->largestDeficit;
			defIndex = j;
		}
	}
	cout << "Total battles fought: " << battleSum << endl;
	cout << "Total wars fought: " << warSum << endl;
	cout << "Average battles/match: " << (battleSum / 4) << endl;
	cout << "Most battles in one match: " << largestBattles << endl;
	cout << "Largest Deficit Overcome to win: " << array[defIndex]->playerName << " (" << deficit << " cards behind opponent)" << endl;
}