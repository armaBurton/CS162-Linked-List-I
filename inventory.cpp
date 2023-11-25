#include "doughnuts.h"
#include "inventory.h"

// constructors
Inventory::Inventory()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

/*
    Name:   loadData()
    Desc:   This function reads data from a file and
            stores it in array of classes
    input:  none
    output: none/prompt
    return: none
*/
bool Inventory::loadData()
{
    ifstream infile("voodoo.txt");

    if (!infile.is_open())
    {
        cerr << "File did not open. Program exiting.\n";
        return false;
    }

    char killThisLine[500];
    infile.getline(killThisLine, 500, '\n');

    int inventoryBuffer = 0;
    int typeBuffer;
    double priceBuffer;
    char nameBuffer[MAXCHAR];
    char addInsBuffer[MAXCHAR];

    while (infile >> inventoryBuffer)
    {
        infile.ignore(5, ';');
        infile.getline(nameBuffer, 101, ';');
        infile >> priceBuffer;
        infile.ignore(5, ';');
        infile.getline(addInsBuffer, 101, ';');
        infile >> typeBuffer;
        infile.ignore(50, '\n');
        Doughnut loadedDoughnut(
            inventoryBuffer,
            nameBuffer,
            priceBuffer,
            addInsBuffer,
            typeBuffer);
        insertDoughnut(loadedDoughnut);
    }

    // infile.close();

    return true;
}

/*
    Name:   writeToConsole()
    Desc:   This function reads through the array and displays
            the data to the console
    input:  none
    output: prompt
    return: none
*/
void Inventory::writeToConsole()
{
    Node * cur = head;
    int curCount = 1;
    if(count == 0){
        cout << "There are no doughnuts in your inventory" << endl;
    } else {
        while(cur != nullptr){
            cout << curCount++ << ". "
                 << cur->doughnut.getInventory() << ";"
                 << cur->doughnut.getName() << ";"
                 << fixed << setprecision(2) << "$" << cur->doughnut.getPrice() << ";"
                 << cur->doughnut.getAddIns() << ";"
                 << cur->doughnut.getType() << endl;
            cur = cur->next;
        }
    }
}

/*
    Name:   addDoughnut()
    Desc:   This function adds a doughnut to the array
    input:  char prompt[]
            int inventory
            char name[]
            double price
            char addIn[]
            int type
    output: prompt
    return: none
*/
void Inventory::addDoughnut()
{
    char prompt[101];
    int inventory;
    char name[101];
    double price;
    char addIns[101];
    int type;

    strcpy(prompt, "Enter a quantity (whole numbers between 1 and 200):");
    getInt(prompt, 1, 200, inventory);
    strcpy(prompt, "Enter the doughtname (100 characters or less): ");
    getCharacterString(prompt, 101, name);
    strcpy(prompt, "Enter the price (between 1.00 and 10.00): ");
    getDouble(prompt, 1, 10, price);
    strcpy(prompt, "Enter the ingredients (100 characters or less): ");
    getCharacterString(prompt, 101, addIns);
    strcpy(prompt, "Enter the type: (0)Ring, (1)Round, (2)Bar, (3)Cannoli, (4)Others): ");
    getInt(prompt, 0, 4, type);

    Doughnut tempDoughnut(inventory, name, price, addIns, type);
    insertDoughnut(tempDoughnut);
}

/*
    Name:   doughnutType()
    Desc:   This function interpertes the type value and
            return the corrisponding string
    input:  none
    output: none
    return: none
*/
void Inventory::doughnutType(int num, char doughnut[])
{
    switch (num)
    {
    case 0:
        strcpy(doughnut, "Ring");
        break;
    case 1:
        strcpy(doughnut, "Round");
        break;
    case 2:
        strcpy(doughnut, "Bar");
        break;
    case 3:
        strcpy(doughnut, "Cannoli");
        break;
    case 4:
        strcpy(doughnut, "Others");
        break;
    default:
        strcpy(doughnut, "Invalid Type");
        break;
    }
}

/*
    Name:   getInt()
    Desc:   This function reads a integer from the user
            performs data validataion
    input:  int intBuffer
    output: string prompt
    return: none
*/
void Inventory::getInt(char prompt[], const int min, const int max, int &value)
{
    int intBuffer;
    cout << prompt << endl;
    cin >> intBuffer;
    while (intBuffer > max || intBuffer < min || cin.fail())
    {
        if (intBuffer > max || intBuffer < min)
        {
            cout << "Values must be between " << min << " and " << max << " inclusive.\n"
                 << prompt << endl;
        }
        if (cin.fail())
        {
            cout << "You chose poorly\n"
                 << prompt << endl;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> intBuffer;
    }
    value = intBuffer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*
    Name:   getCharacterString()
    Desc:   This function reads input from the user in the
            form of a character string
    input:  char userPrompt[]
    output: char prompt[]
    return: none
*/
void Inventory::getCharacterString(char prompt[], const int max, char userPrompt[])
{
    char userInput[max];
    cout << prompt;
    cin.getline(userInput, max, '\n');
    strncpy(userPrompt, userInput, max);
}

/*
    Name:   getDouble()
    Desc:   This function reads data from the user in the
            form of a double
    input:  double
    output: prompt
    return: none
*/
void Inventory::getDouble(char prompt[], const int min, const int max, double &value)
{
    double doubleBuffer;
    cout << prompt << endl;
    cin >> doubleBuffer;
    while (doubleBuffer < min || doubleBuffer > max || cin.fail())
    {
        if (doubleBuffer < min || doubleBuffer > max)
        {
            cout << "Invalid price! Must be between " << min << " and " << max << " inclusive!\n"
                 << prompt << endl;
        }
        if (cin.fail())
        {
            cout << "You chose poorly\n"
                 << prompt << endl;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> doubleBuffer;
    }
    value = doubleBuffer;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/*
    Name:   getUpper()
    Desc:   This function converts the target cstring
            to uppercase
    input:  none
    output: none
    return: none
*/
void Inventory::getUpper(char makeUpper[], int &makeCount, char targetCString[])
{
    while (targetCString[makeCount] != '\0')
    {
        makeUpper[makeCount] = toupper(targetCString[makeCount]);
        makeCount++;
    }
    makeUpper[makeCount] = '\0';
}

/*
    Name:   insertDoughnut()
    Desc:   This function inserts a doughnut into the array in alphbetical order
    input:  none
    output: none
    return: none
*/
void Inventory::insertDoughnut(Doughnut & newDoughnut){
    Node * nodePtr = new Node;//Nodes have both a Doughnut and a next pointer
    Node * cur, * prev;
    nodePtr->next = nullptr;
    nodePtr->doughnut = newDoughnut;
    if(head == nullptr){    //if list is empty head = new node
        head = nodePtr;
        tail = nodePtr;
    } else if (strcmp(newDoughnut.getCapName(), head->doughnut.getCapName()) <= 0){ //add to the head
        nodePtr->next = head;
        head = nodePtr;
    } else if (strcmp(tail->doughnut.getCapName(), nodePtr->doughnut.getCapName()) <= 0) {  //add to the end of the list
        tail->next = nodePtr;
        tail = nodePtr;
    } else {
        cur = prev = head;
        while(strcmp(nodePtr->doughnut.getCapName(), cur->doughnut.getCapName()) >= 0){   //add into list
            prev = cur;
            cur = cur->next;
        }
        prev->next = nodePtr;
        nodePtr->next = cur;
    }
    count++;

    delete nodePtr;
}

int Inventory::getCount()
{
    return count;
}

/*
    Name:   removeByIndex()
    Desc:   This function reads an int from the user and
            then send the number to removeIndex()
    input:  int
    output: prompt
    return: none
*/
void Inventory::removeByIndex()
{
    int index;
    if (head != nullptr){
        char prompt[101] = "Enter index of the doughtnut to remove: ";
        writeToConsole();

        getInt(prompt, 1, count, index);
        while (index < 1 || index > count){
            strcpy(prompt, "Index out of bounds, please try again: ");
            getInt(prompt, 1, count, index);
        }
        removeIndex(index);
        cout << "after removal" << endl;
    } else {
        cout << "The list is empty." << endl;
    }
}

/*
    Name:   removeIndex()
    Desc:   This function removes the doughnut from the
            associated index
    input:  none
    output: none
    return: none
*/
void Inventory::removeIndex(const int index)
{
    Node * cur = head;
    Node * prev = nullptr;
    int curCount = 1;

    if (index == 1){
        if(head->next == nullptr){
            delete head;
            count--;
            head = tail = nullptr;
        } else {
            head = head->next;
            delete cur;
            count--;
        }
    } else {
        while (curCount < index){
            prev = cur;
            cur = cur->next;
            curCount++;
        }
        prev->next = cur->next;
        delete cur;
        count--;
        if (prev->next == nullptr){
            tail = prev;
        }
    }
}

/*
    Name:   listByType()
    Desc:   This function reads an int from the user then creates an array
            of doughnuts that have the matching type
    input:  int
    output: prompt, Doughnut
    return: none
*/
void Inventory::listByType()
{
    char prompt[101] = "Enter type: (0)Ring, (1)Round, (2)Bar, (3)Cannoli, (4)Other";
    int type, typeCount = 1;
    Node * cur = head;
    getInt(prompt, 0, 4, type);

    for(cur;cur;cur = cur->next){
        if(cur->doughnut.getType() == type){
            char donutType[MAXCHAR];
            doughnutType(type, donutType);
            cout << typeCount++ << ". "
                 << cur->doughnut.getInventory() << ";"
                 << cur->doughnut.getName() << ";"
                 << fixed << setprecision(2) << "$" << cur->doughnut.getPrice() << ";"
                 << cur->doughnut.getAddIns() << ";"
                 << donutType << endl;
        }
    }
}

/*
    Name:   listByIngredient()
    Desc:   This function reads a cstring from the user and then
            searches the addIns value for matches, It creates an array
            of type Doughnut when it finds matches
    input:  int
    output: prompt, Doughnut
    return: none
*/
void Inventory::listByIngredient()
{
    Node * cur = head;
    char prompt[101] = "Enter the search ingredient: ";
    char userPrompt[101];
    Doughnut doughnutsByIngredient[101];
    int newCount = 1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getCharacterString(prompt, 101, userPrompt);

    for(cur;cur;cur = cur->next){
        if (strstr(cur->doughnut.getAddIns(), userPrompt) != nullptr){
            char donutType[MAXCHAR];
            doughnutType(cur->doughnut.getType(), donutType);
            cout << newCount++ << ". "
                 << cur->doughnut.getInventory() << ";"
                 << cur->doughnut.getName() << ";"
                 << fixed << setprecision(2) << "$" << cur->doughnut.getPrice() << ";"
                 << cur->doughnut.getAddIns() << ";"
                 << donutType << endl;
        }
    }

    // for (int i = 0; i < count; i++)
    // {
    //     char tempAddIns[101];
    //     doughnuts[i].getAddIns(tempAddIns);
    //     if (strstr(tempAddIns, userPrompt) != nullptr)
    //     {
    //         doughnutsByIngredient[newCount] = doughnuts[i];
    //         newCount++;
    //     }
    // }
    // cout << "The doughnut(s) that match that ingredient are: \n";
    // writeToConsoleSelect(doughnutsByIngredient, newCount);
}

/*
    Name:   save and quit()
    Desc:   This function writes the data to a file then quits the program
    input:  none
    output: prompt
    return: none
*/
void Inventory::saveAndQuit()
{
    // ofstream outFile("voodoo.txt");
    // if (!outFile.is_open())
    // {
    //     cerr << "Error opening file.\n";
    //     return;
    // }
    // outFile << "inventory count;doughnut name;price;ingredients;type\n";
    // for (int i = 0; i < count; i++)
    // {
    //     char name[101];
    //     char addIns[101];
    //     doughnuts[i].getName(name);
    //     doughnuts[i].getAddIns(addIns);

    //     outFile << doughnuts[i].getInventory() << ";"
    //             << name << ";"
    //             << doughnuts[i].getPrice() << ";"
    //             << addIns << ";"
    //             << doughnuts[i].getType() << "\n";
    // }

    // outFile.close();

    // cout << "Doughnuts written to file! Thank you for using my program!!\n";
}

Inventory::~Inventory()
{
    delete head;
    delete tail;
}