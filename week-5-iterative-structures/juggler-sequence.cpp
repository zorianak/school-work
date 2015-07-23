#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//
//
//	Desc.:	Calculates terms in a juggler sequence
//--------------------------------------------------------

const string FIRST_TERM_PROMPT = "Enter the first term: ",
			 NUM_TERMS_PROMPT = "Enter the number of turns to calculate (after first): ",
			 LINES_DISPLAY_PROMPT = "Enter the terms to display per line: ";

int validateInput(string prompt);

int main() {
	int firstTerm,
		numTerms,
		numLines;
	
	cout << "Program will determine the terms in a Juggerly Series" << endl << endl;
	
	// user userdefined function to get valid input
	firstTerm = validateInput(FIRST_TERM_PROMPT);
	numTerms = validateInput(NUM_TERMS_PROMPT) - 1;
	numLines = validateInput(LINES_DISPLAY_PROMPT);
	
	// Now loop through numTerms amount of times to determine 
	// the sequence itself
	cout << "First " << numTerms << " terms of JUGGLER SERIES starting with " << firstTerm << endl;
	int j = 1;
	for(int i = 0; i < numTerms; i++){
		// so we want to print out each line,
		// and then add an endl if we've reached
		// numTerms per line
		
		// so we want to calculate and print out a term, and set a thing to that
		// we can reuse firstTerm here..
		// we also want to determine if it is odd or even, so mod 2 here
		// If its odd...
		if(firstTerm % 2 == 1) {
			firstTerm = floor(pow(firstTerm, 1.5));
		} else {
			firstTerm = floor(pow(firstTerm, 0.5));
		}
		
			cout << setw(15) << firstTerm;
		
		// just mod whatever i is at and that should tell us
		// if its a multiple of the amount of lines
		// so that we know if we've done x amount terms
		if(j == numLines) {
			cout << endl;
			j = 1;
		} else {
			j++;
		}
	}
	
	return 0;
}

//--------------------------------------------------------
//	Input: 	prompt - the prompt we are getting input for
//	output: Prompt user for needed input
//	return: Returns an int of whatever is being validated
//
//
//	Desc.:	Validates user's input and prompts if invalid
//--------------------------------------------------------

int validateInput(string prompt){
	int input = 0;
	// so test for the input
	// We can use this for the first input, thus a do-while should
	// do the trick here
	do {
		cout << prompt;
		cin >> input;
		cout << endl;
		
		// now inform the user that their input is invalid and 
		// then prompt again.
		if(input <= 0) {
			cout << endl << "Input must be a positive integer greater than 0." << endl << endl;
		}
	} while (input <= 0);
	
	return input;
}
