#include "Player.h"

using namespace std;

class War{
	public:
		War(Player** array, int size);
		bool Battle(ostream& out, Player** array);
		int getBattleCount();
		int getWarCount();
		Player* Flip_Tournament(ostream& out, int battleArr[], int subSize = 0, Player* array[] = 0);
		void resetDecks(Player* array[]);
		void showStatistics(int battleArr[], int playerCount, Player* array[]);

	private:
		Player** arr;
		int arrSize;
		bool firstWon = false;
		bool preMatch = true;
		bool inWar = false;  //this
		bool wasInWar = false; //and this only necessary for printing purposes to output file
		int warCount = 0;
		int battleCount = 0;
		int matchCount = 0;
		//Boolean values work for single war; a double war is still counted accurately but an interior step is logged
};