/* Shivam Patel
 * Description: used inhertitance for each unit and virtual functions 
*/

using namespace std;
#include <iostream>

class Unit{
	public:
		virtual int getHealth() =0;
		virtual int getRange()  =0;
		virtual int getDamage() =0;
		virtual bool getMove()  =0;
		virtual void setMove(bool)  =0;
		virtual pair<int,int> getPosition() =0;
		virtual void print()    =0;
		virtual bool move(pair<int,int>,int,int) =0; //destination position, rowsize, column size
		virtual bool attack(pair<int,int>,int, Unit*)   =0; //unit, destination position visibility, victim's health
};

class Base : public Unit{
	public:
		int getHealth();
		int getRange();
		pair<int,int> getPosition();
		int getDamage();
		bool getMove();
		void setMove(bool);
		void print();
		bool move(pair<int,int>, int, int);
		bool attack(pair<int,int>,int, Unit*);
		Base(int,int);
	private:
		pair<int,int>pos;
		int health;
		int damage;
		int range;
		bool moveCheck;
};

class Sniper : public Unit{
	public:	
		int getHealth();	
		int getRange();
		pair<int,int> getPosition();
		int getDamage();
		bool getMove();
		void setMove(bool);
		void print();
		bool move(pair<int,int>, int, int);
		bool attack(pair<int,int>, int, Unit*);
		Sniper(int , int);
	private:
		pair<int,int> pos;
		int health;
		int damage;
		int range;
		bool moveCheck;
};

class Artillery : public Unit{
	public:	
		int getHealth();
		int getRange();
		int getDamage();
		pair<int,int> getPosition();
		bool getMove();
		void setMove(bool);
		void print();
		bool move(pair<int,int>, int , int);
		bool attack(pair<int,int>,int, Unit*);
		Artillery(int row,int col);
	private:
		pair<int,int>pos;
		int health;
		int damage;
		int range;
		bool moveCheck;
};

class Infantry : public Unit{
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
		Infantry(int row, int col);
	private:
		pair<int,int>pos;
		int health;
		int damage;
		int range;
		bool moveCheck;

};

class Cavalry : public Unit{
	public:	
		int getHealth();
		int getRange();
		int getDamage();
		pair<int,int> getPosition();
		bool getMove();
		void setMove(bool);
		void print();
		bool move(pair<int,int>, int, int);
		bool attack(pair<int,int>,int,Unit*);
		Cavalry(int row, int col, int columnSize);
	private:
		pair<int,int>pos;
		int health;
		int damage;
		int range;
		bool moveCheck;
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
		Biker(int row, int col);
	private:
		pair <int,int> pos;
		int health;
		int damage;
		int range;
		bool moveCheck;
};



