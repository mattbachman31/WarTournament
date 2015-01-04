#include "War.h"
#include <ctype.h>

using namespace std;

int main(int argc, char* argv[]){
	if(argc == 1){
		cout << "Need input and output files. Terminating Program." << endl;
		return 0;
	}
	if(argc == 2){
		cout << "Need output file. Terminating Program." << endl;
		return 0;
	}
	if(argc > 3){
		cout << "Too many command prompts given. Only need executable, input and output files. Terminating program." << endl;
		return 0;
	}
	srand(unsigned(time(0)));
	ifstream in1(argv[1]);
	ofstream out(argv[2]);
	char c;
	int playerCount = 0;
	if(!in1.fail()){
		while(in1.get(c)){
			if(c == '\n'){playerCount++;}
		}
	}
	in1.close();
	Player* array[playerCount];
	int power = 2;
	while(playerCount != power){
		if(power > playerCount){
			cout << "Number of participants must equal power of 2 for a proper bracket! Program terminating." << endl;
			return 0;
		}
		power *= 2;
	}
	ifstream in2(argv[1]);
	string oldTemp;
	for(int i=0; i<playerCount; i++){
		string temp;
		getline(in2,temp,'\n');
		//cout << temp << endl;
		if((i%2 == 0)) {oldTemp = temp;}
		if((i%2 == 1)){
			deque<PlayingCard> firstDeck;
			deque<PlayingCard> secondDeck;
			array[i-1] = new Player(firstDeck, oldTemp);
			array[i] = new Player(secondDeck, temp);
		}
	}
	in2.close();
	Player first = *(array[0]);
	Player second = *(array[1]);
	int battleArr[2*(playerCount-1)];
	War newWar(array,sizeof(array)/sizeof(array[0]));
	Player* winner = newWar.Flip_Tournament(out,battleArr);
	out << "Flip Championship Winner is: " << winner->playerName << endl;
	cout << "Flip Championship Winner is: " << winner->playerName << endl;
	for(int i=0; i<2*(playerCount-1); i+=2){
		out << battleArr[i] << endl;
	}
	newWar.showStatistics(battleArr, playerCount, array);
	for(int i=0; i< playerCount; i++){
		delete array[i];
	}
	return 0;
}
