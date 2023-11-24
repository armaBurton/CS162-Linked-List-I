/******************************************************************************
# Author:           Arma Burton
# Assignment:       Assignment 01 Classes
# Date:             10/10/23
# Description:      This program reads a text-file.
					Allows a user to add an item.
					List all items.
					List items by type.
					Find an item by ingredient.
					Remove an item by index
					Save.
					Quit
# Input:            Int, double, char[]
# Output:           Int, double, char[]
# Sources:          Lab 1 specifications
#                   ChatGPT
#****************************************************************************/
#include "main.h"
#include "doughnuts.h"
#include "inventory.h"

int main()
{
	Inventory *inventory = new Inventory();

	char option[10];

	if (!inventory->loadData())
	{
		cerr << "Failed to load data" << endl;
		return 1;
	}

	greetings(inventory->getCount());

	do
	{
		menu(option);
		menuOption(option, inventory);
	} while (option[0] != 'q');

	return 0;
}

// Name:   greetings()
// Desc:   This function reads a string from the user and returns it
// input:  none
// output: prompt
// return: none
void greetings(int count)
{
	cout << endl
		 << "Welcome to Voodoo Doughnut!\n"
		 << "This program will help you manage your doughnut inventory.\n"
		 << count << " doughnuts added from the data file.\n"
		 << endl;
}

/*
	Name:   menu()
	Desc:   This function displays the menu then
			prompts the user for an option
	input:  char *option
	output: prompt
	return: string name
*/
void menu(char *option)
{
	char inputBuffer;
	cout << endl
		 << "Pick an option from below:\n"
		 << endl
		 << "(A)Add a new doughnut\n"
		 << "(L)List doughnuts\n"
		 << "(T)List doughtnuts by certain type\n"
		 << "(I)Search doughnuts by ingredients\n"
		 << "(R)Remove doughnut by index\n"
		 << "(Q)Quit\n"
		 << endl;

	cin >> inputBuffer;
	option[0] = tolower(inputBuffer);
}

/*
	Name:   menuOption()
	Desc:   Interperets the user input and runs the corrisponding
			function
	input:  none
	output: none/prompt
	return: none
*/
void menuOption(char *option, Inventory *inventory)
{
	switch (*option)
	{
	case 'a':
		inventory->addDoughnut();
		break;
	case 'l':
		inventory->writeToConsole();
		break;
	case 't':
		inventory->listByType();
		break;
	case 'i':
		inventory->listByIngredient();
		break;
	case 'r':
		inventory->removeByIndex();
		break;
	case 'q':
		inventory->saveAndQuit();
		break;
	default:
		cout << "Invalid option!! Please try again!" << endl;
		break;
	}
}
