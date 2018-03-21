#pragma once
#include "Controller.h"
#include "UndoRepository.h"

typedef struct
{
	Controller* controller;
}UI;
/*
	struct type defined to create an object of type UI
*/
UI* createUI(Controller* c);
/*
	creates an object of type UI
	Input: a pointer to an object of type controller
	Output: a pointer to an object of type UI
*/
void destroyUI(UI* ui);
/*
	frees the memory allocated for the object of type UI
*/
void printMenu();
/*
	prints the commands available to the user
*/
int validCommand(int command);
/*
	will validate if the command read is valid or not
	Input: - int command, an integer
	Output: - 1, if the command is valid
	        - 0, otherwise
*/
int readCommand(const char* command);
/*
	will read a string then turn it into an int
	Input: - string command
	Output:- int command
*/
void startUI(UI* ui);
/*
	here we call all the functions outside the UI and complete the commands
	Input: a pointer to UI
	Output: the result of the commands
*/
int addMaterialUI(UI* ui, Material* m);
/*
	functions which calls the addMateril function from Controller and interprets it's result
	Input:- pointer to UI
		  - pointer to a material type object
	Output: -1, if it was added succesfully
			-0, otherwise
*/
void printAllMaterials(UI* ui);
/*
	displays on screen all the available materials from the repository
	Input:- pointer to UI
	Output: none
*/
int validDate(ExpDate date);
/*
	will check if a date is valid
	Input: -  variable of type expDate
	Output: - 1, if it's valid
			- 0 , if it's invalid
*/
void printMaterialsContainingAGivenStringDecending(UI* ui);
/*
	will do exactly what the name of the function says
	Input:- pointer to UI
	Output: none
*/
Material* read();
/*
	will read a new material
	Input: none
	Output: a pointer to a newly created object of type material
*/
void printMaterialsFromASupplierAscedingByExpirationMonth(UI* ui);
/*
	will show all the materials from a given supplier decending by the expiration month
*/
