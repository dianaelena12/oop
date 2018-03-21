#pragma once
#include "Material.h"
#include <stdlib.h>


typedef struct
{
	int nrOfTheCommand;
	Material* material;
	char* oldName;
	char* newName;
	double newQ;
	ExpDate newD;
}UndoType;
/*
	struct type defined to simulate a stack, where all the commands from the UI will be memorised

*/

UndoType* createUndoType(int nrOfTheCommand, Material* material, char* string, char* newN, double newQ, ExpDate newD);
/*
	creates an undoType object
	Input: - integer number , which holds the number of the command
		   - material type object containing a material
		   - a pointer to a string
		   - another pointer to a string
		   - double type variable containing a quantity
		   - expDate type variable containing the expiration date
	Output: a pointer to a UndoType object
*/
void destroyUndoType(UndoType* undo);
/*
	frees all the memory allocated for the undotype object
	Input: -  a pointer to an object of UndoType
	Output: none
*/
char* getOldName(UndoType* undo);
/*
	returns a string containing the parameter oldName for the undoType object
	Input: -  a pointer to an object of UndoType
	Output: - a string
*/
Material* getMaterial(UndoType* undo);
/*
	returns a pointer containing the parameter material for the undoType object
	Input: -  a pointer to an object of UndoType
	Output: - a pointer to a Material type object
*/
int getCommnadNumber(UndoType* undo);
/*
	returns an int containing the parameter commandNumber for the undoType object
	Input: -  a pointer to an object of UndoType
	Output: - an integer number from 1 to 6
*/
double getUndoQuantity(UndoType* undo);
/*
	returns a double containing the parameter newQ(quantity) for the undoType object
	Input: -  a pointer to an object of UndoType
	Output: - a double
*/
ExpDate getUndoEXPDate(UndoType* undo);
/*
	returns a variable containing the parameter newD(expiration date) for the undoType object
	Input: -  a pointer to an object of UndoType
	Output: - a varible of type EXPdate
*/
char* getNewName(UndoType* undo);
/*
	returns a string containing the parameter newName for the undoType object
	Input: -  a pointer to an object of UndoType
	Output: - a string
*/
