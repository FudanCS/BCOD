#ifndef COMPLEX0_H_
#define COMPLEX0_H_

#include <iostream>
#include <istream>
#include <ostream>

class complex
{
private:
	double real;
	double imaginary;

public:
	complex();
	complex(double r, double i);
	complex operator + (const complex & t) const;
	complex operator - (const complex & t) const;
	complex operator * (const complex & t) const;
	complex operator * (double r) const;
	//complex operator / (const complex & t) const;
	complex operator ~ () const;
	bool operator == (const complex & t) const;

	friend complex operator * (double m, complex t);
	friend std::ostream & operator << (std::ostream & os, const complex t);
	friend std::istream & operator >> (std::istream & is, complex & t);

};

#endif