#pragma once
#include "MaterialRepo.h"

typedef struct
{
	MaterialRepo* repo;
}Controller;
/*
	struct type defined to create an object of type controller
*/

Controller* createController(MaterialRepo* repo);
/*
	creates an object of type controller
	Input: - a pointer to a materialRepo type array
	Output - the controller
*/
void destroyController(Controller* c);
/*
	frees the memory allocated for the controller
	Input: - a pointer to a controller type object
	Output: - nothing
*/
int addMaterial(Controller* c, char* name, char* supplier, double quantity, ExpDate date);
/*
	adds a new material
	Input: - a pointer to a controller type object
		   - pointer to the name
		   - pointer to the supplier
		   - a double variable containing the quantity
		   - a expDate variable containing the expiration date
	Output: - 1
			- 0
*/
MaterialRepo* getRepo(Controller* c);
/*
	returns a pointer to the array of type MaterialRepo
	Input: - a pointer to a controller type object
	Output: -  the array
*/
int updateTheName(Controller* c, char* name, char* newN);
/*
	Input: - a pointer to a controller type object
	- pointer to a string containing the current name
	- a pointer to a string containing the new name
	Output: - 1 , if the update was successfully
	- 0, otherwise
*/
int updateTheSupplier(Controller* c, char* name, char* supplier);
/*
	Input: - a pointer to a controller type object
	- pointer to a string containing the name
	- a pointer to a string containing the new name for the supplier
	Output: - 1 , if the update was successfully
	- 0, otherwise
*/
int delete(Controller* c, char* name);
/*
	Input: - a pointer to a controller type object
	- a pointer to a string containing the name of the material
	Output: - 1, if the material was deleted succesfully
	- 0, otherwise
*/
int updateExpDatectrl(Controller* c, char* name, ExpDate date);
/*
	Input: - a pointer to a controller type object
	- pointer to a string containing the  name of the material
	- a variable of type expDate containing the new date of the material
	Output: - 1 , if the update was successfully
	- 0, otherwise
*/
int updateTheQuantity(Controller* c, char* name, double quantity);
/*
	Input: - a pointer to a controller type object
			- pointer to a string containing the  name
			- a variable of type double containing the new quantity
	Output: - 1 , if the update was successfully
			- 0, otherwise

*/
MaterialRepo* EmptyRepo(Controller* c);
/*
	will empty the array of pointers containing the object, without deleting the objects
	Input: - a pointer to a controller type object
	Output: nothing
*/