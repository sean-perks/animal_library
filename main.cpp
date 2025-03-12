#include "fauna.h"

 /*
  * Assignment 4

  Created by sean perks 3/5/2025
  
 */
    
int main() {
	int count = 0;

	// Create a Fauna object.
	Fauna myCreatures;
	char choice = ' ';
	cout << "Welcome to Fauna Database!" << endl << endl;
	count = myCreatures.loadCreatures(); 
	if(count != ERROR) {
		cout << count << " Creature(s) loaded to the LIBRARY" << endl;
		cout << endl << "What would you like to do?" << endl;
		cout << "(L)ist, (A)dd, (R)emove, (S)earch, List by (D)omain, or (Q)uit? ";  
		cin >> choice;
		cin.ignore();
		choice = tolower(choice);
		while(choice != 'q') {
			switch(choice) {
				case 'l':
					myCreatures.printCreatures();
					break; 
				case 'a':
					cout << "Add an creature!" << endl << endl;
					myCreatures.addCreature();
					break;
				case 'r':
					myCreatures.printCreatures();
					cout << endl;
					myCreatures.remove();
					break;
				case 's':
					myCreatures.searchByName();
					break;
				case 'd':
					myCreatures.searchByDomain();
					break;
			}

			cout << endl << "What would you like to do?" << endl;
			cout << "(L)ist, (A)dd, (R)emove, (S)earch, List by (D)omain, or (Q)uit? ";  
			cin >> choice;
			cin.ignore();
			choice = tolower(choice);

		}
	}
	// ASk if want to save, save with writeData and exit
	bool save = quitMenu();
	if (save){
		myCreatures.writeData();
		cout << "Saving!" << endl;
	}
	cout << "Goodbye!!" << endl;
	return 0;

}
