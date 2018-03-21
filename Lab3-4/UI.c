#include "UI.h"
#include <stdio.h>
#include <conio.h>
#include <crtdbg.h>

UI* createUI(Controller* c)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->controller = c;
	return ui;
}

void destroyUI(UI* ui)
{
	destroyController(ui->controller);
	free(ui);
	ui = NULL;
}

void printMenu()
{
	printf("\n****************************************\n");
	printf("1 - Add a new material. \n");
	printf("2 - Update a material. \n");
	printf("3 - Delete a material. \n");
	printf("4 - List all materials with specifications. \n");
	printf("5 - List all materials containing a given string and past their expiration date.\n");
	printf("6 - See the available materials containing a given string, decending by supplier.\n");
	printf("7 - All materials from a given supplier, which are in short supply.\n");
	printf("8 - Undo last command.\n");
	printf("9 - Redo previous command.\n");
	printf("10- For a given supplier, see all materials, sorted ascending by expiration month.\n");
	printf("0 - to exit. \n");
	printf("****************************************\n");

}

int validCommand(int command)
{
	if (command >= 0 && command <= 10)
		return 1;
	return 0;
}

int validDate(ExpDate date)
{
	if (date.day < 1 || date.day > 31)
		return 0;
	if (date.month < 1 || date.month > 12)
		return 0;
	if (date.year < 1900)
		return 0;
	if ((int)(date.day) != date.day || (int)(date.month) != date.month || (int)(date.year) != date.year)
		return 0;
	return 1;
	
}

int readCommand(const char* command)
{
	char string[16];
	int result = 0, flag = 0, r = 0;

	while (flag == 0)
	{
		printf(command);
		scanf("%s", string);

		r = sscanf(string, "%d", &result);
		flag = (r == 1);
		if (flag == 0)
			printf("Error at reading the command!\n");

	}
	return result;
}

int addMaterialUI(UI* ui, Material* m)
{
	
	return addMaterial(ui->controller, m->name, m->supplier, m->quantity, m->date);
}

int deleteMaterialUI(UI* ui, UndoRepo* undo)
{
	char name[50];
	ExpDate d; d.day = 0; d.month = 0; d.year = 0;
	UndoType* obj;
	printf("What material would you like to delete? :");
	scanf("%s", name);
	int result = delete(ui->controller, name);
	obj = createUndoType(2, NULL, name, "", 0, d);
	if(result == 1)
		addToUndo(undo,obj);
	return result;
}

int updateMaterial(UI* ui, MaterialRepo* undo)
{
	char name[50], supplier[100];
	double quantity = 0;
	ExpDate date;
	int result = -1;
	UndoType* obj;

	printf("1 - for updating the name\n");
	printf("2 - for updating the supplier\n");
	printf("3 - for updating the quantity\n");
	printf("4 - for updating the expiration date\n");

	int selection;
	scanf("%d", &selection);
	if (selection >= 1 && selection <= 4)
	{
		switch (selection)
		{
		case 1:
		{
			printf("Input the name of the material: ");
			//scanf("%s", &name);
			getchar();
			gets(name);
			printf("Input the new name: ");
			char newN[50];
			gets(newN);
			//scanf("%s", newN);
			result = updateTheName(ui->controller, name, newN);
			ExpDate d; d.day = 0; d.month = 0; d.year = 0;
			obj = createUndoType( 3, NULL, name,newN, 0, d);
			if (result == 1)
				addToUndo(undo, obj);
			break;
		}
		case 2:
		{
			printf("Input the name of the material: ");
			//scanf("%s", &name);
			getchar();
			gets(name);
			printf("Input the new supplier: ");
			char newN[50];
			//scanf("%s", newN);
			gets(newN);
			result = updateTheSupplier(ui->controller, name, newN);
			ExpDate d; d.day = 0; d.month = 0; d.year = 0;
			obj = createUndoType(4, NULL, name, newN, 0, d);
			if (result == 1)
				addToUndo(undo, obj);
			break;
		}
		case 3:
		{
			printf("Input the name of the material: ");
			//scanf("%s", &name);
			getchar();
			gets(name);
			printf("Input the new quantity: ");
			scanf("%lf", &quantity);
			if (quantity < 0)
				break;
			result = updateTheQuantity(ui->controller, name, quantity);
			ExpDate d; d.day = 0; d.month = 0; d.year = 0;
			obj = createUndoType(5, NULL, name, "", quantity, d);
			if (result == 1)
				addToUndo(undo, obj);
			break;
		}
		case 4:
		{
			printf("Input the name of the material: ");
			//scanf("%s", &name);
			getchar();
			gets(name);
			printf("Input the expiration date:\n Day : ");
			scanf("%d", &date.day);
			printf(" Month : ");
			scanf("%d", &date.month);
			printf(" Year : ");
			scanf("%d", &date.year);
			if (validDate(date) == 0)
				break;
			result = updateExpDatectrl(ui->controller,name,date);
			obj = createUndoType(6, NULL, name, "", 0, date);
			if (result == 1)
				addToUndo(undo, obj);
			break;
		}
		}
	}
	else
		printf("Chose from the given commands!\n");
	free(obj);
	obj = NULL;
	return result;
}

void printAllMaterials(UI* ui)
{
	MaterialRepo* repo = getRepo(ui->controller);
	Material* m = NULL;
	int lenght = getLenght(repo);
	printf("%d", lenght);
	if (lenght == 0)
	{
		char* str = "There are no stored materials";
		printf("%s \n", str);
	}
	else
		for (int i = 0; i < getLenght(repo); i++)
		{
			m = getMaterialOnPosition(repo, i);
			printf("%s , supplied by %s, having the quantity of %lf and the expiration date %d-%d-%d\n",
				m->name,m->supplier,m->quantity, m->date.day, m->date.month, m->date.year);
		}
	m = NULL;
	repo = NULL;
}

void printMaterialsContainingAGivenStringAndExpired(UI* ui)
{
	MaterialRepo* repo = getRepo(ui->controller);
	int lenght = getLenght(repo);
	Material* m = NULL;
	if (lenght == 0)
	{
		char* str = "There are no stored materials";
		printf("%s \n", str);
	}
	else
	{
		char string[20];
		printf("Input the wanted string: ");
		getchar();
		gets(string);
		//scanf("%s", string);
		for (int i = 0; i < lenght; i++)
		{
			m = getMaterialOnPosition(repo, i);
			if(strcmp(string, "") == 0)
				if (checkValability(repo, m) == 0)
				{
					printf("%s , supplied by %s, having the quantity of %lf and the expiration date %d-%d-%d\n",
						m->name, m->supplier, m->quantity, m->date.day, m->date.month, m->date.year);
				}
			if (strcmp(string, "") != 0)
			{
				if(checkValability(repo, m) == 0 && strstr(m->name, string) != NULL)
				{
					printf("%s , supplied by %s, having the quantity of %lf and the expiration date %d-%d-%d\n",
						m->name, m->supplier, m->quantity, m->date.day, m->date.month, m->date.year);
				}
			}
		}
	}
	m = NULL;
	repo = NULL;
}

void printMaterialsFromASupplierInShortQuantity(UI* ui)
{
	MaterialRepo* repo = getRepo(ui->controller);
	Material* m = NULL;
	Material *aux = NULL;
	MaterialRepo* sorted = createRepository();
	int lenght = getLenght(repo);
	if (lenght == 0)
	{
		printf("\n!There are no stored materials\n");
	}
	else
	{
		char string[20];
		printf("Input the supplier: ");
		getchar();
		gets(string);
		printf("Input the quantity: ");
		double quantity;
		scanf("%lf", &quantity);
		sorted->lenght = 0;
		for (int i = 0; i < lenght; i++)
		{
			m = getMaterialOnPosition(repo, i);
			if (strcmp(m->supplier, string) == 0 && m->quantity < quantity)
			{
				sorted->materials[sorted->lenght] = m;
				sorted->lenght++;
			}
		}
		if (sorted->lenght < 1)
			printf("\n !No such materials! \n");
		else
		{
			for (int i = 0; i< sorted->lenght; i++)
				for (int j = 0; j < sorted->lenght; j++)
					if (strcmp(sorted->materials[i]->name, sorted->materials[j]->name) >= 0)
					{
						aux = sorted->materials[i];
						sorted->materials[i] = sorted->materials[j];
						sorted->materials[j] = aux;
					}

			for (int i = 0; i < sorted->lenght; i++)
			{
				printf("%s - %s - %lf \n", sorted->materials[i]->name, sorted->materials[i]->supplier, sorted->materials[i]->quantity);
			}
		}

	}
	sorted = NULL;
	printf("\n");
	m = NULL;
	repo = NULL;
	aux = NULL;
}

void printMaterialsFromASupplierAscedingByExpirationMonth(UI* ui)
{
	MaterialRepo* repo = getRepo(ui->controller);
	Material* m = NULL;
	Material *aux = NULL;
	MaterialRepo* sorted = createRepository();
	int lenght = getLenght(repo);
	if (lenght == 0)
	{
		printf("\n!There are no stored materials\n");
	}
	else
	{
		char string[20];
		printf("Input the supplier: ");
		getchar();
		gets(string);
		printf("Input the expiration month: ");
		int month;
		scanf("%d", &month);
		sorted->lenght = 0;

		for (int i = 0; i < lenght; i++)
		{
			m = getMaterialOnPosition(repo, i);
			if (strcmp(m->supplier, string) == 0 && (m->date.month <= month))
			{
				sorted->materials[sorted->lenght] = m;
				sorted->lenght++;
			}
		}
		if (sorted->lenght < 1)
			printf("\n !No such materials! \n");
		else
		{
			for (int i = 0; i < sorted->lenght; i++)
				for (int j = 0; j < sorted->lenght; j++)
					if (sorted->materials[i]->date.month <= sorted->materials[j]->date.month)
					{
						aux = sorted->materials[i];
						sorted->materials[i] = sorted->materials[j];
						sorted->materials[j] = aux;
					}

			for (int i = 0; i < sorted->lenght; i++)
			{
				printf("%s - %s - Day:%d, Month:%d, Year:%d \n", sorted->materials[i]->name, sorted->materials[i]->supplier, sorted->materials[i]->date.day, sorted->materials[i]->date.month, sorted->materials[i]->date.year);
			}
		}

	}
	sorted = NULL;
	printf("\n");
	m = NULL;
	repo = NULL;
	aux = NULL;
}

void printMaterialsContainingAGivenStringDecending(UI* ui)
{
	MaterialRepo* repo = getRepo(ui->controller);
	Material* m = NULL;
	Material* aux = NULL;
	MaterialRepo* sorted = createRepository();
	int lenght = getLenght(repo);;
	if (lenght == 0)
	{
		printf("\n!There are no stored materials!\n");
	}
	else
	{
		char string[20];
		printf("Input the wanted string: ");
		//scanf("%s", string);
		getchar();
		gets(string);
		sorted->lenght = 0;
		for (int i = 0; i < lenght; i++)
		{
			m = getMaterialOnPosition(repo, i);;
			if (strcmp(string,"") == 0)
			{
				sorted->materials[sorted->lenght] = m;
				sorted->lenght++;
			}
			if (strcmp(string, "") != 0)
				if (strstr(m->name, string) != NULL)
				{
					sorted->materials[sorted->lenght] = m;
					sorted->lenght++;
				}

		}
		if (sorted->lenght < 1)
			printf("\n !No such materials! \n");
		else
		{
			for (int i = 0; i< sorted->lenght; i++)
				for (int j = 0; j < sorted->lenght; j++)
					if (strcmp(sorted->materials[i]->supplier, sorted->materials[j]->supplier) <= 0)
					{
						aux = sorted->materials[i];
						sorted->materials[i] = sorted->materials[j];
						sorted->materials[j] = aux;
					}

			for (int i = 0; i < sorted->lenght; i++)
			{
				printf("%s - %s \n", sorted->materials[i]->name, sorted->materials[i]->supplier);
			}
		}

	}
	sorted = NULL;
	printf("\n");
	m = NULL;
	repo = NULL;
	aux = NULL;
}

Material* read()
{
	char name[50], supplier[100];
	double quantity = 0;
	ExpDate date;

	printf("Input the name of the material : ");
	getchar();
	gets(name);
	printf("Input the name of the supplier: ");
	gets(supplier);
	printf("Input the quantity: ");
	scanf("%lf", &quantity);
	if (quantity < 0)
		return 0;
	printf("Input the expiration date:\n Day : ");
	scanf("%d", &date.day);
	printf(" Month : ");
	scanf("%d", &date.month);
	printf(" Year : ");
	scanf("%d", &date.year);
	if (validDate(date) == 0)
		return 0;
	return createMaterial(name, supplier, quantity, date);
}

void startUI(UI* ui)
{
	UndoRepo* undo = createUndoRepo();
	while (1)
	{
		system("cls");
		printMenu();
		int command = readCommand("Input command: ");
		while (validCommand(command) == 0)
		{
			printf("Error! Please give a valid input!\n");
			command = readCommand("Input command: ");
		}
		switch (command)
		{
		case 0 :
		{
			_CrtDumpMemoryLeaks();
			exit(0);
		}
		case 1:
		{
			Material* m = read();
			ExpDate d;
			d.day = 0;
			d.month = 0;
			d.year = 0;
			int comm = 1;
			UndoType* obj = createUndoType(comm, m, "","",0, d);
			printf("\n%d\n", obj->nrOfTheCommand);
			int result = addMaterialUI(ui, m);
			if (result == 1)
			{
				printf("Material added successfully!\n");
				addToUndo(undo, obj);
				printf("\n cursor undo: %d and leght undo list: %d\n", returnCursor(undo), undo->lenght);
				system("pause");
				
			}
			
			else
			{
				if (result == 2)
				{
					printf("The material allready exists!\n");
					addToUndo(undo, obj);
					printf("\n cursor undo: %d and leght undo list: %d\n", returnCursor(undo), undo->lenght);
					system("pause");
				}
				else
				{
					printf("Error at adding the material!\n");
					system("pause");
				}
			}
			free(m);
			m = NULL;
			free(obj);
			obj = NULL;
			break;
		}
		case 2:
		{
			int result = updateMaterial(ui, undo);
			if (result == 1)
			{
				printf("Material updated successfully!\n");
				printf("\n cursor undo: %d and leght undo list: %d\n", returnCursor(undo), undo->lenght);
				system("pause");
			}
			else
			{
				printf("Error at updating the material!\n");
				system("pause");
			}
			break;
		}
		case 3:
		{
			int result = deleteMaterialUI(ui, undo);
			if (result == 1)
			{
				printf("Material successfully deleted\n");
				printf("\n cursor undo: %d and leght undo list: %d\n",returnCursor(undo), undo->lenght);
				system("pause");
			}
			else
			{
				printf("The material does not exist\n");
				system("pause");
			}
			break;
		}
		case 4:
		{
			printAllMaterials(ui);
			system("pause");
			break;
		}
		case 5:
		{
			printMaterialsContainingAGivenStringAndExpired(ui);
			system("pause");
			break;
		}
		case 6:
		{
			printMaterialsContainingAGivenStringDecending(ui);
			system("pause");
			break;
		}
		case 7:
		{
			printMaterialsFromASupplierInShortQuantity(ui);
			system("pause");
			break;
		}
		case 8:
		{
			int check = undoCommand(undo);
			
			if (check == 0)
			{
				printf("\nCouldn't perform undo\n");
				system("pause");
			}
			else
			{
				
				int cursor = returnCursor(undo);
				int result = executeAllCommands(undo, cursor + 1, ui->controller);
				if (result == 1)
				{
					printf("\n Undo operation performed successfully\n");
					system("pause");
				}
				else
				{
					printf("\nThere is no command to undo\n");
					system("pause");
				}
			}
			break;
		}
		case 9:
		{
			int check = redoCommand(undo);
			
			if (check == 0)
			{
				printf("\nCouldn't perform redo\n");
				system("pause");
			}
			else
			{
				int cursor = returnCursor(undo) ;
				int result = executeAllCommands(undo, cursor, ui->controller);
				if (result == 1)
				{
					printf("\n Redo operation performed successfully\n");
					system("pause");
				}
				else
				{
					printf("\n No command to redo\n");
					system("pause");
				}
			}
			break;
		}
		case 10:
		{
			printMaterialsFromASupplierAscedingByExpirationMonth(ui);
			system("pause");
			break;
		}
		}
	}
}