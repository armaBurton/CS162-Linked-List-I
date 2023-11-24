#ifndef INVENTORY_H
#define INVENTORY_H

const int CAP = 1;
const int GROW = 5;

class Inventory
{
private:
    Doughnut *doughnuts;
    int count;
    int capacity;
    void growList();

public:
    // constructors
    Inventory();
    // Inventory(Doughnut *, int);
    // copy constructor
    // Inventory(const Doughnut &aDoughnut);

    void removeByIndex();
    void removeIndex(const int index);
    void listByIngredient();
    void listByType();
    void getInt(char prompt[], const int min, const int max, int &value);
    void insertDoughnut(Doughnut &newDoughnut);
    void getUpper(char makeUpper[], int &makeCount, char targetCString[]);
    void getCharacterString(char prompt[], const int max, char userPrompt[]);
    void getDouble(char prompt[], const int min, const int max, double &value);
    void addDoughnut();
    bool loadData();
    int getCount();
    void writeToConsole();
    void writeToConsoleSelect(Doughnut *doughnuts, const int count);
    void doughnutType(int num, char doughnut[]);
    void saveAndQuit();
    ~Inventory();
};

#endif