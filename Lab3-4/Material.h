#pragma once
/*
 struct type defined for creating an expiration date

*/
typedef struct
{
	int year;
	int month;
	int day;
}ExpDate;

/*
 struct type defined for creating an object of type Material

*/
typedef struct
{
	char* name;
	char* supplier;
	double quantity;
	ExpDate date;
}Material;

Material* createMaterial(char* name, char* supplier, double quantity, ExpDate date);
/*
	creates an object of type material
	parameters: - name
				- supplier
				- quantity
				- expiration date, of type expDate
	returns: - an aobject of type material
*/
void destroyMaterial(Material* m);
/*
	parameters: - pointer of type Material
	frees the memory allocated for an object of type material
	returns: - nothing
*/
char* getName(Material* m);
/*
	parameters: -  pointer of type Material
	returns: - pointer to the name of the material
*/
char* getSupplier(Material* m);
/*
	parameters: -  pointer of type Material
	returns: - pointer to the supplier of the material

*/
double getQuantity(Material* m);
/*
	parameters: -  pointer of type Material
	returns: - the quantity of type double of the material

*/
ExpDate getExpirationDate(Material* m);
/*
	parameters: -  pointer of type Material
	returns: - the expiration date of type ExpDate of the material

*/
void toString(Material m, char str[]);
/*
	parameters: - object of type material
				- string of type char
	returns : -  nothing
	turns the name, supplier, quantity and expiration date into a string, to be printed on the console later

*/
void testsMaterialRepository();
/*
	here are all the tests for the Material Repo
*/
