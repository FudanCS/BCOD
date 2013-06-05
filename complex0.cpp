#include <iostream>
#include "complex0.h"

complex::complex()
{
	this->real = 1.0f;
	this->imaginary = 1.0f;
}

complex::complex(double r, double i)
{
	this->real = r;
	this->imaginary = i;
}

complex complex::operator ~ () const
{
	complex temp;
	temp.real = this->real;
	temp.imaginary = -(this->imaginary);
	return temp;
}

bool complex::operator == (const complex & t)const
{
	return (real == t.real) && (imaginary == t.imaginary);
}

complex complex::operator + (const complex & t) const
{
	complex temp;
	temp.real = this->real + t.real;
	temp.imaginary = this->imaginary + t.imaginary;
	return temp;
}

complex complex::operator - (const complex & t) const
{
	complex temp;
	temp.real = this->real - t.real;
	temp.imaginary = this->imaginary - t.imaginary;
	return temp;
}

complex complex::operator * (const complex & t) const
{
	complex temp;
	temp.real = this->real * t.real - this->imaginary * t.imaginary;
	temp.imaginary = this->real * t.imaginary + this->imaginary * t.real;
	return temp;
}

complex complex::operator * (double r) const
{
	complex temp;
	temp.real = r * this->real;
	temp.imaginary = r * this->imaginary;
	return temp;
}

complex operator * (double m, complex t)
{
	complex temp;
	temp.real = m * (t.real);
	temp.imaginary = m * (t.imaginary);
	return temp;
}

std::ostream & operator << (std::ostream & os, const complex t)
{
	os << "(" << t.real << ", " << t.imaginary << "i)";
	return os;
}

std::istream & operator >> (std::istream & is, complex & t)
{
	double r;
	double i;
	is >> t.real;
	is >> t.imaginary;
	return is;
}

