#pragma once
#include "Material.h"
#include <Windows.h>
/*
	struct type defined to create an array of Material type objects
*/
typedef struct
{
	Material*   materials[200];
	int lenght;
}MaterialRepo;


/*
	struct type defined to get the current time and date

*/
typedef struct {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME1;

MaterialRepo* createRepository();
/*
	here we create the array of materials
	parameters : - none
	returns : - a pointer to an  array of type MaterialRepo
*/
void destroyRepo(MaterialRepo* repo);
/*
	frees all the memory allocated for the MaterialRepo type
	parameters: - pointer to a materialRepo array
	returns: - nothing
*/
Material* findMaterialByName(MaterialRepo* repo, char* name);
/*
  Is searching for an existing material in the repository of materials
  Input: - repo, a pointer to the MaterialRepo
         - name, string containing the name of the material we are searching for
  Output: - -1 if the material was not found
          - the index of the position of the material in MaterialRepo
*/

int add(MaterialRepo* repo, Material* m);
/*
	
	Adds a material to the repository of material.
	Input:	- repo - pointer to the MaterialRepo
			- m - material
	Output: 1 - if the material was sucessfully added
			0 - if the material could not be added, as another material with the same name already exists in the MaterialRepo.
*/
Material* getMaterialOnPosition(MaterialRepo* repo, int position);
/*
	returns a pointer to a material type object found on a certain index in the array
	Input:  - a pointer to an array of type MaterialRepo
			- an index on the array

	Output: - a pointer to a material type object
			- NULL, if the material does not exist
*/
int getLenght(MaterialRepo* repo);
/*
	returns the lenght of the array
	Input:  - a pointer to an array of type MaterialRepo
*/
int updateName(MaterialRepo* repo, char* name, char* newN);
/*
	updates the name of a material in the array
	Input:  - a pointer to an array of type MaterialRepo
			- pointer to a string containing the current name
			- a pointer to a string containing the new name
	Output: - 1 , if the update was successfully
			- 0, otherwise

*/
int updateQuantity(MaterialRepo* repo, char* name, double quantity);
/*
	updates the quantity of a material in the array
	Input:  - a pointer to an array of type MaterialRepo
			- pointer to a string containing the  name
			- a variable of type double containing the new quantity
	Output: - 1 , if the update was successfully
			- 0, otherwise
*/
int updateSupplier(MaterialRepo* repo, char* name, char supplier[]);
/*
	updates the supplier of a material in the array
	Input:  - a pointer to an array of type MaterialRepo
			- pointer to a string containing the name
			- a pointer to a string containing the new name for the supplier
	Output: - 1 , if the update was successfully
			- 0, otherwise
*/
int deleteMaterial(MaterialRepo* repo, char* name);
/*
	deletes the a certain material after it's name
	Input - a pointer to an object of type MaterialRepo
		  - a pointer to a string containing the name of the material
	Output: - 1, if the material was deleted succesfully
			- 0, otherwise
*/
int updateExpDate(MaterialRepo* repo, char* name, ExpDate date);
/*
	updates the expiration date of a material in the array
	Input:  - a pointer to an array of type MaterialRepo
			- pointer to a string containing the  name of the material
			- a variable of type expDate containing the new date of the material
	Output: - 1 , if the update was successfully
			- 0, otherwise
*/
int checkValability(MaterialRepo* repo, Material* m);
/*
	checks if a material is not past it's expiration date
	Input: - a pointer to an array of type MaterialRepo
		   - a pointer to an object of type Material
	Output: - 1, if the material is still edible
			- 0 , otherwise
*/
int returnIndexOfAMaterial(MaterialRepo * repo, Material* m);
/*
	returns the index of a certain material in the array
	Input: - a pointer to an array of type MaterialRepo
		   - a pointer to an object of type Material
	Output: - -1, if the material is not in the list
			- any other integer, otherwise
*/
MaterialRepo* emptyTheRepository(MaterialRepo* repo);
/*
	will empty the array of pointers containing the object, without deleting the objects
	Input: - a pointer to an array of type MaterialRepo
	Output: - nothing
*/