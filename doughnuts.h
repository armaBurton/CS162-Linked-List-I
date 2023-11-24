#ifndef DOUGHNUTS_H
#define DOUGHNUTS_H

using namespace std;

// libraries
#include <fstream>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <limits>
#include <cctype>

const int MAXCHAR = 101;

class Doughnut
{
private:
	int inventory = 0;
	char *name;
	double price;
	char *addIns;
	int type = 0;

public:
	// constructors
	Doughnut();
	Doughnut(int, char *, double, char *, int);

	// copy constructor
	Doughnut(Doughnut &aDoughnut);

	const Doughnut& operator=( Doughnut &aDoughnut);

	void setInventory(int);
	void setName(char *);
	void setPrice(double);
	void setAddIns(char *);
	void setType(int);
	int getInventory();
	void getName(char *);
	double getPrice();
	void getAddIns(char *);
	int getType();
	// int getInventory() const;
	// void getName(char *) const;
	// double getPrice() const;
	// void getAddIns(char *) const;
	// int getType() const;

	~Doughnut();
};

#endif
