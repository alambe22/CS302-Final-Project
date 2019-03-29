#include <string>
using namespace std;
class Unit{
public:
	virtual int getMovesLeft() =0;
	virtual int getMaxMoves()=0;
	virtual int getUsedMoves()=0;
	virtual void setUsedMoves(int usedMoves)=0;
	virtual bool move(char direction, int numTiles) =0;
};

class Base : public Unit{
public:
	Base(int r, int c);
	int getMovesLeft() {return maxMoves-usedMoves;}
	int getMaxMoves() {return maxMoves;}
	int getUsedMoves() {return usedMoves;}
	void setUsedMoves(int usedMoves) {this->usedMoves=usedMoves;}


	bool move(int row, int col);
	int r;
	int c;
	string name;
private:
	int maxMoves;
	int usedMoves;
};

class Infantry : public Unit{
public:
	Infantry(int r, int c);
	int getMovesLeft() {return maxMoves-usedMoves;}
	int getMaxMoves() {return maxMoves;}
	int getUsedMoves() {return usedMoves;}
	void setUsedMoves(int usedMoves) {this->usedMoves=usedMoves;}

	bool move(int row, int col);
	int r;
	int c;
	string name;
private:
	int maxMoves;
	int usedMoves;
};
