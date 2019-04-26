/* Shivam Patel
 * Title: Unit's header file
 * Description: used inhertitance for each unit and pure virtual functions to attack and move along with some helper functions
*/

using namespace std;
#include <iostream>
#include <vector>
//base class
class Unit{
	public:
		int getHealth();
		void setHealth(int);
		int getRange();
		int getDamage();
		bool getMove();
		void setMove(bool);
		bool getAttack();
		void setAttack(bool);
		pair<int,int> getPosition();
		void print();
		virtual bool move(vector<vector<pair<char,bool> > >,pair<int,int>,int,int) =0; //grid vector, destination position, rowsize, column size
		virtual bool attack(int, Unit*)   =0; //visibility, the unit being attacked
		int deadCount; //keep track of how many turns unit has been dead before it can respawn
		bool isDead;
	protected:
		pair<int,int>pos;
		int health;
		int damage;
		int range;
		bool moveCheck;
		bool attackCheck;

};

//derived classes
//each unit will have a different movement and attack style 
//in each constructor of these units, the row and column the unit will be placed on the map is passed in
class Base : public Unit{
	public:
		bool move(vector<vector<pair<char,bool> > >,pair<int,int>, int, int);
		bool attack(int, Unit*);
		Base(int,int);
};

class Sniper : public Unit{
	public:	
		bool move(vector<vector<pair<char,bool> > >,pair<int,int>, int, int);
		bool attack(int, Unit*);
		Sniper(int, int);
};

class Artillery : public Unit{
	public:	
		bool move(vector<vector<pair<char,bool> > >,pair<int,int>, int , int);
		bool attack(int, Unit*);
		Artillery(int,int);
};

class Infantry : public Unit{
	public:	
		bool move(vector<vector<pair<char,bool> > >,pair<int,int>, int, int);
		bool attack(int,Unit*);
		Infantry(int, int);
};

class Cavalry : public Unit{
	public:	
		bool move(vector<vector<pair<char,bool> > >,pair<int,int>, int, int);
		bool attack(int,Unit*);
		Cavalry(int, int, int);
};

class Biker : public Unit{
	public:
		bool move(vector<vector<pair<char,bool> > >,pair<int,int>, int, int);
		bool attack(int,Unit*);
		Biker(int, int);
};



