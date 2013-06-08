#include <cstdlib>
#include "BCOD.h"
#include "complex0.h"

BCOD::BCOD(int m)
{
	if(m <= 0 || m >= 10)
	{
		//Currently we support only 1 - 10 because of the memory limit
		//Or can we find a way to increase m ?
		std::cout << "Invalid m received." << std::endl;
		std::cout << "0 < m < 10 is accepted." << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Invalid m received." << std::endl;
		outfile << "0 < m < 10 is accepted." << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	this->m = m;
	N = 1;
	filledKey.push_back(this->N);

	Item defaultItem;
	//Item defaultItem2(false, true, "Z", 2);
	//Initialize the overall a[10000][10000] to default(unknown)
	for(int i = 0; i < 1050; i++)
		for(int j = 0; j < 1050; j++)
			ItemSquare[i][j] = defaultItem;

	crossWarden = 2 * m;
	rowWarden = 2 * m;

 	InitializeZoneA();
 	InitializeZoneB();
 	InitializeZoneC();
 	InitializeZoneD();

	//Initialize the output file
	outfile.open("output.txt");
}

BCOD::~BCOD()
{
	outfile.close();
}

void BCOD::InitializeZoneA()
{
	for(int i = 0; i < crossWarden / 2; i++)
	{
		for(int j = 0; j < rowWarden / 2; j++)
		{
			if(i == j)
				ItemSquare[i][j] = Item(true, false, "Z", N);  //Z(n)
			else
				ItemSquare[i][j] = Item(true, false, " ", 0); //Zero
		}
	}
}

void BCOD::InitializeZoneB()
{
	//Auxiliary square
	Item aux[20][20];
	int auxRowWarden = m;
	int auxCrossWarden = m;

	for(int i = 0; i < m; i++)
	{
		aux[i][i] = Item(true, false, " ", 0);
	}

	int tempN = N + 1;
	for(int i = 0; i < m; i++)
	{
		for(int j = i + 1; j < m; j++)
		{
			aux[i][j] = Item(true, false, "Z", tempN);
			aux[j][i] = Item(false, false, "Z", tempN);
			tempN++;
		}
	}

	for(int i = 0; i < rowWarden / 2; i++)
	{
		for(int j = crossWarden / 2; j < crossWarden; j++)
		{
			ItemSquare[i][j] = aux[i][j - m];
		}
	}

}

void BCOD::InitializeZoneC()
{
	//Must first Initialize ZoneB
	for(int i = rowWarden / 2; i < rowWarden; i++)
	{
		for(int j = 0; j < rowWarden / 2; j++)
		{
			Item tempItem = ItemSquare[i - m][j + m];

			//0 cannot have 0*
			if(!tempItem.IsZero())
				tempItem.SetIsConjugate(true);
			
			ItemSquare[i][j] = tempItem;
		}
	}
}

void BCOD::InitializeZoneD()
{
	for(int i = crossWarden / 2; i < crossWarden; i++)
	{
		for(int j = rowWarden / 2; j < rowWarden; j++)
		{
			if(i == j)
				ItemSquare[i][j] = Item(true, true, "Z", N);  //Z(n)*
			else
				ItemSquare[i][j] = Item(true, false, " ", 0);     //Zero
		}
	}
}

void BCOD::RowExchange(int rowX, int rowY)
{
	if(rowX < 0 || rowX > rowWarden)
	{
		std::cout << "rowX should be 0 < rowX < " << rowWarden << std::endl;
		std::cout << "Unexpected rowX : " << rowX << " received." << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "rowX should be 0 < rowX < " << rowWarden << std::endl;
		outfile << "Unexpected rowX : " << rowX << " received." << std::endl;
		outfile << "Program Terminated." << std::endl;

		exit(0);
	}

	if(rowY < 0 || rowY > rowWarden)
	{
		std::cout << "rowY should be 0 < rowY < " << rowWarden << std::endl;
		std::cout << "Unexpected rowY : " << rowY << " received." << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "rowX should be 0 < rowY < " << rowWarden << std::endl;
		outfile << "Unexpected rowY : " << rowY << " received." << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	Item tempRow[30];

	//Store rowX
	for(int i = 0; i < crossWarden; i++)
		tempRow[i] = ItemSquare[rowX][i];

	//rowX replaced by rowY
	for(int i = 0; i < crossWarden; i++)
		ItemSquare[rowX][i] = ItemSquare[rowY][i];

	//rowY replaced by rowX
	for(int i = 0; i < crossWarden; i++)
		ItemSquare[rowY][i] = tempRow[i];
}

void BCOD::CrossExchange(int crossX, int crossY)
{
	if(crossX < 0 || crossX > crossWarden)
	{
		std::cout << "crossX should be 0 < crossX < " << crossWarden << std::endl;
		std::cout << "Unexpected crossX : " << crossX << " received." << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "crossX should be 0 < crossX < " << crossWarden << std::endl;
		outfile << "Unexpected crossX : " << crossX << " received." << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	if(crossY < 0 || crossY > crossWarden)
	{
		std::cout << "crossY should be 0 < crossY < " << crossWarden << std::endl;
		std::cout << "Unexpected crossY : " << crossY << " received." << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "crossY should be 0 < crossY < " << crossWarden << std::endl;
		outfile << "Unexpected crossY : " << crossY << " received." << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	Item tempCross[1500];

	//Store crossX
	for(int i = 0; i < rowWarden; i++)
		tempCross[i] = ItemSquare[i][crossX];

	//crossX replaced by crossY
	for(int i = 0; i < rowWarden; i++)
		ItemSquare[i][crossX] = ItemSquare[i][crossY];

	//crossY replaced by crossX
	for(int i = 0; i < rowWarden; i++)
		ItemSquare[i][crossY] = tempCross[i];
}

bool BCOD::FindElementInRow_Conjugate(int rowX, int elementSerialNumber)
{
	if(rowX < 0 || rowX > rowWarden)
	{
		std::cout << "Illegal Argument rowX : " << rowX << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument rowX : " << rowX << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	if(elementSerialNumber <= 0)
	{
		std::cout << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	//Set to false by default
	bool result = false;
	for(int i = 0; i < crossWarden; i++)
	{
		if(ItemSquare[rowX][i].GetSerialNumber() == elementSerialNumber && ItemSquare[rowX][i].GetIsConjugate() == true)
		{
			result = true;
			break;
		}
	}

	return result;
}

bool BCOD::FindElementInRow_InConjugate(int rowX, int elementSerialNumber)
{
	if(rowX < 0 || rowX > rowWarden)
	{
		std::cout << "Illegal Argument rowX : " << rowX << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument rowX : " << rowX << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	if(elementSerialNumber <= 0)
	{
		std::cout << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	//Set to false by default
	bool result = false;
	for(int i = 0; i < crossWarden; i++)
	{
		if(ItemSquare[rowX][i].GetSerialNumber() == elementSerialNumber && ItemSquare[rowX][i].GetIsConjugate() == false)
		{
			result = true;
			break;
		}
	}

	return result;
}

bool BCOD::FindElementInRow_NotConjugateSensitive(int rowX, int elementSerialNumber)
{
	if(rowX < 0 || rowX > rowWarden)
	{
		std::cout << "Illegal Argument rowX : " << rowX << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument rowX : " << rowX << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	if(elementSerialNumber <= 0)
	{
		std::cout << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	//Set to false by default
	bool result = false;
	for(int i = 0; i < crossWarden; i++)
	{
		if(ItemSquare[rowX][i].GetSerialNumber() == elementSerialNumber)
		{
			result = true;
			break;
		}
	}

	return result;
}

bool BCOD::FindElementInCross_Conjugate(int crossX, int elementSerialNumber)
{
	if(crossX < 0 || crossX > crossWarden)
	{
		std::cout << "Illegal Argument crossX : " << crossX << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
        outfile << "Illegal Argument crossX : " << crossX << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	if(elementSerialNumber <= 0)
	{
		std::cout << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	//Set to false by default
	bool result = false;
	for(int i = 0; i < rowWarden; i++)
	{
		if(ItemSquare[i][crossX].GetSerialNumber() == elementSerialNumber && ItemSquare[i][crossX].GetIsConjugate() == true)
		{
			result = true;
			break;
		}
	}

	return result;
}

bool BCOD::FindElementInCross_InConjugate(int crossX, int elementSerialNumber)
{
	if(crossX < 0 || crossX > crossWarden)
	{
		std::cout << "Illegal Argument crossX : " << crossX << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
        outfile << "Illegal Argument crossX : " << crossX << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	if(elementSerialNumber <= 0)
	{
		std::cout << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	//Set to false by default
	bool result = false;
	for(int i = 0; i < rowWarden; i++)
	{
		if(ItemSquare[i][crossX].GetSerialNumber() == elementSerialNumber && ItemSquare[i][crossX].GetIsConjugate() == false)
		{
			result = true;
			break;
		}
	}

	return result;
}

bool BCOD::FindElementInCross_NotConjugateSensitive(int crossX, int elementSerialNumber)
{
	if(crossX < 0 || crossX > crossWarden)
	{
		std::cout << "Illegal Argument crossX : " << crossX << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
        outfile << "Illegal Argument crossX : " << crossX << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	if(elementSerialNumber <= 0)
	{
		std::cout << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	//Set to false by default
	bool result = false;
	for(int i = 0; i < rowWarden; i++)
	{
		if(ItemSquare[i][crossX].GetSerialNumber() == elementSerialNumber)
		{
			result = true;
			break;
		}
	}

	return result;
}

int BCOD::FindRowNoInCross_NotConjugateSensitive(int crossX, int elementSerialNumber)
{
	if(crossX < 0 || crossX > crossWarden)
	{
		std::cout << "Illegal Argument crossX : " << crossX << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
        outfile << "Illegal Argument crossX : " << crossX << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	if(elementSerialNumber <= 0)
	{
		std::cout << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument elementSerialNumber : " << elementSerialNumber << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	int result = -1;
	for(int i = 0; i < rowWarden; i++)
	{
		if(ItemSquare[i][crossX].GetSerialNumber() == elementSerialNumber)
		{
			result = i;
			break;
		}
	}

	return result + 1;
}

void BCOD::MultiplyRow(int rowX, int times)
{
	if(rowX < 0 || rowX > rowWarden)
	{
		std::cout << "Illegal Argument rowX : " << rowX << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "Illegal Argument rowX : " << rowX << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	for(int i = 0; i < crossWarden; i++)
	{
		Item tempItem = ItemSquare[rowX][i];
		tempItem.MultiplyMinusOne();
		ItemSquare[rowX][i] = tempItem;
	}
}

void BCOD::MultiplyCross(int crossX, int times)
{
	if(crossX < 0 || crossX > crossWarden)
	{
		std::cout << "Illegal Argument crossX : " << crossX << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
        outfile << "Illegal Argument crossX : " << crossX << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	for(int i = 0; i < rowWarden; i++)
	{
		Item tempItem = ItemSquare[i][crossX];
		tempItem.SetSerialNumber(tempItem.GetSerialNumber() * times);
		ItemSquare[i][crossX] = tempItem;
	}
}

void BCOD::FillEveryCrossWithN()
{
	for(int i = 0; i < crossWarden; i++)
	if(!FindElementInCross_NotConjugateSensitive(i, N))
	{
		//Insert Z(n) in left
		if(i < crossWarden / 2)
		{
			ItemSquare[rowWarden][i] = Item(true, false, "Z", N);
			rowWarden++;
		}
		else
		{
			ItemSquare[rowWarden][i] = Item(true, true, "Z", N);
			rowWarden++;
		}
	}
}

void BCOD::HandleDiagElement()
{
	for(int i = 0; i < 2 * m; i++)
	{
		if(!ItemSquare[i][i].IsUNK() && !ItemSquare[i][i].IsZero() && !ItemSquare[i][i].GetIsPositive())
			MultiplyRow(i, -1);
	}
}

void BCOD::FillZoneA()
{
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < m; j++)
		{
			//Set the element to Zero
			if(i != j)
				ItemSquare[i][j] = Item(true, false, " ", 0);
		}
	}
}

void BCOD::FillZoneB()
{
	//By default every element is UNK
	Item tempSquare[20][20];
	//A vector that is used to store the UNK a[i][j]
	std::vector<Item*> UNKList;
	//An array that stores whether the serialNumber is used.
	bool usedNumber[2000];

	//set usedNumber to false by default
	for(int i = 0; i < 2000; i++)
		usedNumber[i] = false;

	//Copy the section B to the tempSquare
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < m; j++)
		{
			tempSquare[i][j] = ItemSquare[i][j + m];
		}
	}

	//Set Zero 
	for(int i = 0; i < m; i++)
		tempSquare[i][i] = Item(true, false, " ", 0);

	//Fill the square if we can calculate the reflection
	//search the section B
	//if we cannot calculate, we store it in an array
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < i; j++)
		{
			if(j != i)
			{
				if(tempSquare[i][j].IsUNK() && !tempSquare[j][i].IsUNK())
				{
					//if ItemSquare[j][i] is not UNK and is not Zero, we can fill it
					//or we must store it for later filling
					//a[j][i] = -a[i][j]
					Item item = tempSquare[j][i];
					item.SetIsPositive(!item.GetIsPositive());
					tempSquare[i][j] = item;
// 					//If a[j][i] still unknown
// 					else//(tempSquare[j][i].IsUNK())
// 					{
// 						//Store the two
// 						Item * a = &tempSquare[i][j];
// 						Item * b = &tempSquare[j][i];
// 						UNKList.push_back(a);					
// 						UNKList.push_back(b);
// 					}
				}
				else if(!tempSquare[i][j].IsUNK() && tempSquare[j][i].IsUNK())
				{
					Item item = tempSquare[i][j];
					item.SetIsPositive(!item.GetIsPositive());
					tempSquare[j][i] = item;
				}
				else if(tempSquare[i][j].IsUNK() && tempSquare[j][i].IsUNK())
				{
					//Store the two
					Item * a = &tempSquare[i][j];
					Item * b = &tempSquare[j][i];
					UNKList.push_back(a);					
					UNKList.push_back(b);
				}
				else{} //else do nothing
			}
		}
	}

	//Search the used number in the whole right part
	//if the number is used, we store it in the usedNumber Array
	for(int i = crossWarden / 2; i < crossWarden; i++)
	{
		for(int j = 0; j < rowWarden; j++)
		{
			if(!ItemSquare[j][i].IsUNK() && !ItemSquare[j][i].IsZero() && ItemSquare[j][i].GetSerialNumber() > 0 && !ItemSquare[j][i].GetIsConjugate())
				usedNumber[ItemSquare[j][i].GetSerialNumber() - 1] = true;  //Actually we decode usedNumber[i] to i + 1
		}
	}

	usedNumber[ItemSquare[m][m].GetSerialNumber() - 1] = true;

	//Finally we fill the unknown a[i][j]
	for(std::vector<Item*>::iterator iter = UNKList.begin(); iter != UNKList.end(); iter += 2) //We store two at the same time
	{
		for(int i = 0; i < 2000; i++)
		{
			//If not used
			if(usedNumber[i] == false)
			{
				(*iter)->SetIsPositive(false);// Item(false, false, "Z", i + 1);
				(*iter)->SetIsConjugate(false);
				(*iter)->SetContent("Z");
				(*iter)->SetSerialNumber(i + 1);
				(*(iter + 1))->SetIsPositive(true);// Item(true, false, "Z", i + 1);
				(*(iter + 1))->SetIsConjugate(false);
				(*(iter + 1))->SetContent("Z");
				(*(iter + 1))->SetSerialNumber(i + 1);
				//Set the flag to used
				usedNumber[i] = true;
				break;
			}
		}
	}

	//Last step, we write the tempSquare back to the ItemSquare
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < m; j++)
		{
			ItemSquare[i][j + m] = tempSquare[i][j];
		}
	}
}

void BCOD::FillZoneC()
{
	for(int i = 0; i < m; i++)
	{
		for(int j = m; j < 2 * m; j++)
		{
			Item item;
			item = ItemSquare[i][j];
			if(!item.IsZero())
				item.SetIsConjugate(true);

			ItemSquare[i + m][j - m] = item;
		}
	}
}

void BCOD::FillZoneD()
{
	for(int i = m; i < 2 * m; i++)
	{
		for(int j = m; j < 2 * m; j++)
		{
			//Set the element to Zero
			if(i != j)
				ItemSquare[i][j] = Item(true, false, " ", 0);
		}
	}
}

int BCOD::SearchNextFillingNumber()
{
	int candidateN = -1;

	for(int i = 0; i < m; i++)
	{
		for(int j = m; j < crossWarden; j++)
		{
			Item item = ItemSquare[i][j];
			if(!item.IsUNK() && !item.IsZero() && isNotInFilledKey(item.GetSerialNumber()) && item.GetSerialNumber() < candidateN)
				candidateN = item.GetSerialNumber();
		}
	}

	if(candidateN <= 0)
	{
		std::cout << "An error occurred." << std::endl;
		std::cout << "Cannot find next N. Not Expected." << std::endl;
		std::cout << "Program Terminated." << std::endl;
		//Write to log
		outfile << "An error occurred." << std::endl;
		outfile << "Cannot find next N. Not Expected." << std::endl;
		outfile << "Program Terminated." << std::endl;
		exit(0);
	}

	//N = candidateN;

	return candidateN;
}

void BCOD::UpdateNextFillingNumber()
{
	N = SearchNextFillingNumber();
}

int BCOD::UpdateK()
{
	int maxkey = -1;

	for(int i = 0; i < rowWarden; i++)
	{
		for(int j = 0; j < crossWarden; j++)
		{
			Item item = ItemSquare[i][j];
			if(!item.IsUNK() && !item.IsZero() && item.GetSerialNumber() > maxkey)
				maxkey = item.GetSerialNumber();
		}
	}

	return maxkey;
}

void BCOD::UpdateFilledKey()
{
	filledKey.push_back(N);
}

void BCOD::show()
{
	std::cout << "    ";
	for(int i = 0; i < crossWarden; i++)
		if(i + 1 < 10)
		    std::cout << i + 1 << "      ";
		else
			std::cout << i + 1 << "     ";
	std::cout << std::endl;

	for(int i = 0; i < rowWarden; i++)
	{
		if(i + 1 < 10)
		    std::cout << i + 1<< "   ";
		else
			std::cout << i + 1 << "  ";
		for(int j = 0; j < crossWarden; j++)
		{
			std::cout << ItemSquare[i][j].toString();
			std::cout << "  ";
		}
		std::cout << std::endl;
	}
}

void BCOD::write()
{
	outfile << "      ";
	for(int i = 0; i < crossWarden; i++)
	{
		if(i + 1 < 10)
			outfile << i + 1 << "       ";
		else if(i + 1 >= 10 && i + 1 < 100)
			outfile << i + 1 << "      ";
		else
			outfile << i + 1 << "     ";
	}
	outfile << std::endl;

	for(int i = 0; i < rowWarden; i++)
	{
		if(i + 1 < 10)
			outfile << i + 1<< "    ";
		else if(i + 1 >= 10 && i + 1 < 100)
			outfile << i + 1 << "   ";
		else
			outfile << i + 1 << "  ";
		for(int j = 0; j < crossWarden; j++)
		{
			outfile << ItemSquare[i][j].toString();
			outfile << "  ";
		}
		outfile << std::endl;
	}

	outfile << "---------------------------------------------------------------------------------------------" << std::endl;
	outfile << "N = " << this->N << "    k = " << UpdateK() << std::endl;
	outfile << "The filledKey List is : " << std::endl;
	for(std::vector<int>::iterator iter = filledKey.begin(); iter != filledKey.end(); iter++)
		outfile << " " << *iter;
	outfile << std::endl;
	outfile << "---------------------------------------------------------------------------------------------" << std::endl;
}

void BCOD::customWrite(std::string str)
{
	outfile << "---------------------------------------------------------------------------------------------" << std::endl;
	outfile << str << std::endl;
	outfile << "---------------------------------------------------------------------------------------------" << std::endl;
}

bool BCOD::isNotInFilledKey(int candidateN)
{
	bool isValidCandidateN = true;

	if(filledKey.size() == 0)
		return isValidCandidateN;

	for(std::vector<int>::iterator iter = filledKey.begin(); iter != filledKey.end(); iter++)
	{
		if(candidateN == *iter)
		{
			isValidCandidateN = false;
			break;
		}
	}

	return isValidCandidateN;
}

int BCOD::FilledKeySize()
{
	return filledKey.size();
}

bool BCOD::isOrthogonal()
{
	//Assign value
	for(int i = 0; i < rowWarden; i++)
	{
		for(int j = 0; j < crossWarden; j++)
		{
			if(!ItemSquare[i][j].IsUNK() && !ItemSquare[i][j].IsZero())
			{
				if(!ItemSquare[i][j].GetIsConjugate())
				{
					if(ItemSquare[i][j].GetIsPositive())
					{
						double real = ItemSquare[i][j].GetSerialNumber();
						double imaginary = 2.0f;
						complex c(real, imaginary);
						ItemSquare[i][j].SetValue(c);
					}
					else
					{
						double real = ItemSquare[i][j].GetSerialNumber();
						double imaginary = 2.0f;
						complex c(-real, -imaginary);
						ItemSquare[i][j].SetValue(c);
					}

				}
				else
				{
					if(ItemSquare[i][j].GetIsPositive())
					{
						double real = ItemSquare[i][j].GetSerialNumber();
						double imaginary = -2.0f;
						complex c(real, imaginary);
						ItemSquare[i][j].SetValue(c);
					}
					else
					{
						double real = ItemSquare[i][j].GetSerialNumber();
						double imaginary = -2.0f;
						complex c(-real, -imaginary);
						ItemSquare[i][j].SetValue(c);
					}

				}

			}
			else if(ItemSquare[i][j].IsZero())
			{
				complex c(0, 0);
				ItemSquare[i][j].SetValue(c);
			}
		}
	}

	bool isOrthogonal = true;
	//Matrix Multiply
	for(int i = 0; i < crossWarden; i++)
	{
		for(int k = i + 1; k < crossWarden; k++)
		{
			complex total(0, 0);
			for(int j = 0; j < rowWarden; j++)
			{
				complex temp = ~(ItemSquare[j][i].GetValue()) * (ItemSquare[j][k].GetValue());
				total = total + temp;
			}

			complex criteria(0, 0);
			if(!(total == criteria))
			{
				isOrthogonal = false;
				return isOrthogonal;
			}
		}
	}

	return isOrthogonal;

}