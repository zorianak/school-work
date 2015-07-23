#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//
//	Input:	initChar - takes in a single character
//	Output: Color information based on that char, or
//			intakes another char.
//
//	Desc.:	intakes a letter from a user and assigns a
//			number to denote what color is an electonic
//			component's rating
//--------------------------------------------------------

int main(int argc, char** argv) {
	// initial character
	char initChar;
	
	cout << "Please enter the first letter of the color: ";
	cin >> initChar;
	cout << endl;
	
	switch(tolower(initChar)) {
		case 'b':
			cout << "Please enter the second letter: ";
			cin >> initChar;
			cout << endl;
			
			// test for black/blue/brown
			switch(tolower(initChar)){
				case 'l':
					cout << "Please enter the third letter: ";
					// we can just assign it to the initChar - no
					// need for a new variable.
					cin >> initChar;
					cout << endl;
					
					switch(tolower(initChar)) {
						case 'u':
							cout << "Blue stands for digit 6." << endl;
							break;
						case 'a':
							cout << "Black stands for digit 0." << endl;
							break;
						default:
							cout << "Unknown color." << endl;
							break;
					}
					
					break;
				case 'r':
					cout << "Brown stands for digit 1." << endl;
					break;
				default:
					cout << "Unknown color." << endl;
					break;
			}
			
			break;
		case 'r':
			cout << "Red stands for digit 2." << endl;
			break;
		case 'o':
			cout << "Orange stands for digit 3." << endl;
			break;
		case 'y':
			cout << "Yellow stands for digit 4." << endl;
			break;
		case 'v':
		// since violet/purple tend to be interchangable,
		// may as well account for both as it only takes an
		// extra check.
		case 'p':
			cout << "Violet stands for digit 7." << endl;
			break;
		case 'w':
			cout << "White stands for digit 9." << endl;
			break;
		case 'g':
			cout << "Please enter the next two letters: ";
			cin >> initChar;
			
				switch(tolower(initChar)){
					// The user has input 2 letters, but the 
					// first one goes into initChar, and then
					// if that is 'correct', initChar is then assigned
					// the third letter. Sweet!
					case 'r':
						cin >> initChar;
						cout << endl;
						
							switch(tolower(initChar)){
								case 'e':
									cout << "Green stands for digit 5." << endl;
									break;
								case 'a':
									cout << "Gray stands for digit 8." << endl;
									break;
								default:
									cout << "Unknown color." << endl;
									break;
							}
							
							
						break;
					// If the user didn't input an r, then no need to read the
					// rest of the input - it's not a known color.
					default:
						cout << "Unknown color." << endl;
						break;
						
				}
			break;
		default:
			cout << "Unknown color." << endl;
			break;
			
	}
	
	return 0;
}
