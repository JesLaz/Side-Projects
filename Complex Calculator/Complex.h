/*
Name: Jessie Lazo
Purpose of Program: Read in a Complex number equation and produce and format result of such
*/
#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include <sstream>
using namespace std;

class Complex {
public:
	Complex();
	Complex(int n);
	Complex(string n);
	Complex(string r, string i);
	Complex(int r, int i, int d);
	int real; //Real Part of a complex number
	int imaginary; //Imaginary Part of a complex number
	int denominator; //Denominator part of a complex number
	string toString() const; //Format [re + imi] / dem
	Complex& operator=(const Complex & c);//Copy Constructor
	bool canSimplify() const;//Determines if Complex number can be simplified
};

Complex operator+(Complex a, Complex b);
Complex operator-(Complex a, Complex b);
Complex operator*(Complex a, Complex b);
Complex operator/(Complex a, Complex b);
ostream& operator<< (ostream& stream, Complex a);

//Find the greatest common denominator and lowest common multiple to reduce fraction and add fraction
static int gcd(int a, int b);
static int lcd(int a, int b);


Complex::Complex() {
	real = 0;
	imaginary = 1;
	denominator = 1;
}

/**
*Complex construcor that creates a Complex object out of a single int
*@param <int> n Which represents a real number without any imaginary aspects
*/
Complex::Complex(int n) {
	real = n;
	imaginary = 0;
	denominator = 1;
}

/**
@param <string> n Which represents a whole number
*Complex constructor that aids the main computation by allowing the passing of numbers larger than 1 singificant digit
*/
Complex::Complex(string n) {
	int realInt = 0;
	stringstream realSS(n);
	realSS >> realInt;
	real = realInt;
	imaginary = 0;
	denominator = 1;
}

/**
*@param <string> r, <string> i : String representations of real and imaginary part of Complex number
*Complex constructor that aids the main computation by taking in a real and imaginary string
*/
Complex::Complex(string r, string i) {
	int realInt = 0;
	stringstream realSS(r);
	realSS >> realInt;
	real = realInt;
	int imagInt = 0;
	stringstream imagSS(i);
	imagSS >> imagInt;
	imaginary = imagInt;
	denominator = 1;
}

Complex::Complex(int REAL, int imag, int den) {
	real = REAL;
	imaginary = imag;
	denominator = den;
}

/**
Formats the real, imaginary and denominator into a string representation
@return this Complex object's data
*/
string Complex::toString() const {
	//First determines if the Complex number can be simplified
	bool simplifiable = canSimplify();
	//If so it then creates new values of type int since the function is const
	//and this Complex obj cannot be modified
	if (simplifiable) {
		//Finds the dividing factor to simplify
		int divingFactor = gcd(real, gcd(imaginary, denominator));
		int simpReal = real / divingFactor;
		int simpImag = imaginary / divingFactor;
		int simpDen = denominator / divingFactor;
		//Formats the Complex properly if the real number is less than 0 AKA negative
		if (real < 0) {
			//Utilizes stringstream to convert the type int data members into strings
			stringstream s;
			s << (simpReal * -1);
			string formatS = s.str();
			stringstream s1;
			s1 << (simpImag * -1);
			string formatS1 = s1.str();
			stringstream s2;
			s2 << (simpDen * -1);
			string formatS2 = s2.str();
			string result = "[";
			int conjImag = simpImag * -1;
			//Formats the string so that theres is no +-i
			if (conjImag < 0) {
				if (conjImag == -1) {
					result = result + formatS + "-i]/" + formatS2;
				}
				else {
					result = result + formatS + formatS1 + "i]/" + formatS2;
				}
			}
			else {
				if (conjImag == 1) {
					result = result + formatS + "+i]/" + formatS2;
				}
				else {
					result = result + formatS + "+" + formatS1 + "i]/" + formatS2;
				}
			}
			return result;
		}
		//PERFORMS SAME PROCESS EXCEPT WITHOUT NEGATIVE FORMATTING
		else {
			stringstream s;
			s << simpReal;
			string formatS = s.str();
			stringstream s1;
			s1 << simpImag;
			string formatS1 = s1.str();
			stringstream s2;
			s2 << simpDen;
			string formatS2 = s2.str();
			string result = "[";
			if (simpImag < 0) {
				if (simpImag == -1) {
					result = result + formatS + "-i]/" + formatS2;
				}
				else {
					result = result + formatS + formatS1 + "i]/" + formatS2;
				}
			}
			else {
				if (simpImag == 1) {
					result = result + formatS + "+i]/" + formatS2;
				}
				else {
					result = result + formatS + "+" + formatS1 + "i]/" + formatS2;
				}
			}
			return result;
		}
	}
	

	//PERFORMS EXACT SAME AS THE ENTIRE CODE BLOCK UP ABOVE ALTHOUGH THIS OCCURS WHEN THE 
	//COMPLEX IS NOT SIMPLIFIABLE
	if (real < 0) {
		stringstream s;
		s << (real * -1);
		string formatS = s.str();
		stringstream s1;
		s1 << (imaginary * -1);
		string formatS1 = s1.str();
		stringstream s2;
		s2 << (denominator * -1);
		string formatS2 = s2.str();
		string result = "[";
		int conjImag = imaginary * -1;
		if (conjImag < 0) {
			if (conjImag == -1) {
				result = result + formatS + "-i]/" + formatS2;
			}
			else {
				result = result + formatS + formatS1 + "i]/" + formatS2;
			}
		}
		else {
			if (conjImag == 1) {
				result = result + formatS + "+i]/" + formatS2;
			}
			else {
				result = result + formatS + "+" + formatS1 + "i]/" + formatS2;
			}
		}
		return result;
	}
	else {
		stringstream s;
		s << real;
		string formatS = s.str();
		stringstream s1;
		s1 << imaginary;
		string formatS1 = s1.str();
		stringstream s2;
		s2 << denominator;
		string formatS2 = s2.str();
		string result = "[";
		if (imaginary < 0) {
			if (imaginary == -1) {
				result = result + formatS + "-i]/" + formatS2;
			}
			else {
				result = result + formatS + formatS1 + "i]/" + formatS2;
			}
		}
		else {
			if (imaginary == 1) {
				result = result + formatS + "+i]/" + formatS2;
			}
			else {
				result = result + formatS + "+" + formatS1 + "i]/" + formatS2;
			}
		}
		return result;
	}
}

/**
*@param reference to Complex obj
*Copy Constructor
@return Complex object
*/
Complex & Complex::operator=(Complex const & c) {
	real = c.real;
	imaginary = c.imaginary;
	denominator = c.denominator;
	return (*this);
}

/**
*@param Two Complex numbers in which the specific operator is to be carried out to
*performs substraction
*@return Complex obj 
*/
inline Complex operator-(Complex a, Complex b) {
	int LCD = lcd(a.denominator, b.denominator);
	int aMultiplier = LCD / a.denominator;
	int bMultiplier = LCD / b.denominator;
	int r = (aMultiplier * a.real) - (bMultiplier * b.real);
	int i = (aMultiplier * a.imaginary) - (bMultiplier * b.imaginary);
	return Complex(r, i, LCD);
}

/**
*@param Two Complex numbers in which the specific operator is to be carried out to
*performs addition
*@return Complex obj
*/
inline Complex operator+(Complex a, Complex b) {
	int LCD = lcd(a.denominator, b.denominator);
	int aMultiplier = LCD / a.denominator;
	int bMultiplier = LCD / b.denominator;
	int r = (aMultiplier * a.real) + (bMultiplier * b.real);
	int i = (aMultiplier * a.imaginary) + (bMultiplier * b.imaginary);
	return Complex(r, i, LCD);
}

/**
*@param Two Complex numbers in which the specific operator is to be carried out to
*performs multiplication
*@return Complex obj
*/
inline Complex operator*(Complex a, Complex b) {
	int r = (a.real * b.real) - (a.imaginary * b.imaginary);
	int d = (a.denominator * b.denominator);
	int i = (a.real * b.imaginary) + (a.imaginary * b.real);
	return Complex(r, i, d);
}

/**
*@param Two Complex numbers in which the specific operator is to be carried out to
*performs division
*@return Complex obj
*/
inline Complex operator/(Complex a, Complex b) {
	//b is the lefthand side and b is the righthand side
	//Comes out as Complex B/ Complex A
	int aConjugateRealResult = (b.real * b.real);
	int imagConj = b.imaginary * -1;
	int aConjugateImagResult = (b.imaginary * b.imaginary);
	int denResult = aConjugateImagResult + aConjugateRealResult;
	int realResult = (b.real * a.real) + (b.imaginary * a.imaginary);
	int imagResult = (imagConj * a.real) + (b.real * a.imaginary);
	return Complex(realResult, imagResult, denResult);
}

inline ostream & operator<<(ostream & stream, Complex a) {
	stream << a.toString();
	return stream;
}

/**
@param Two respective denominators of type int
Finds the largest positive integer that divides the numbers without a remainder
by utilizing the Euclidean algorithm through recursion
@return int The highest common factor of the two arguments
*/
inline static int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

/**
@param Two respective denominators of type int
Determines the least common multiple out of the set of two numbers to simplify fractions
@return int The lowest common denominator of the two arguments
*/
inline static int lcd(int a, int b) {
	int result = (a * b) / gcd(a, b);
	return result;
}


/**
*Using multiple instances of the GCD function determines if the Complex number can be simplified
@return <bool> true if simplifiable/else otherwise
*/
bool Complex::canSimplify() const{
	int GCD = gcd(real, gcd(imaginary, denominator));
	if (GCD != 1) {
		return true;
	}
	else {
		return false;
	}
}
