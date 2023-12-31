#include "doughnuts.h"
#include "inventory.h"

// constructors
Inventory::Inventory()
{
    head = nullptr;
    tail = nullptr;
    count = 0;
}

//reads data from a file.
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

    infile.close();

    return true;
}

//inserts a new donut alphabetically by name into the list
void Inventory::insertDoughnut(Doughnut &newDoughnut){
    Node * nodePtr = new Node;
    Node * cur, * prev;
    nodePtr->next = nullptr;
    nodePtr->doughnut = newDoughnut;
    char newCapName[101], headCapName[101], tailCapName[101], curCapName[101];

    newDoughnut.getCapName(newCapName);
    if (head != nullptr){
        head->doughnut.getCapName(headCapName);
    }
    if (tail != nullptr){
        tail->doughnut.getCapName(tailCapName);
    }
    if(head == nullptr){
        head = nodePtr;
        tail = nodePtr;
    } else if (strcmp(newCapName, headCapName) <= 0){
        nodePtr->next = head;
        head = nodePtr;
    } else if (strcmp(tailCapName, newCapName) <= 0){
        tail->next = nodePtr;
        tail = nodePtr;
    } else { 
        cur = prev = head;
        cur->doughnut.getCapName(curCapName);
        while (strcmp(newCapName, curCapName) >= 0){
            prev = cur;
            cur = cur->next;
            cur->doughnut.getCapName(curCapName);           
        }
        prev->next = nodePtr;
        nodePtr->next = cur;
    }
    count++;
}

//writes the contents of the list to the console.
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

//Prompts the user for a new donut
//creates a new donut and sends it back to the function that called it 
//through a reference parameter
void Inventory::addDoughnut(Doughnut & donut)
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
    donut = tempDoughnut;
}

//this is called when writing to the console
//the donut type is provided as an int and then returned
//as a cstring
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

//displays the prompt provided in the prompt[] paramter
//reads an integer from the user and checks against the min and max
//returns the int by reference
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

//displays the prompt provided in the prompt[] paramter
//reads an array of characters from the user
//returns the cstring by reference
void Inventory::getCharacterString(char prompt[], const int max, char userPrompt[])
{
    char userInput[max];
    cout << prompt;
    cin.getline(userInput, max, '\n');
    strncpy(userPrompt, userInput, max);
}


//displays the prompt provided in the prompt[] paramter
//reads an double from the user and checks against the min and max
//returns the double by reference
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

//returns the count
int Inventory::getCount()
{
    return count;
}

//prompts the user for an index of a donut to remove from the list
//then displays the new list to the console
void Inventory::removeByIndex()
{
    int index;
    if (head != nullptr){
        cout << endl;
        char prompt[101] = "Enter index of the doughtnut to remove: ";

        writeToConsole();
        getInt(prompt, 1, count, index);

        while (index < 1 || index > count){
            strcpy(prompt, "Index out of bounds, please try again: ");
            getInt(prompt, 1, count, index);
        }
        removeIndex(index);
        cout << endl <<  "After removal of index: " << index << endl;
        writeToConsole();
    } else {
        cout << "The list is empty." << endl;
    }
}

//handles the removal of the index provided by the user
void Inventory::removeIndex(const int index)
{
    Node * cur = head;
    Node * prev = nullptr;
    int curCount = 1;

    if (index == 1){                    //in the case of the deletion of the first element 
        if(head->next == nullptr){      //if next = nullptr then reset the list
            delete head;
            count--;
            head = tail = nullptr;
        } else {                        //otherwise assign head next
            head = head->next;          
            delete cur;                 //delete the old head
            count--;
        }
    } else {                            //otherwise
        while (curCount < index){       //traverse the list until you reach index
            prev = cur;                 
            cur = cur->next;            
            curCount++;                 //until curCount == index
        }
        prev->next = cur->next;         //remove cur by setting prev->next to cur->next
        delete cur;                     //delete the cur node
        count--;                        //decrement count
        if (prev->next == nullptr){     //reset the tail if prev->next == nullptr
            tail = prev;
        }
    }
}

//prompts the user for a int associated with a type of donut
//then traverses through the list printing the corrisponding donuts
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

//prompts the user for an ingredient then traverses the list searching for
//donuts that have matching ingredients and writing them to console
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
}

//writes the current list to a file and closes the program
void Inventory::saveAndQuit()
{
    ofstream outFile("voodoo.txt");
    if (!outFile.is_open())
    {
        cerr << "Error opening file.\n";
        return;
    }
    outFile << "inventory count;doughnut name;price;ingredients;type\n";
    Node * cur = head;
    for (cur;cur;cur = cur->next){
        outFile << cur->doughnut.getInventory() << ";"
                << cur->doughnut.getName() << ";"
                << cur->doughnut.getPrice() << ";"
                << cur->doughnut.getAddIns() << ";"
                << cur->doughnut.getType() << endl;
    }

    outFile.close();

    cout << "Doughnuts written to file! Thank you for using my program!!\n";
}

//while head != nullptr, traverse the list and delete each element
Inventory::~Inventory()
{
    Node * cur = head;
    while (head != nullptr){
        cur = head->next;
        delete head;
        head = cur;
    }
}
