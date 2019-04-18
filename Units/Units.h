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
		virtual pair<int,int> getPosition() =0;
		virtual void print()    =0;
		virtual bool move(pair<int,int>, int,int) =0; //destination position, rowsize, column size
//		virtual void attack(int visibility)   =0; //current position, destination position, visibility

	

};

class Base : public Unit{
	public:
		int getHealth();
		int getRange();
		pair<int,int> getPosition();
		int getDamage();
		void print();
		bool move(pair<int,int>, int, int);
		void attack();
		Base(int,int);
	private:
		pair<int,int>pos;
		int health;
		int damage;
		int range;
};

class Sniper : public Unit{
	public:	
		int getHealth();	
		int getRange();
		pair<int,int> getPosition();
		int getDamage();
		void print();
		bool move(pair<int,int>, int, int);
		void attack();
		Sniper(int , int);
	private:
		pair<int,int> pos;
		int health;
		int damage;
		int range;
};

class Artillery : public Unit{
	public:	
		int getHealth();
		int getRange();
		int getDamage();
		pair<int,int> getPosition();
		void print();
		bool move(pair<int,int>, int , int);
		void attack();
		Artillery(int row,int col);
	private:
		pair<int,int>pos;
		int health;
		int damage;
		int range;
};

class Infantry : public Unit{
	public:	
		int getHealth();
		int getRange();
		int getDamage();
		pair<int,int> getPosition();
		void print();
		bool move(pair<int,int>, int, int);
		void attack();
		Infantry(int row, int col);
	private:
		pair<int,int>pos;
		int health;
		int damage;
		int range;	

};

class Cavalry : public Unit{
	public:	
		int getHealth();
		int getRange();
		int getDamage();
		pair<int,int> getPosition();
		void print();
		bool move(pair<int,int>, int, int);
		void attack();
		Cavalry(int row, int col, int columnSize);
	private:
		pair<int,int>pos;
		int health;
		int damage;
		int range;
};

class Biker : public Unit{
	public:	
		int getHealth();
		int getRange();
		int getDamage();
		pair<int,int> getPosition();
		void print();
		bool move(pair<int,int>, int, int);
		void attack();
		Biker(int row, int col);
	private:
		pair <int,int> pos;
		int health;
		int damage;
		int range;
};



