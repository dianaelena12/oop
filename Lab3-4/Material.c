#include "Material.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Material* createMaterial(char* name, char* supplier, double quantity, ExpDate date)
{
	Material* m = (Material*)malloc(sizeof(Material));
	m->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(m->name, name);
	m->supplier = (char*)malloc(sizeof(char) * (strlen(supplier) + 1));
	strcpy(m->supplier, supplier);
	m->quantity = quantity;
	m->date = date;
	
	return m;
}

void destroyMaterial(Material* m)
{
	free(m->name);
	free(m->supplier);
	m->name = NULL;
	m->supplier = NULL;
	free(m);
	m = NULL;
}

char* getName(Material* m)
{
	return m->name;
}

char* getSupplier(Material* m)
{
	return m->supplier;
}

double getQuantity(Material* m)
{
	return m->quantity;
}

ExpDate getExpirationDate(Material* m)
{
	return m->date;
}

void toString(Material m, char str[])
{
	sprintf(str, "Product %s, supplied by %s, has a quantity of %.2lf and it's expiration date is %d.%d.%d", m.name, m.supplier, m.quantity,m.date.day,m.date.month,m.date.year);
}
