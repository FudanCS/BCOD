#include <iostream>
#include "BCOD.h"
#include "Item.h"

int main(void)
{
	std::cout << "Please input the number m" << std::endl;
	int m;
	std::cin >> m;
 	BCOD * bcod = new BCOD(m);
	bcod->customWrite("Initializing!");
	bcod->write();

	while(bcod->FilledKeySize() != bcod->UpdateK())
	{
		int maxicon = bcod->UpdateK();
		bcod->customWrite("Update the value of K");
		bcod->write();
		int nextFillingNumber = bcod->SearchNextFillingNumber();
		bcod->UpdateNextFillingNumber();
	//	bcod->customWrite("Update Next Filling Number");
	//	bcod->write();

		bcod->FillEveryCrossWithN();
		bcod->customWrite("FillEveryCrossWithN");
		bcod->write();

		for(int i = 0; i < m; i++)
		{
			if(bcod->FindElementInCross_Conjugate(i, nextFillingNumber))
				bcod->CrossExchange(i, i + m);
		}
		bcod->customWrite("Cross Exchange");
		bcod->write();

		for(int i = 0; i < 2 * m; i++)
		{
			if(bcod->FindRowNoInCross_NotConjugateSensitive(i, nextFillingNumber) > 0)
			{
				bcod->RowExchange(bcod->FindRowNoInCross_NotConjugateSensitive(i, nextFillingNumber) - 1, i);
			}
		}
		bcod->customWrite("Row Exchange");
		bcod->write();

		bcod->HandleDiagElement();
	//	bcod->customWrite("Diag * -1");
	//	bcod->write();
		bcod->FillZoneA();
	//	bcod->customWrite("FillZoneA");
	//	bcod->write();
		bcod->FillZoneB();
		bcod->customWrite("FillZoneB");
		bcod->write();
		bcod->FillZoneC();
	//	bcod->customWrite("FillZoneC");
	//	bcod->write();
		bcod->FillZoneD();
	//	bcod->customWrite("FillZoneD");
	//	bcod->write();
		bcod->UpdateFilledKey();
	//	bcod->customWrite("UpdateFilledKey");
	//	bcod->write();
	}
	


	return 0;
}