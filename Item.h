#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <iostream>
#include "complex0.h"

//every element in the square
//four attributes:
//IsPositive : +/-
//IsConjugate: *
//Content: Z
//serial number: 1, 2, 3....
class Item
{
private:

	bool IsPositive;
	bool IsConjugate;
	std::string content;
	int serialNumber;
	complex value;

public:

	//Set to Unknown by default
	Item()
	{
		IsPositive = true;
		IsConjugate = false;
		content = "UNK";
		serialNumber = -1; //When serialNumber = -1, the show function will ignore it because it is an unknown and will appear as ?
	}

	Item(bool IsPositive, bool IsConjugate, std::string content, int serialNumber)
	{
		this->IsPositive = IsPositive;
		this->IsConjugate = IsConjugate;
		this->content = content;
		this->serialNumber = serialNumber;
	}

	~Item(){}

	bool IsZero()
	{
		return serialNumber == 0;
	}

	bool IsUNK()
	{
		return serialNumber == -1;
	}

	void MultiplyMinusOne()
	{
		if(!IsZero() && !IsUNK())
		{
			if(IsPositive)
				IsPositive = false;
			else
				IsPositive = true;
		}
	}

	std::string toString()
	{
		//for formatted output purposes only
		std::string positiveFlag = " ";
		std::string conjugateFlag = " ";
		std::string number = " ";
		std::string blank = " ";
		std::string lastblank = " ";

		//If is negative, - will be shown
		if(!IsPositive)
			positiveFlag = "-";

		//If is conjugate, * will be shown
		if(IsConjugate)
			conjugateFlag = "*";

		//If is valid
		if(serialNumber >= 0 && serialNumber < 10)
			number  = std::to_string(serialNumber);
		else if(serialNumber >= 10 && serialNumber < 100)
		{
			number  = std::to_string(serialNumber);
			blank = "";
			lastblank = " ";
		}
		else if(serialNumber >= 100)
		{
			number = std::to_string(serialNumber);
			blank = "";
			lastblank = "";
		}
		else
		{
			positiveFlag = "";
			conjugateFlag = " ";  //leave a space
			number = "";
		}

		//For example(-Z2*)                -            Z        2           *
		std::string output = blank + positiveFlag + content + number + conjugateFlag + lastblank;

		return output;
	}

	void SetValue(complex c)
	{
		value = c;
	}

	complex GetValue()
	{
		return value;
	}

	//Getters and Setters
	inline bool GetIsPositive() const { return IsPositive; }
	inline void SetIsPositive(bool val) { IsPositive = val; }
	inline bool GetIsConjugate() const { return IsConjugate; }
	inline void SetIsConjugate(bool val) { IsConjugate = val; }
	inline std::string GetContent() const { return content; }
	inline void SetContent(std::string val) { content = val; }
	inline int GetSerialNumber() const { return serialNumber; }
	inline void SetSerialNumber(int val) { serialNumber = val; }
};

#endif