#include "UndoType.h"

UndoType * createUndoType(int nrOfTheCommand, Material * material, char * string, char* newN, double newQ, ExpDate newD)
{
	UndoType* undo = (UndoType*)malloc(sizeof(UndoType));
	undo->material = (Material*)malloc(sizeof(Material));
	undo->material = material;
	undo->oldName = (char*)malloc(sizeof(char)* (strlen(string) + 1));
	strcpy(undo->oldName, string);
	undo->nrOfTheCommand = nrOfTheCommand;
	undo->newName = (char*)malloc(sizeof(char)* (strlen(newN) + 1));
	strcpy(undo->newName, newN);
	undo->newQ = newQ;
	undo->newD = newD;

	return undo;

}

void destroyUndoType(UndoType * undo)
{
	destroyMaterial(undo->material);
	undo->material = NULL;
	free(undo->oldName);
	undo->oldName = NULL;
	free(undo->newName);
	undo->newName = NULL;
	free(undo);
	undo = NULL;
}

char * getOldName(UndoType * undo)
{
	return undo->oldName;
}

Material * getMaterial(UndoType * undo)
{
	return undo->material;
}

int getCommnadNumber(UndoType * undo)
{
	return undo->nrOfTheCommand;
}

double getUndoQuantity(UndoType * undo)
{
	return undo->newQ;
}

ExpDate getUndoEXPDate(UndoType * undo)
{
	return undo->newD;
}

char * getNewName(UndoType * undo)
{
	return undo->newName;
}
