/* Shivam Patel
 * Description: used inhertitance for each unit and virtual functions 
*/

using namespace std;
#include <iostream>

class Unit{
	public:
		int getHealth();
		int getRange();
		int getDamage();
		bool getMove();
		void setMove(bool);
		pair<int,int> getPosition();
		void print();
		virtual bool move(pair<int,int>,int,int) =0; //destination position, rowsize, column size
		virtual bool attack(pair<int,int>,int, Unit*)   =0; //unit, destination position visibility, victim's health
		int deadCount;
		bool isDead;
	protected:
		pair<int,int>pos;
		int health;
		int damage;
		int range;
		bool moveCheck;

};

class Base : public Unit{
	public:
		bool move(pair<int,int>, int, int);
		bool attack(pair<int,int>,int, Unit*);
		Base(int,int);
};

class Sniper : public Unit{
	public:	
		bool move(pair<int,int>, int, int);
		bool attack(pair<int,int>, int, Unit*);
		Sniper(int, int);
};

class Artillery : public Unit{
	public:	
		bool move(pair<int,int>, int , int);
		bool attack(pair<int,int>,int, Unit*);
		Artillery(int,int);
};

class Infantry : public Unit{
	public:	
		bool move(pair<int,int>, int, int);
		bool attack(pair<int,int>, int,Unit*);
		Infantry(int, int);
};

class Cavalry : public Unit{
	public:	
		bool move(pair<int,int>, int, int);
		bool attack(pair<int,int>,int,Unit*);
		Cavalry(int, int, int);
};

class Biker : public Unit{
	public:	
		int getHealth();
		int getRange();
		int getDamage();
		pair<int,int> getPosition();
		bool getMove();
		void setMove(bool);
		void print();
		bool move(pair<int,int>, int, int);
		bool attack(pair<int,int>, int,Unit*);
		Biker(int, int);
};



