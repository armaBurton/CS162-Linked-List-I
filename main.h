#ifndef MAIN_H
#define MAIN_H

// libraries
#include <iostream>
#include "doughnuts.h"
#include "inventory.h"

// Structs

// Constants
#define ARRLEN 100

// Function Prototypes
void greetings(int count);
void menu(char *option);
void menuOption(char *option, Inventory *inventory);

#endif
