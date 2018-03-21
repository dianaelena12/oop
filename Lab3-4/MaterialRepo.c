#include "MaterialRepo.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

MaterialRepo* createRepository()
{
	MaterialRepo* repo = (MaterialRepo*)malloc(sizeof(MaterialRepo));
	repo->lenght = 0;
	return repo;
}

MaterialRepo* emptyTheRepository(MaterialRepo* repo)
{
	MaterialRepo* copy = createRepository();
	for (int i = 0; i < repo->lenght; i++)
	{
		copy->materials[i] = repo->materials[i];
		copy->lenght++;
	}
	free(repo);
	repo->lenght = 0;
	/*for (int i = 0; i > repo->lenght; i++)
	{
		//free(repo->materials[i]);
		repo->materials[i] = NULL;
	}*/
	//repo->lenght = 0;
	return copy;

}

void destroyRepo(MaterialRepo * repo)
{
	for (int i = 0; i < repo->lenght; i++)
	{
		destroyMaterial(repo->materials[i]);
		repo->materials[i] = NULL;
	}
	free(repo);
	repo = NULL;
}

Material* findMaterialByName(MaterialRepo* repo, char* name)
{
	for (int i = 0; i < repo->lenght; i++)
	{
		if (strcmp(repo->materials[i]->name, name) == 0)
			return repo->materials[i];
	}
	return NULL;
}

int returnIndexOfAMaterial(MaterialRepo * repo, Material* m)
{
	for (int i = 0; i < repo->lenght; i++)
		if (m == repo->materials[i])
			return i;
	return -1;
}

int add(MaterialRepo* repo, Material* m)
{
	Material* exista = findMaterialByName(repo, m->name);
	if (exista != NULL)
	{
		double newQ = m->quantity;
		newQ = newQ + exista->quantity;
		updateQuantity(repo, m->name, newQ);
		return 2;
	}
	else
	{
		repo->materials[repo->lenght] = m;
		repo->lenght++;
	}

	return 1;
}

int updateQuantity(MaterialRepo* repo,char* name,double quantity)
{
	Material* result = findMaterialByName(repo, name);
	int index = returnIndexOfAMaterial(repo, result);
	if ( index == -1)
		return 0;
	repo->materials[index]->quantity = quantity;

	return 1;
}

int updateName(MaterialRepo* repo, char* name, char newN[])
{
	Material * result = findMaterialByName(repo, name);
	if (result == NULL)
		return 0;
	int index = returnIndexOfAMaterial(repo, result);
	if (index == -1)
		return 0;
	strcpy(repo->materials[index]->name , newN);
	return 1;
}

int updateSupplier(MaterialRepo* repo, char* name, char* supplier)
{
	Material* result = findMaterialByName(repo, name);
	int index = returnIndexOfAMaterial(repo, result);
	if (index == -1)
		return 0;
	strcpy(repo->materials[index]->supplier, supplier);
	return 1;
}

int deleteMaterial(MaterialRepo* repo, char* name)
{
	Material* m = findMaterialByName(repo, name);
	if (m == NULL)
		return 0;
	int index = -1;
	for (int i=0; i< repo->lenght;i++)
		if (m == repo->materials[i])
		{
			index = i;
			break;
		}
	while (index < repo->lenght - 1)
	{
		repo->materials[index] = repo->materials[index + 1];
		index++;
	}
	repo->lenght--;
	return 1;
}


int updateExpDate(MaterialRepo* repo, char* name, ExpDate date)
{
	Material* result = findMaterialByName(repo, name);
	int index = returnIndexOfAMaterial(repo, result);
	if (index == -1)
		return 0;
	repo->materials[index]->date.day = date.day;
	repo->materials[index]->date.month = date.month;
	repo->materials[index]->date.year = date.year;

	return 1;
}

int checkValability(MaterialRepo* repo, Material* m)
{
	SYSTEMTIME1 str_t;
	GetSystemTime(&str_t);

	int day, month, year;
	day = str_t.wDay;
	month = str_t.wMonth;
	year = str_t.wYear;

	if (m->date.year < year)
		return 0;
	if (m->date.month < month && m->date.year <= year)
		return 0;
	if (m->date.day < day && m->date.year <= year && m->date.month <= month)
		return 0;
	return 1;
}

Material* getMaterialOnPosition(MaterialRepo* repo, int position)
{
	if (position < 0 || position >= repo->lenght)
		return NULL;
	return repo->materials[position];
}

int getLenght(MaterialRepo* repo)
{
	return repo->lenght;
}

// Tests...........................................

void testAdd()
{
	MaterialRepo* repo = createRepository();
	ExpDate date2;
	date2.day = 11;
	date2.month = 1;
	date2.year = 2017;
	Material* m1 = createMaterial( "Cacao", "Dr.Oetker", 10, date2);
	add(repo, m1);
	assert(getLenght(repo) == 1);
	assert(strcmp(getName(getMaterialOnPosition(repo, 0)), "Cacao") == 0);
	Material* m2 = createMaterial("Oat", "Dr.Oetker", 11, date2);
	assert(add(repo, m2) == 1);
	assert(getLenght(repo) == 2);

	destroyRepo(repo);
	//destroyMaterial(m1);
	//destroyMaterial(m2);
}

void testUpdate()
{
	MaterialRepo* repo = createRepository();
	ExpDate date2;
	date2.day = 11;
	date2.month = 1;
	date2.year = 2017;
	Material* m1 = createMaterial("Cacao", "Dr.Oetker", 10, date2);
	Material* m2 = createMaterial("Oat", "Dr.Oetker", 11, date2);
	Material* m3 = createMaterial("Butter", "Market", 1, date2);
	add(repo, m1);
	add(repo, m2);
	add(repo, m3);
	ExpDate newDate; newDate.day = 13; newDate.month = 10; newDate.year = 1999;
	assert(updateExpDate(repo, "Oat", newDate) == 1);
	assert(updateExpDate(repo, "Banana", newDate) != 1);
	assert(updateName(repo, "Cacao", "Cocoa") == 1);
	assert(strcmp(getName(getMaterialOnPosition(repo, 0)), "Cocoa") == 0);
	assert(updateQuantity(repo, "Butter", 10) == 1);
	assert(getQuantity(m3) == 10);
	assert(updateSupplier(repo, "Butter", "Dr.Oetker") == 1);
	assert(strcmp(getSupplier(m3) , "Dr.Oetker") == 0);

	destroyRepo(repo);
	//destroyMaterial(m1);
	//destroyMaterial(m3);
	//destroyMaterial(m2);

}

void testDelete()
{
	MaterialRepo* repo = createRepository();
	ExpDate date2;
	date2.day = 11;
	date2.month = 1;
	date2.year = 2017;
	Material* m1 = createMaterial("Cacao", "Dr.Oetker", 10, date2);
	Material* m2 = createMaterial("Oat", "Dr.Oetker", 11, date2);
	Material* m3 = createMaterial("Butter", "Market", 1, date2);
	add(repo, m1);
	add(repo, m2);
	add(repo, m3);
	assert(deleteMaterial(repo, "Oat") == 1);
	assert(deleteMaterial(repo, "Oat") == 0);
	assert(findMaterialByName(repo, "Oat") == NULL);

	destroyRepo(repo);
	//destroyMaterial(m1);
	//destroyMaterial(m2);
	//destroyMaterial(m3);
}

void testsMaterialRepository()
{
	testAdd();
	testUpdate();
	testDelete();
}