// Sean Perks, Assignment 4, creature cpp file.  

#include "creature.h"


// default constructor
Creature::Creature() {
	count = 0;
	status = 0;
	weight = 0.0;
	name = nullptr;
	domain = nullptr;
	description = nullptr;
}

// constructor with arguments
Creature::Creature(const char * nameArg, const char * domainArg, int countArg, int statusArg, double weightArg, const char * descArg) {
	count = countArg;
	status = statusArg;
	weight = weightArg;
	
	name = new char[strlen(nameArg) + 1];
	strcpy(name, nameArg);
	
	domain = new char[strlen(domainArg) + 1];
	strcpy(domain, domainArg);
	
	description = new char[strlen(descArg) + 1];
	strcpy(description, descArg);
}

// copy constructor
Creature::Creature(const Creature &other) {
	count = other.count;
	status = other.status;
	weight = other.weight;
	
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	
	domain = new char[strlen(other.domain) + 1];
	strcpy(domain, other.domain);
	
	description = new char[strlen(other.description) + 1];
	strcpy(description, other.description);
}

//Assignment operator
const Creature & Creature::operator=(const Creature & other) {
	if(name != nullptr) { // mem allocated if true
		delete[] name;
	}
	
	if (domain != nullptr) {
		delete[] domain;
	}
	
	if (description != nullptr) {
		delete[] description;
	}
	
	name = new char[strlen(other.name) + 1];
	domain = new char[strlen(other.domain) + 1];
	description = new char[strlen(other.description) + 1];
	
	strcpy(name, other.name);
	strcpy(domain, other.domain);
	strcpy(description, other.description);
	
	count = other.count;
	status = other.status;
	weight = other.weight;
	
	return *this; // ? return current object ?
}

Creature Creature::operator+(const Creature & other) {
    Creature retCreature;
	strcpy(retCreature.name, name);
	strcpy(retCreature.name, " and ");
	strcpy(retCreature.name, other.name);
	return retCreature;	
}
	
// friend function  keyword friend allows direct access to privatre members
bool operator>=(const Creature & c1, const Creature & c2) {
	bool retValue = false;
	if(strcmp(c1.name, c2.name) >= 0) {
		retValue = true;
	}
	return retValue;
}

// destructor
Creature::~Creature() {
	if(name != nullptr) { // mem allocated if true
		delete[] name;
	}
	
	if (domain != nullptr) {
		delete[] domain;
	}
	
	if (description != nullptr) {
		delete[] description;
	}
}

// Pree Increment
Creature & Creature::operator++() {
    count++;
    return *this;
} 

// POST increment by value (returning a local variable
Creature Creature::operator++(int u) {
    Creature retCreature = *this;
    count++;
    return retCreature;
}


ostream& operator<<(ostream & out, const Creature & creature) {
    char status[STR_SIZE]; 
    if (creature.status == 0) {
	strcpy(status, "Critically Endangered");
    }
    else if(creature.status == 1) {
	strcpy(status, "Near Endangered");
    }
    else if(creature.status == 2) {
	strcpy(status, "Threatened");
    }
    else if(creature.status == 3) {
	strcpy(status, "Near Threatened");
    }
    else if(creature.status == 4) {
	strcpy(status, "Least Concern");
    }
    else {
	strcpy(status, "none");
    }
    out << left << setw(25) << creature.name << setw(15) << 
    creature.domain << setw(10) << creature.count << setw(26) <<
    status << setw(10) << creature.weight << setw(16) << 
    left << creature.description;
    
    return out;

}


// NAME
void Creature::setName(const char * nameArg) {
    if(name != nullptr) { // Name already points to memory if true
        delete[] name;
    }
    name = new char[strlen(nameArg) + 1];
    strcpy(name, nameArg);
}

const char * Creature::getName() {
    return name;
}


// DOMAIN
void Creature::setDomain(const char * domainArg) {
	if(domain != nullptr) { // Name already points to memory if true
		delete[] domain;
	}
	domain = new char[strlen(domainArg) + 1];
	strcpy(domain, domainArg);
}

const char * Creature::getDomain() {
	return domain;
}


// COUNT
void Creature::setCount(int countArg) {
	count = countArg;
}

int Creature::getCount() {
	return count;	
}


// STATUS
void Creature::setStatus(int choice = -1) {
    while (choice < 0 || choice > 4) {
        cout << "Enter the animal's ICUN Status: 0 - CriticallyEndangered, 1 - NearEndangered, 2 - Threatened, 3 - NearThreatened, 4 - LeastConcern: ";
        choice = readInt();
    }
    
    status = choice;
}

const char * Creature::getStatus() {
    switch (status) { 
        case 0:
            return "Critically Endangered";

            break;
        case 1:
            return "Endangered";

            break;
        case 2:
            return "Vulnerable";
            break;
        case 3:
            return "Near Threatened";
            break;
        case 4:
            return "Least Concern";
            break;
        default:
            return "none";
    }
}

int Creature::getStatusNumber() {
    return status;	
}

// WEIGHT
void Creature::setWeight(double weightArg){
    weight = weightArg;
}

double Creature::getWeight(){
    return weight;
}


// DESCRIPTION
void Creature::setDescription(const char * descriptionArg) {
    if(description != nullptr) { // Name already points to memory if true
        delete[] description;
    }
    description = new char[strlen(descriptionArg) + 1];
    strcpy(description, descriptionArg);
}

const char * Creature::getDescription() {
    return description;
}


// read, validate and return an int
int readInt() {	
    int temp = 0;
    cin >> temp;
    //data validation
    while (!cin || temp < 0) {


        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid integer!! Please try again: ";
        cin >> temp;
    }
    cin.ignore(100, '\n');

    return temp;
}

// read, validate and return an int
double readDouble() {	
    double temp = 0.0;
    cin >> temp;
    //data validation
    while (!cin || temp < 0) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid number, please try again: ";
        cin >> temp;
    }
    cin.ignore(100, '\n');

    return temp;
}


void toLower(char str[]) {
    for (int i = 0; str[i] != '\0'; ++i) {
        str[i] = std::tolower(str[i]);
    }
}



