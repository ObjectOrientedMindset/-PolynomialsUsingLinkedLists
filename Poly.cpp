#include <stdio.h>
#include "Poly.h"
#include<string>
#include<sstream>
#include<vector>
#include<math.h>
#include<iostream>
using namespace std;
//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the poly1 PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
//
PolyNode* CreatePoly(char* expr) {
	//Remove spaces
	vector<string> terms;
	string term;
	bool coef = true;
	string _coefficient = "";
	string _exponent = "";
	double coefficient = 0;
	int exponent = 0;
	PolyNode* head = new PolyNode();
	PolyNode* tail = new PolyNode();
	string str(expr);
	stringstream ss;
	string temp;
	ss << str;
	str = "";
	while (!ss.eof()) {
		ss >> temp;
		str = str + temp;
	}
	//Get terms
	for (int i = 0; i < str.size(); i++)
	{
		if (i > 0) {
			if (str[i] == '-' || str[i] == '+') {
				terms.push_back(term);
				term = "";
			}
		}
		term += str[i];
		if (i == str.size() - 1) {
			terms.push_back(term);
		}
	}
	//Create Linked List
	for (int i = 0; i < terms.size(); i++) {
		//Calculate coef and exp
		for (int y = 0; y < terms[i].size(); y++) {
			if (terms[i][y] == 'x') {
				coef = false;
				if (_coefficient == "-") {
					coefficient = -1;
				}
				else if (_coefficient == "+") {
					coefficient = 1;
				}
				else if (_coefficient == "") {
					coefficient = 1;
				}
				else {
					coefficient = stod(_coefficient);
				}
				exponent = 1;
			}
			if (coef) {
				_coefficient += terms[i][y];
			}
			if (y == terms[i].size() - 1) {
				if (_coefficient == "-") {
					coefficient = -1;
				}
				else if (_coefficient == "+") {
					coefficient = 1;
				}
				else if (_coefficient == "") {
					coefficient = 1;
				}
				else {
					coefficient = stod(_coefficient);
				}
			}
			if (terms[i][y] == '^') {
				for (int a = y + 1; a < terms[i].size(); a++) {
					_exponent += terms[i][a];
				}
				exponent = stoi(_exponent);
			}
		}

		PolyNode* newNode = new PolyNode();
		newNode->coef = coefficient;
		newNode->exp = exponent;
		newNode->next = NULL;

		if (i == 0) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		coefficient = 0;
		exponent = 0;
		_coefficient = "";
		_exponent = "";
		coef = true;
	}

	return head;
} //end-CreatePoly

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {

	while (poly != NULL) {
		PolyNode* old = poly;
		poly = poly->next;
		delete old;
	}

} // end-DeletePoly

//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
PolyNode* tail2 = new PolyNode();
PolyNode* AddNode(PolyNode* head, double coef, int exp) {
	//Count Node
	int nodeCount = 0;
	PolyNode* temp = head;
	PolyNode* temp2 = head;
	bool equal = false;

	while (temp != NULL) {
		nodeCount++;
		temp = temp->next;
	}
	if (nodeCount == 0) {
		PolyNode* newNode = new PolyNode();
		newNode->coef = coef;
		newNode->exp = exp;
		newNode->next = NULL;
		head = newNode;
		tail2 = newNode;
	}
	else {
		for (int i = 0; i < nodeCount; i++) {
			if (temp2->exp == exp) {
				temp2->coef += coef;
				equal = true;
			}
			temp2 = temp2->next;
		}
		if (!equal) {
			PolyNode* newNode = new PolyNode();
			newNode->coef = coef;
			newNode->exp = exp;
			newNode->next = NULL;

			tail2->next = newNode;
			tail2 = newNode;
		}
	}
	return head;
} // end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode* Add(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* poly = new PolyNode();
	struct PolyNode* temp = new PolyNode();
	temp->next = NULL;
	poly = temp;
	while (poly1 && poly2)
	{
		if (poly1->exp > poly2->exp)
		{
			temp->coef = poly1->coef;
			temp->exp = poly1->exp;
			poly1 = poly1->next;
		}
		else if (poly1->exp < poly2->exp)
		{
			temp->coef = poly2->coef;
			temp->exp = poly2->exp;
			poly2 = poly2->next;
		}
		else
		{
			temp->coef = poly1->coef + poly2->coef;
			temp->exp = poly1->exp;
			poly1 = poly1->next;
			poly2 = poly2->next;
		}

		if (poly1 && poly2)
		{
			temp->next = new PolyNode();
			temp = temp->next;
			temp->next = NULL;
		}
	}
	while (poly1 || poly2)
	{
		temp->next = new PolyNode();
		temp = temp->next;
		temp->next = NULL;

		if (poly1)
		{
			temp->coef = poly1->coef;
			temp->exp = poly1->exp;
			poly1 = poly1->next;
		}

		else if (poly2)
		{
			temp->coef = poly2->coef;
			temp->exp = poly2->exp;
			poly2 = poly2->next;
		}
	}
	return poly;
}

 //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2) {
	PolyNode* poly = new PolyNode();
	struct PolyNode* temp = new PolyNode();
	temp->next = NULL;
	poly = temp;
	while (poly1 && poly2)
	{
		if (poly1->exp > poly2->exp)
		{
			temp->coef = poly1->coef;
			temp->exp = poly1->exp;
			poly1 = poly1->next;
		}
		else if (poly1->exp < poly2->exp)
		{
			temp->coef = -poly2->coef;
			temp->exp = poly2->exp;
			poly2 = poly2->next;
		}
		else
		{
			temp->coef = poly1->coef - poly2->coef;
			temp->exp = poly1->exp;
			poly1 = poly1->next;
			poly2 = poly2->next;
		}

		if (poly1 && poly2)
		{
			temp->next = new PolyNode();
			temp = temp->next;
			temp->next = NULL;
		}
	}
	while (poly1 || poly2)
	{
		temp->next = new PolyNode();
		temp = temp->next;
		temp->next = NULL;

		if (poly1)
		{
			temp->coef = poly1->coef;
			temp->exp = poly1->exp;
			poly1 = poly1->next;
		}

		else if (poly2)
		{
			temp->coef = -poly2->coef;
			temp->exp = poly2->exp;
			poly2 = poly2->next;
		}
	}
	return poly;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2) {
	int coefficient, exponent;
	PolyNode* poly = new PolyNode();
	struct PolyNode* temp = poly2;
	if (!poly1 && !poly2) {
		return poly;
	}
	if (!poly1) {
		poly = poly2;
	}
	else if (!poly2) {
		poly = poly1;
	}
	else {
		while (poly1) {
			while (poly2) {
				coefficient = poly1->coef * poly2->coef;
				exponent = poly1->exp + poly2->exp;
				poly2 = poly2->next;
				poly = AddNode(poly, coefficient, exponent);
			}
			poly2 = temp;
			poly1 = poly1->next;
		}
	}
	return poly;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode* poly, double x) {
	int temp = 0;
	int result = 0;
	while (poly != NULL) {
		temp = 0;
		if (poly->exp == 0) {
			result += poly->coef;
		}
		else {
			
			result += pow(x, poly->exp) * poly->coef;
		}
		poly = poly->next;
	}
	return result;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode* Derivative(PolyNode* poly) {
	PolyNode* temp = poly;
	while (temp != NULL) {
		
		if (temp->exp == 0) {
			temp->coef = 0;
		}
		else {
			temp->coef = temp->exp * temp->coef;
			temp->exp -= 1;
		}
		temp = temp->next;
	}
	return poly;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode* poly, int x1, int x2) {
	for (int i = x1; i < x2; i++) {
		cout << "y = " << Evaluate(poly, i) << "\n";
	}
} //end-Plot
