#ifndef __FAUNA__
#define __FAUNA__
#include "creature.h"

/* Fauna header file A05.
 * Sean Perks  CS162 */


class Fauna {
    private:
	struct Node {
	    Creature theCreature;
            Node * next; // chain nodes using the next pointers
            Node * prev;
	};
	Node * head, * tail;
	
	int count; // actual num creatures in array
	
	char fileName[STR_SIZE];
	ifstream inFile;
	ofstream outFile; 
	void insert(Creature & toAdd);
	
    public:
	Fauna(); // Default constructor.
	Fauna(const Fauna &); // no copies allowed
	Fauna & operator=(const Fauna &) = delete; // no assignments allowed
	~Fauna(); // destructor.
	int loadCreatures();
	void writeData();
	bool addCreature();


	
	void remove();
	void searchByDomain();
	void printCreatures();
	void printCreaturesReverse();
	void searchByName();
	
	 // Overloading the square brackets (subscript operator).
	Creature & operator[](int); 
	
	// friend Movie operator+(Movie & firstMovie, Movie & secondMovie); // external function.
	// Creature & at(int);
};



// Helpers
// just prints the header
void printHeader();
// quit menu is display only and does not need access to any class members
bool quitMenu();

#endif
