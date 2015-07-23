#include <iostream>
#include <iomanip>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//
//
//	Desc.:	Calculates the sum of all even numbers using
//			a formula, a loop, and recursion
//--------------------------------------------------------

// uses formula
void formulaEvenSum(int num, int& formulaResult);

// Computes and returns the sum using iteration
void LoopEvenSum(int num, int& loopResult);

// Copmute and return the sum using recursion
void RecursiveEvenSum(int num, int& recurResult, int i);

int main() {
	int num = 1;
	while(num != 0) {
		num = 0;
		
		int formulaResult = 0,
			loopResult = 0,
			recurResult = 0;
		cout << "Program to compute teh sum of even integers from 1 to num" << endl << endl;
		cout << "Enter a positive integoer (or 0 to exit): ";
		cin >> num;
		cout << endl;
		
		if(num > 0) {
			formulaEvenSum(num, formulaResult);
			cout << "Formula result = " << setw(5) << formulaResult << endl;
			LoopEvenSum(num, loopResult);
			cout << "Loop result = " << setw(8) << loopResult << endl;
			RecursiveEvenSum(num, recurResult, 1);
			cout << "Recursion result = " << setw(3) << recurResult << endl << endl;
		} else {
			cout << "Goodbye!";
			return 0;
		}
	}
	
}

//--------------------------------------------------------
//	output params:	formulaResult - the result of the addition
//	input params:	num - the final number
//	return: 		none
//
//
//	Desc.:	Uses formula to compute sum of evens
//--------------------------------------------------------

void formulaEvenSum(int num, int& formulaResult) {
	formulaResult = (num/2) * ((num/2) + 1);
}

//--------------------------------------------------------
//	output params:	loopResult - the result of the addition
//	input params:	num - the final number
//	return: 		none
//
//
//	Desc.:	Uses loop to compute sum of evens
//--------------------------------------------------------
void LoopEvenSum(int num, int& loopResult) {
	for(int i = 0; i <= num; i++) {
		if( i % 2 == 0) {
			loopResult += i;
		}
	}
}

//--------------------------------------------------------
//	output params:	recurResult - the result of the addition
//	input params:	num - the final number
//					i - the counter for telling where we are
//					recursively
//	return: 		none
//
//
//	Desc.:	Uses recursion to compute sum of evens
//--------------------------------------------------------
void RecursiveEvenSum(int num, int& recurResult, int i) {
	if(i == 1)
		recurResult = 0;
	if(i > num)
		return;
	if(i %2 == 0)
		recurResult += i;
	RecursiveEvenSum(num, recurResult, i + 1);
}
