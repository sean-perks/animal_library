// Sean Perks, Assignment 4, creature header file


#ifndef __CREATURE_H_
#define __CREATURE_H__

const int ARR_SIZE = 40;
const int STR_SIZE = 128;
const int ERROR = -1;

#include <iostream> // angle brackets mean go to the library files.
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cstring>  // If a library starts with c, it's written in c.
using namespace std;

class Creature {
	private: // Properties are private.
		char * name; // Dynamic c-strings.
		char * domain;
		int count;
		double weight;
		int status;
		char * description;
	
	public:
		Creature(); // default constructor.
		Creature(const char * nameArg, const char * domainArg, int countArg, int statusArg, double weightArg, const char * descArg); // fill constructor
		// copy constructor.
		Creature(const Creature &);
		~Creature(); // destructor.
		// Overloaded assignment operator.
		const Creature & operator=(const Creature & other);
		Creature operator+(const Creature & other); // ???
		friend bool operator>=(const Creature & c1, const Creature & c2);
		friend ostream& operator <<(ostream & out, const Creature & creature);
		Creature & operator++(); // pre increment
		Creature operator++(int unused); // post-increment int unused only changes the signature
		
		
		// Getters
		const char * getName();
		const char * getDomain();
		int getCount();
		const char * getStatus();
		int getStatusNumber();
		double getWeight();
		const char * getDescription();
		
		// Setters
		void setName(const char *);
		void setDomain(const char *);
		void setCount(int);
		void setStatus(int);
		void setWeight(double);
		void setDescription(const char *);
		
	

};

// helpers
void toLower(char str[]);
double readDouble();
int readInt();

#endif
