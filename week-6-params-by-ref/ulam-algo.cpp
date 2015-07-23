#include <iostream>
#include <iomanip>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//
//
//	Desc.:	Calculates tests for Ulam's algorithm
//--------------------------------------------------------

void validateInput(int& num1, int& num2);
int incrementNum(int num1, int num2);
void ulamAlgo(int num1, int num2, int increment);

int main() {
	int num1,
		num2,
		increment;
	cout << "Program will test Ulam's algorithm" << endl << endl;
	
	validateInput(num1, num2);
	cout << endl;
	increment = incrementNum(num1, num2);
	ulamAlgo(num1, num2, increment);
	
	return 0;
}

//--------------------------------------------------------
//	output params:	num1 - first number to test
//					num2 - last number to test
//	return: 		none
//
//
//	Desc.:	Prompts for first and last numbers, and validates
//			that they are between 100 and 1000, and that
//			the last number is greater than the first
//--------------------------------------------------------

void validateInput(int& num1, int& num2) {
	do{
		cout << "Enter the first number to test: ";
		cin >> num1;
		
		if(num1 < 100 || num1 > 1000) {
			cout << "Invalid -- must be between 100 and 1000. Try again." << endl << endl;
		}
	} while(num1 < 100 || num1 > 1000);
	
	do{
		cout << endl << "Enter the last number to test: ";
		cin >> num2;
		
		if(num2 < 100 || num2 > 1000) {
			cout << "Invalid -- must be between 100 and 1000. Try again." << endl << endl;
		}
		if(num2 < num1) {
			cout << "Invalid -- Last number must be greater than first number. Try again." << endl;
		}
	} while((num2 < 100 || num2 > 1000) || num2 < num1);
	
	return;
}

//--------------------------------------------------------
//	Input: 	num1 - first number to test
//			num2 - second number to test
//	output: Prompt user for increment value
//	return: increment - value to increment by
//
//
//	Desc.:	Determines if num2 is more than 1 greater than
//			num1, and if not, then prompts for what value
//			to increment by.
//--------------------------------------------------------

int incrementNum(int num1, int num2) {
	int increment = 1;
	// if the nums are equal, or num2 is only num1+1,
	// increment by 1
	if(!(num1 == num2) && !(num1 + 1 == num2)) {
		
		while(increment <= 1) {
			cout << "Enter the increment for testing values: ";
			cin >> increment;
			cout << endl;
			
			if(increment <= 1) {
				cout << "Invalid -- increment must be greater than 1. Try again." << endl;
			}
		}
		
	}
	
	return increment;
}

//--------------------------------------------------------
//	Input: 	num1 - first number to test
//			num2 - second number to test
//			increment - what to increment test nums by
//	output: Values from testing the algorithm
//	return: void
//
//
//	Desc.:	Runs Ulam's algorithm on the first and last 
//			numbers, and displays the results
//--------------------------------------------------------
void ulamAlgo(int num1, int num2, int increment) {
	const int colWidth = 7,
			  amntTerms = 10;
			  
	int num = num1,
		i = 0,
		j = 1;
	
	// loop through the sequence of terms to reach 1
	for(i = num1; i <= num2; i = i + increment) {
		num = i;
		cout << "Series generated for " << i << endl;
		int k = 1;
		while( num > 1 ) {
			
			// output term we're at, and endl if applicable
			cout << setw(colWidth) << num ;
			if( j == amntTerms) {
				cout << endl;
				j = 1;
			} else {
				j++;
			}
			
			// do math
			if(num % 2  == 0) {
				num = num / 2;
			} else {
				num = num * 3 + 1;
			}
			k++;
		}
		cout << endl << "Total number of terms: " << k << endl << endl;
		// so if we don't set num properly, it won't loop back.
		num = num1 + i;
		
	}
	
	return;
}
