#ifndef BCOD_H_
#define BCOD_H_

#include <iostream>
#include <ostream>
#include <vector>
#include <fstream>
#include "Item.h"

class BCOD
{
private:

	int m;  // 2^m * 2m
	int N;  //Max number of the already full loaded variable
	int k;  //Max number that is already handled
	Item ItemSquare[1050][1050];   //that is to say m must not be greater than 10, this can be edited
	std::vector<int> filledKey;  //store the k that is already used
	int rowWarden;    //the maximum row the current square has
	int crossWarden;  //the maximum cross the current square has
	//e.g. if a[3][2], rowWarden = 3, crossWarden = 2
	std::ofstream outfile;  //write the result to file

	//return true if candidateN is not in vector<int> filledKey
	bool isNotInFilledKey(int /*candidateN*/);

public:

	BCOD(int /*scale*/);
	~BCOD();

	void InitializeZoneA();
	void InitializeZoneB();
	void InitializeZoneC();
	void InitializeZoneD();

	void RowExchange(int /*rowA*/, int /*rowB*/);
	void CrossExchange(int /*crossA*/, int /*crossB*/);

	bool FindElementInRow_Conjugate(int /*rowX*/, int /*elementSerialNumber*/);
	bool FindElementInRow_InConjugate(int /*rowX*/, int /*elementSerialNumber*/);
	bool FindElementInRow_NotConjugateSensitive(int /*rowX*/, int /*elementSerialNumber*/);
	bool FindElementInCross_Conjugate(int /*crossX*/, int /*elementSerialNumber*/);
	bool FindElementInCross_InConjugate(int /*crossX*/, int /*elementSerialNumber*/);
	bool FindElementInCross_NotConjugateSensitive(int /*crossX*/, int /*elementSerialNumber*/);

	int FindRowNoInCross_NotConjugateSensitive(int /*crossX*/, int /*elementSerialNumber*/);

	void MultiplyRow(int /*rowX*/, int /*times*/);
	void MultiplyCross(int /*crossX*/, int /*times*/);

	//Fill every cross if the cross does not contain Z(n)
	//Z(n) is filled in left and Z(n)* is filled in right
	void FillEveryCrossWithN();
	void HandleDiagElement();

	void FillZoneA(); //Used in the last step
	void FillZoneB(); //Used in the last step
	void FillZoneC(); //Used in the last step
	void FillZoneD(); //Used in the last step

	//Update next filling number, for example, z1 -> z2 -> z3 -> z4 -> z6 -> z5, return the next filling number
	void UpdateNextFillingNumber();
	int SearchNextFillingNumber();
	//Return the current k (max number)
	int UpdateK();
	//Push the filledKey to the filledKey List
	void UpdateFilledKey();
	//Return the size of filledKey
	int FilledKeySize();

	void show();  //show the square in console
	void write(); //write the square to file
	//void printFilledKey(); //print all the N that are used
	void customWrite(std::string str);  //User can define customOutput

	//return true if ItemSquare is orthogonal
	bool isOrthogonal();

};

#endif