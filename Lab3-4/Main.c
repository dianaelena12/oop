#include "MaterialRepo.h"
#include "UI.h"
#include "Controller.h"
#include <crtdbg.h>


void addMaterialsOnList(Controller* ctrl)
{
	ExpDate date1, date2, date3, date4, date5, date6, date7, date8, date9, date10;

	date1.day = 12;
	date1.month = 8;
	date1.year = 2020;
	printf("%d",addMaterial(ctrl, "Faina Alba", "Market", 30, date1));

	date2.day = 11;
	date2.month = 1;
	date2.year = 2017;
	addMaterial(ctrl, "Cacao", "Dr.Oetker", 10, date2);

	date3.day = 21;
	date3.month = 12;
	date3.year = 2029;
	addMaterial(ctrl, "Sugar", "Market", 100, date3);

	date4.day = 31;
	date4.month = 4;
	date4.year = 2016;
	addMaterial(ctrl, "Oat", "Market", 5, date4);

	date5.day = 3;
	date5.month = 10;
	date5.year = 1999;
	addMaterial(ctrl, "Cornstarch", "Dr.Oetker", 0.1, date5);

	date6.day = 3;
	date6.month = 6;
	date6.year = 2018;
	addMaterial(ctrl, "Nuts", "Dr.Oetker", 6.5, date6);

	date7.day = 20;
	date7.month = 03;
	date7.year = 2018;
	addMaterial(ctrl, "Bananas", "Jungle", 20, date7);

	date8.day = 6;
	date8.month = 10;
	date8.year = 2020;
	addMaterial(ctrl, "Berries", "Forest", 10, date8);

	date9.day = 12;
	date9.month = 07;
	date9.year = 2025;
	addMaterial(ctrl, "Brown-Sugar", "Dr.Oetker", 0.7, date9);

	date10.day = 30;
	date10.month = 11;
	date10.year = 2019;
	addMaterial(ctrl, "Butter", "Pillos", 10.8, date10);

}


int main()
{
	//testsMaterialRepository();
	
	MaterialRepo* repo = createRepository();
	Controller* ctrl = createController(repo);

	addMaterialsOnList(ctrl);

	UI* ui = createUI(ctrl);
	startUI(ui);

	destroyUI(ui);
	
	_CrtDumpMemoryLeaks();

	system("pause");
	return 0;
}