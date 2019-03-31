/* Shivam Patel
 * Description: used inhertitance for each unit and virtual functions 
*/

using namespace std;
#include <iostream>

class Base{
	public:
		int healthStat();
		void print();
		Base();
	private:
		int health;
};

class Unit{
	public:
		virtual int getHealth() =0;
		virtual int getRange()  =0;
		virtual int getDamage() =0;
		virtual void print()    =0;
		virtual void move(pair<int,int>, pair<int,int>, int,int) =0; //current position, destination position, rowsize, column size
//		virtual void attack(int visibility)   =0; //current position, destination position, visibility

	

};

class Sniper : public Unit{
	public:	
		int getHealth();	
		int getRange();
		int getDamage();
		void print();
		void move(pair<int,int>, pair<int,int>, int, int);
		void attack();
		Sniper();
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
		void print();
		void move(pair<int,int>, pair<int,int>, int , int);
		void attack();
		Artillery();
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
		void print();
		void move(pair<int,int>, pair<int,int>, int, int);
		void attack();
		Infantry();
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
		void print();
		void move(pair<int,int>, pair<int,int>, int, int);
		void attack();
		Cavalry(int rowsize);
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
		void print();
		void move(pair<int,int>, pair<int,int>, int, int);
		void attack();
		Biker();
	private:
		pair <int,int> pos;
		int health;
		int damage;
		int range;
};



