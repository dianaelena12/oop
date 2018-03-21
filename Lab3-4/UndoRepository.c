#include "UndoRepository.h"

UndoRepo * createUndoRepo()
{
	UndoRepo* repo = (UndoRepo*)malloc(sizeof(UndoRepo));
	repo->lenght = 0;
	repo->cursor = 0;

	return repo;
}

void destroyUndoRepo(UndoRepo * repo)
{
	for (int i = 0; i < repo->lenght; i++)
	{
		destroyUndoType(repo->undoList[i]);
		repo->undoList[i] = NULL;
	}
	free(repo);
	repo = NULL;
}

int addToUndo(UndoRepo * undoRepo, UndoType * undo)
{
	undoRepo->undoList[undoRepo->lenght] = undo;
	undoRepo->lenght++;
	undoRepo->cursor++;

	return 1;
}

int returnCursor(UndoRepo * undoRepo)
{
	return undoRepo->cursor;
}

int getNrOfTheCommand(UndoRepo* repo, int index)
{
	return  repo->undoList[index]->nrOfTheCommand;
}

int executeAllCommands(UndoRepo * undo, int cursor, Controller* c)
{
	MaterialRepo* copy = EmptyRepo(c);
	int result;
	printf("%d cursor:\n", cursor);
	for (int i = 0; i < cursor ; i++)
	{
		printf("Intra aiiiiiciiii!!!!");
		printf("%d\n", getNrOfTheCommand(undo, i));
		result = 0;
		if (getNrOfTheCommand(undo, i) == 1)
		{
			printf("Hereeeeee\n");
			result = addMaterial(c, undo->undoList[i]->material->name, undo->undoList[i]->material->supplier, undo->undoList[i]->material->quantity, undo->undoList[i]->material->date);
		}
		if (undo->undoList[i]->nrOfTheCommand == 2)
		{
			result =delete(c, undo->undoList[i]->oldName) ;
		}
		if (undo->undoList[i]->nrOfTheCommand == 3)
		{
			result = updateTheName(c, undo->undoList[i]->oldName, undo->undoList[i]->newName);
		}
		if (undo->undoList[i]->nrOfTheCommand == 4)
		{
			result = updateTheSupplier(c, undo->undoList[i]->oldName, undo->undoList[i]->newName);
		}
		if (undo->undoList[i]->nrOfTheCommand == 5)
		{
			result = updateTheQuantity(c, undo->undoList[i]->oldName, undo->undoList[i]->newQ);
		}
		if (undo->undoList[i]->nrOfTheCommand == 6)
		{
			result = updateExpDate(c, undo->undoList[i]->oldName, undo->undoList[i]->newD);
		}
	}
	destroyRepo(copy);
	return 1;

}

int undoCommand(UndoRepo* repo)
{
	if (repo->cursor == 0)
		return 0;
	repo->cursor -= 1;
	return 1;
}

int redoCommand(UndoRepo* repo)
{
	if (repo->lenght == repo->cursor)
		return 0;
	repo->cursor += 1;
	return 1;
}
