#include "Controller.h"
#include <string.h>
#include <stdlib.h>

Controller* createController(MaterialRepo* repo)
{
	Controller* controller = (Controller*)malloc(sizeof(Controller));
	controller->repo = repo;

	return controller;
}

MaterialRepo* EmptyRepo(Controller* c)
{
	return emptyTheRepository(c->repo);
}

void destroyController(Controller* c)
{
	destroyRepo(c->repo);
	free(c);
	c = NULL;
}

int addMaterial(Controller* c, char* name, char* supplier, double quantity, ExpDate date)
{
	int result = -1;
	Material* m = createMaterial(name, supplier, quantity, date);
	result = add(c->repo, m);
	if (0 == result)
		destroyMaterial(m);
	return result;
}
int updateTheQuantity(Controller* c, char* name, double quantity)
{
	return updateQuantity(c->repo, name, quantity);
}
int updateExpDatectrl(Controller* c, char* name, ExpDate date)
{
	return updateExpDate(c->repo, name, date);
}

int updateTheName(Controller* c, char* name, char* newN)
{
	int result = updateName(c->repo, name, newN);
	return result;

}

int updateTheSupplier(Controller* c, char* name, char* supplier)
{
	int result = updateSupplier(c->repo, name, supplier);
	return result;
}

int delete(Controller* c, char* name)
{
	int result = deleteMaterial(c->repo, name);
	return result;
}

MaterialRepo* getRepo(Controller* c)
{
	return c->repo;
}
