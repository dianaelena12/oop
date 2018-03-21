#pragma once
#include "UndoType.h"
#include "Controller.h"

typedef struct
{
	UndoType* undoList[200];
	int lenght;
	int cursor;
}UndoRepo;
/*
	struct type defined to create an undoRepo type object
*/
UndoRepo* createUndoRepo();
/*
	creates an undoRepo object, which is an array similar to MaterialRepo
	Input - nothing
	Output - the object of the undoType
*/
void destroyUndoRepo(UndoRepo* repo);
/*
	frees the memory allocated for the undoRepo
	Input: - a pointer to the array of type undoRepo
	Output: - nothing
*/
int addToUndo(UndoRepo* undoRepo, UndoType* undo);
/*
	adds a new object of undoType to the array
	Input: - a pointer to the array of type undoRepo
		   - a pointer to the object of undoType
	Output: - 1, if the object was added
			- 0, otherwise

*/
int returnCursor(UndoRepo* undoRepo);
/*
	returns the cursor of the undoRepo object
	Input: - a pointer to the array of type undoRepo
	output: - an integer number
*/
int executeAllCommands(UndoRepo * undo, int cursor, Controller* c);
/*
	remakes all the commands on the UndoRepo array from 0 to cursor
	Input: - a pointer to the array of type undoRepo
		   - the cursor of type int
		   - a pointer to an object of type controller
*/
int undoCommand(UndoRepo* repo);
/*
	will format the cursor so the undo command will be uccessfully executed
	Input: - a pointer to the array of type undoRepo
	Output: - 1, if everything is ok
			- 0, otherwise
*/
int redoCommand(UndoRepo* repo);
/*
	will format the cursor so the redo command will be uccessfully executed
	Input: - a pointer to the array of type undoRepo
	Output: - 1, if everything is ok
			- 0, otherwise
*/