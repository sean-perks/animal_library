#include "fauna.h"

/* Fauna cpp file A04.
 * Sean Perks With massive help from: Robert Martin, CS162 */


// Default constructor
Fauna::Fauna() {
    count = 0;
    head = tail = nullptr; // start with empty list

}

// copy constructor
Fauna::Fauna(const Fauna & other) {
    head = tail = nullptr;
}


Fauna::~Fauna() {
    // Traverse and delete as we go.
    Node * cur = head;
    while(cur != nullptr) {
        cur = cur->next;
        delete head;     // theMovie destructor is invoked automatically.
        head = cur;
    }
}

// prints just the header.
void printHeader() {
    cout << setw(5) << left << "No." 
	<< setw(25) << left << "Name" 
	<< setw(15) << left << "Domain" 
	<< setw(10) << "Count" 
	<< setw(26) << "Status" 
	<< setw(10) << "Weight" 
	<< setw(17) << left << "Description" << endl;
    
	cout << setw(5) 
	<< "----" << setw(25) 
	<< "-----" << left << setw(15) 
	<< "------" << setw(10) 
	<< "-----" << setw(26) 
	<< "------" << setw(10) 
	<< "------" << setw(17) 
	<< "-----------" << endl;
}

// print all function
void Fauna::printCreatures() {
    
    printHeader();
    
    // traverse list
    Node * cur = head;
    int line = 1;
    
    while(cur != nullptr) {
	// We use overloaded << instead of: cout << (*cur).theCreature.getStatusNumber() << endl;
	cout << right << setw(2) << line << ": " << cur->theCreature << endl;
	cur = cur->next;
	line++;
    }
}

// inserts an creature
void Fauna::insert(Creature & toAdd) {
    Node * temp = new Node;
    temp->theCreature = toAdd;
    temp->next = nullptr;
    
    if(head == nullptr) { // list is empty
	head = temp;
	tail = temp;
    }
    else { // head is not nullptr
	Node * cur = head;
	Node * prev = nullptr;
	
	while (cur != nullptr && strcmp(cur->theCreature.getName(), temp->theCreature.getName()) <= 0) {
            prev = cur;
            cur = cur->next;
        }

	// first in list 
        if (prev == nullptr) { 
            temp->next = head;
            head = temp;
        } 
	// goes at end
        else if (cur == nullptr) { 
            prev->next = temp;
            tail = temp; 
        } 
        else { // somewhere in middle
            prev->next = temp;
            temp->next = cur;
        }
	
	// debug
	//cout << "Tail: " << (*tail).theCreature.getName() << endl;
    
    }
    
    count++;
}



bool Fauna::addCreature() {
    bool success = false;
    char nameArg[STR_SIZE], domainArg[STR_SIZE], descArg[STR_SIZE];
    int countArg = 0; 
    int statusArg = -1;
    double weightArg = 0.0;

    cout << "What is the name of the creature? ";
    cin.getline(nameArg, STR_SIZE);
        
    cout << "Which domain does this creature occupy? ";
    cin.getline(domainArg, STR_SIZE);
        
    cout << "What is the estimated population? ";
    countArg = readInt();
        
    while (statusArg < 0 || statusArg > 4) {
        cout << "Enter the animal's ICUN Status: 0 - CriticallyEndangered, 1 - NearEndangered, 2 - Threatened, 3 - NearThreatened, 4 - LeastConcern: ";
        statusArg = readInt();
    }
    
    cout << "How much does the creature weigh (pounds)? ";
    weightArg = readDouble();

    cout << "Enter a description for the creature: ";
    cin.getline(descArg, STR_SIZE);
    

     // Use the constructor that takes arguments to construct toAdd.
    Creature toAdd(nameArg, domainArg, countArg, statusArg, weightArg, descArg);
    // for reference the constructor with args is: Creature(const char * nameArg, const char * domainArg, int countArg, int statusArg, double weightArg, const char * descArg)
    insert(toAdd);
    success = true;

    return success;
}

Creature & Fauna::operator[](int index) {
    int nodeCount = 0;
    Node * cur = head;
    while(nodeCount < index) {
        cur = cur->next;
        nodeCount++;
    }
    return cur->theCreature;
}


// def to remove a struct from the creature strruct list
bool Fauna::remove() {
    Node *prev = head, *cur = head;
    bool success = false;
    char removeName[STR_SIZE];
    // possibility 1, empty list.
    if (head != nullptr) {
	cout << "What creature would you like to remove? ";
	cin.getline(removeName, STR_SIZE);
	
	while(cur && strcmp(cur->theCreature.getName(), removeName) != 0) {
	    prev = cur;
	    cur = cur->next;
	}
	
	if(cur) {  // if cur is nullptr, node not found. skip
	    // option 1. if cur == head then we are deleting the first node
	    if(cur == head) {
		head = head->next;
		delete cur;
		if(cur == nullptr) {  // we deleted last node, update the tail
		    tail = nullptr;
		}
	    }
	    // option 2, match is the last node
	    else if(cur == tail) {
		tail = prev;
		prev->next = nullptr;
		delete cur;
	    }
	    // option 3, match not first or last node
	    else {
		prev->next = cur->next;
		delete cur;
	    }
	    success = true;
	}
    }
    if(!success) {
	cout << "Not found. No creature deleted." << endl;
    }
    else {
	cout << "The creature " << removeName << " was successfully removed." << endl;
    }
    return success;
}

// used to search the db by name
void Fauna::searchByName() {
    Node *cur = head;
    char findName[STR_SIZE];
    // possibility 1, empty list.
    if (head != nullptr) {
	cout << "What creature would you like to search for? ";
	cin.getline(findName, STR_SIZE);
	
	while(cur && strcmp(cur->theCreature.getName(), findName) != 0) {
	    cur = cur->next;
	}
	
	if(cur) { // if cur is not nullptr then there wqas a match
	    printHeader();
	    // We use overloaded << instead of: cout << (*cur).theCreature.getStatusNumber() << endl;
	    cout << right << setw(2) << "1.   " << cur->theCreature << endl;
	}
	else {
	    cout << findName << " not found." << endl; 
	}
    }
    
    else {
	cout << "Database empty." << endl;
    }
}

// list all creatures for a domain
void Fauna::searchByDomain() {
    Node *cur = head;
    char findDomain[STR_SIZE];
    bool found = false;
    int count = 1;
    // possibility 1, empty list.
    if (head != nullptr) {
	cout << "What domain would you like to search? ";
	cin.getline(findDomain, STR_SIZE);
	printHeader();
	while(cur) {
	    if(strcmp(cur->theCreature.getDomain(), findDomain) == 0){
		cout << right << setw(2) << count << ".  " << cur->theCreature << endl;
		found = true;
		count++;
	    }
	    cur = cur->next;
	}
	
	if(found == false) {
	    cout << findDomain << " not found in domain's." << endl; 
	}
    }
    
    else {
	cout << "Database empty." << endl;
    }	
}


int Fauna::loadCreatures() {
    count = 0;
    int num = 0;
    double weight;
    char str[STR_SIZE];
    Creature toLoad; // Let's use this to load each creature to pass to insert().
    cout << "Enter file name (example galapagos.txt): ";
    cin.getline(fileName, STR_SIZE);
    if (strcmp(fileName, "g") == 0) {
        strcpy(fileName, "galapagos.txt");
    }
    inFile.open(fileName); 
    while(!inFile.is_open() && strcmp(fileName, "quit") != 0) {
        cout << "That file did not open. Please try again or type quit: ";
        cin.getline(fileName, STR_SIZE);
        inFile.open(fileName);
    }
    // At this point, the user either typed quit or the file is open.
    if(strcmp(fileName, "quit") == 0) {
        cout << "You have chosen to quit. No creature's loaded." << endl;
        count = ERROR;
    }
    
    else { 
		// If we're here, then the file is open and ready to load.
        while(inFile.getline(str, STR_SIZE, ';')) {
	    toLoad.setName(str);
	    
	    inFile.getline(str, STR_SIZE, ';');
	    toLoad.setDomain(str);
	    
	    inFile >> num;
	    inFile.ignore();
	    toLoad.setCount(num);

	    inFile >> num;
	    inFile.ignore();
	    toLoad.setStatus(num);

	    inFile >> weight;
	    inFile.ignore();
	    toLoad.setWeight(weight);
	    

	    inFile.getline(str, STR_SIZE);
	    toLoad.setDescription(str);
	    
	    insert(toLoad);
	    
	}
        // Check to see if we are out of room.
        
    }
    inFile.close();
    return count;  
}

//This function writes the data to the file
void Fauna::writeData() {
    // traverse list
    Node * cur = head;
    

    outFile.open(fileName);
    if(!outFile) {
        cout << "Output file did not open!! Program exiting!!!" << endl;
        exit(0);
    }

    else {
	while(cur != nullptr) {
	    outFile << (*cur).theCreature.getName() << ";" << (*cur).theCreature.getDomain() << ";" 
	    <<  (*cur).theCreature.getCount() << ";" << (*cur).theCreature.getStatusNumber() << ";" 
	    << (*cur).theCreature.getWeight() << ";" << (*cur).theCreature.getDescription() << endl;
	    cur = cur->next;
	}
	outFile.close();
    }

}

	
	
bool quitMenu() {
    char yn = 'k';
    cout << endl << "Would you like to save? (y/n): ";
    
    while (tolower(yn) != 'y' || tolower(yn) != 'n') {
        cin >> yn;
        if (tolower(yn) == 'y') {
            return true;
	}
        else if (tolower(yn) == 'n'){
            return false;
	}
        else {
            cout << "Must enter either y or n: ";
	}
    
    }
    return false;
}
