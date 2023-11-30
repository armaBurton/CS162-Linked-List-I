#ifndef INVENTORY_H
#define INVENTORY_H

#include "doughnuts.h"

const int CAP = 1;
const int GROW = 5;
// const int MAXCHAR = 101;

struct Node {
    Doughnut doughnut;
    Node * next;
};

class Inventory
{
    Node * head;
    Node * tail;
    int count;

public:
    // constructors
    Inventory();
    ~Inventory();

    void removeByIndex();
    void removeIndex(const int index);
    void listByIngredient();
    void listByType();
    void getInt(char prompt[], const int min, const int max, int &value);
    void insertDoughnut(Doughnut &newDoughnut);
    void getUpper(char makeUpper[], int &makeCount, char targetCString[]);
    void getCharacterString(char prompt[], const int max, char userPrompt[]);
    void getDouble(char prompt[], const int min, const int max, double &value);
    void addDoughnut(Doughnut & donut);
    // void addDoughnut();
    bool loadData();
    int getCount();
    void writeToConsole();
    void doughnutType(int num, char doughnut[]);
    void saveAndQuit();
};

#endif