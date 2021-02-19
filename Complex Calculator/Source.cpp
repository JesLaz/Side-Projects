/*
Name: Jessie Lazo
Purpose of Program: Read in a Complex number equation and produce and format result of such
*/
#include <iostream>
#include <string>
#include "Complex.h"
//#include "Node.h"
#include "DoublyLinkedList.h"
#include "StackDoublyLinkedList.h"
#include <vector>
#include <array>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

static map <char, int> operatorMap{ {'(', -1}, {')', -1}, {'%', 0}, {'+', 1}, { '-', 1 }, { '*', 2 }, { '/', 2 } };
static Complex conjugate(Complex c);//Returns the conjugate of the Complex number
static Complex calculate(Complex c1, Complex c2, char op);//Performs the desired operation to the Comlpex obj's
static int getPrecedence(char c);//Returns the value of an operators precedence
static Complex computeString(string s);//Carries out the computation of the given equation
static bool isOperator(char c);//Determines if character is a predetermined operator





/**
*@param Complex object c
*Function that multiplies the Complex obj passed in to determine it's conjugate
*@return Complex object equal to the conjugate of the argument passed in
*/
static Complex conjugate(Complex c) {
	return Complex(c.real, c.imaginary * -1, c.denominator);
}

/**
*@parma c1 and c2 which are the lefthand and righthand operands of an equation respectively and op which is the operator to be carried out
*Using enumeration the function performs the specific operator
*@return Complex obj that is the result of the arithmetic to the parameters
*/
static Complex calculate(Complex c1, Complex c2, char op) {
	Complex c;
	switch (op) {
	case '+': c = c1 + c2;
		return c;
	case '-': c = c1 - c2;
		return c;
	case '*': c = c1 * c2;
		return c;
	case '/': c = c1 / c2;
		return c;
	}
}

/**
*@param the character representation of a specific operator being parsed
*Using a map to expedite finding the value of the specified key
*@return the int value found from the map operatorMap
*/
static int getPrecedence(char c) {
	return operatorMap.at(c);
}

/**
*@param character of the string being parsed
*Determines if the character is one of the valid operations for the Complex class
@return bool value indicative of the statement
*/
static bool isOperator(char c) {
	vector<char> ops{ '%', '-', '+', '/', '*' };
	for (auto x : ops) {
		if (c == x) {
			return true;
		}
	}
	return false;
}

/**
*@param a string of the equation to be calculated
*By using two StackDoublyLinkedList(s) of the type char and Complex the string is parsed first testing 
*if the characters are a number and retrieving all parts of that number and then determines by precedence
*what actions should be taken to either compute contents of the Complex stack with the current operator
*or if it should be pushed onto the stack for later evaluation once all of the string has been parsed
*@return Complex that is the result of all the operations in the string
*/
static Complex computeString(string s) {
	StackDoublyLinkedList<char> operators;
	StackDoublyLinkedList<Complex> comps;
	string temp = "";
	bool begunComplex = false;
	//Parses through string
	for (int i = 0; i < s.size(); i++) {
		//To determine if there is more than one digit to a number continues to perform checks
		if (isdigit(s[i])) {
			begunComplex = true;
			temp += s[i];
		}
		//There may be a numerical part to the imaginary number
		else if(s[i] == 'i'){
			begunComplex = false;
			//if the size is greater than one then there is a numerical part to the imaginary
			if (temp.size() >= 1) {
				int findI = temp.find('i');
				string imag = temp.substr(0, findI);
				Complex c("0", imag);
				comps.addBack(c);
			}
			//otherwise creates just an imaginary
			else {
				Complex c(0, 1, 1);
				comps.addBack(c);
			}
			temp = "";
		}
		//If there is no imaginary then the number is created as a Complex obj
		else if(begunComplex == true){
			begunComplex = false;
			Complex c(temp);
			comps.addBack(c);
			temp = "";
		}
		Complex d(-1);//Dummy object used because in nested if statements there are errors of trying to push a newly created Comlex obj onto the stack


		if (s[i] == '(') {
			operators.addBack(s[i]);
		}
		//Carries out operations in the opeartor stack until the opening ( is found
		else if (s[i] == ')') {
			if (comps.getSize() >= 2) {
				while (operators.getTop() != '(') {
					char op = operators.getTop();
					operators.popBack();
					Complex rightHand = comps.getTop();
					comps.popBack();
					Complex leftHand = comps.getTop();
					comps.popBack();
					Complex result = calculate(leftHand, rightHand, op);
					comps.addBack(result);
				}
				operators.popBack();
			}
		}
		//Simply carries out the conjugate without adding to operators stack
		else if (s[i] == '%') {
			Complex top = comps.getTop();
			comps.popBack();
			Complex topConj = conjugate(top);
			comps.addBack(topConj);
		}
		//There are more than one operators therefore comparisons must be drawn
		else if (isOperator(s[i]) == true && operators.getSize() > 0) {
			char op = operators.getTop();
			//the current op has lowest precedence, carry out top before 
			if ((getPrecedence(s[i]) > getPrecedence(op)) && comps.getSize() > 1 && op != '(') {
				operators.popBack();
				Complex rightHand = comps.getTop();
				comps.popBack();
				Complex leftHand = comps.getTop();
				comps.popBack();
				d = calculate(leftHand, rightHand, op);
				comps.addBack(d);
			}
			else if (d.real != -1) {
				comps.addBack(d);
			}
			operators.addBack(s[i]);
		}
		else if (isOperator(s[i]) == true) {
			operators.addBack(s[i]);
		}
		else if (s[i] == '=') {
			continue;
		}
	}//end for loop
	while (operators.isEmpty() != true) {
		char op = operators.getTop();
		operators.popBack();
		Complex rightHand = comps.getTop();
		comps.popBack();
		Complex leftHand = comps.getTop();
		comps.popBack();
		Complex result = calculate(leftHand, rightHand, op);
		comps.addBack(result);
	}//end final while
	return comps.getTop();
}//end function


int main() {
	ifstream myFile;
	ofstream outFile;
	outFile.open("result.txt", ios_base::app);
	myFile.open("expression.txt");
	if (!myFile) {
		cout << "Could not open expressions file" << endl;
	}
	vector<string> expressions;
	string line;
	while (getline(myFile, line)) {
		expressions.push_back(line);
	}
	for (auto x : expressions) {
		cout << "input = " << x << endl;
		outFile << computeString(x) << endl;
		cout << "Final Result = " << computeString(x) << "\n" <<  endl;
	}
	myFile.close();
	outFile.close();
	return 0;
}

