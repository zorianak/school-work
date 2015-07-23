#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS362 Data Structures
//
//
//	Desc.:	reads MEDICAL.TXT and analyzes the data
//--------------------------------------------------------

bool readData(double empOnly[], double empFam[], int MAX_COVERED, int& amntFam, int& amntEmpOnly);

double avgExp(double theArray[], int count);
double highestExp(double theArray[], int count);
int amntOverAvg(double theArray[], int count, int avg);

void displayResult(int amntFam, int amntEmpOnly, double empHighest, double famHighest, int empOverAvg, int famOverAvg,
	double avgFamExp, double avgEmpExp);

int main() {
	bool success;
	
	const int MAX_COVERED = 1000;
	
	int amntFam = 0,
		amntEmpOnly = 0,
		empOverAvg,
		famOverAvg;
	
	double avgEmpExp,
		avgFamExp,
		empHighest,
		famHighest;
	
	double empOnly[MAX_COVERED],
			empFam[MAX_COVERED];
	
	// set this to a boolean so we know if it went well
	success = readData(empOnly, empFam, MAX_COVERED, amntFam, amntEmpOnly);
	
	if(success) {
		avgEmpExp = avgExp(empOnly, amntEmpOnly);
		empHighest = highestExp(empOnly, amntEmpOnly);
		empOverAvg = amntOverAvg(empOnly, amntEmpOnly, avgEmpExp);
		
		avgFamExp = avgExp(empFam, amntFam);
		famHighest = highestExp(empFam, amntFam);
		famOverAvg = amntOverAvg(empFam, amntFam, avgFamExp);
		
		displayResult(amntFam, amntEmpOnly, empHighest, famHighest, empOverAvg, famOverAvg,
	avgFamExp, avgEmpExp);
		
	} else { // didn't read file, exit 5
		return 5;
	}
	
	
	return 0;
}

//--------------------------------------------------------
//	Desc: 	Calculates sum of the items in the array, and
//			then calculates the average expense
//
//	Input: 	empOnly - array of employee-only expenses
//			empFam - array of family expenses
//			MAX_COVERED - the maxmium amount per array
//			amntFam - count of the family plans
//			amntEmpOnly - count of employee plans
//
//
//	Return:	true or false if successful
//--------------------------------------------------------

bool readData(double empOnly[], double empFam[], int MAX_COVERED, int& amntFam, int& amntEmpOnly){
	
	
	const string FILENAME = "MEDICAL.txt";
	
	double annExpense;
		
	char coverType,
		ch;
	
	ifstream medFile;
	
	medFile.open(FILENAME.c_str());
	
	if(medFile){ // opens file as expected
		
		while(medFile){			// test for end of file
			medFile >> coverType >> annExpense; // read the coverage type and expense
			
			if(coverType == 'F') { // family coverage
				if(amntFam <= MAX_COVERED) {
					empFam[amntFam] = annExpense;
					amntFam++; // increment
				} else { // too many!
					cout << "Too many!" << endl;
				}
			} else { // Otherwise, its employee only
				if(amntEmpOnly <= MAX_COVERED) {
					empOnly[amntEmpOnly] = annExpense;
					amntEmpOnly++; // increment
				} else { // "Too many!"
					cout << "Too many!" << endl;
				}
			}
			
			// test if both are full
			if(amntFam > MAX_COVERED && amntEmpOnly > MAX_COVERED) {
//				cout >> "Too many for both!" >> endl;
			}
			
			medFile.ignore(10, '\n');
		}
		
		
		return true;
	} else {
		cout << "Couldn't open" << endl;
		return false;
	}
	
	
	medFile.close();
}

//--------------------------------------------------------
//	Desc: 	Calculates sum of the items in the array, and
//			then calculates the average expense
//
//	Input: 	theArray - the array to be used
//			count - the amount of items in the array
//
//
//	Return:	avg - the average of the expenses
//--------------------------------------------------------

double avgExp(double theArray[], int count){
	double sum = 0.0,
			avg;
			
	for(int i = 0; i <= count; i++) {
		sum = sum + theArray[i];
	}
			
	avg = sum / count;
	
	return avg;
}

//--------------------------------------------------------
//	Desc: 	Gets the highest expense
//
//	Input: 	theArray - the array to be used
//			count - the amount of items in the array
//
//
//	Return:	highest - the highest expense in the array
//--------------------------------------------------------

double highestExp(double theArray[], int count) {
	double highest = 0.0,
		tempDouble;
	
	for(int i = 0; i <= count; i++) {
		tempDouble = theArray[i];
		if(tempDouble > highest) {
			highest = tempDouble;
		}
	}
	
	return highest;
}

//--------------------------------------------------------
//	Desc: 	Gets amount of values over the average expense
//
//	Input: 	theArray - the array to be used
//			count - the amount of items in the array
//			avg - the average
//
//
//	Return:	amntOver - the amount of expenses over the avg
//--------------------------------------------------------

int amntOverAvg(double theArray[], int count, int avg) {
	int amntOver = 0;
	
	for(int i = 0; i<= count; i++){
		if(theArray[i] > avg) {
			amntOver++;
		}
	}
	
	return amntOver;
}

//--------------------------------------------------------
//	Desc: 	Displays the results of the program
//
//	Input: 	amntFam - the amount of employees on the family plan
//			amntEmpOnly - employee-only plans
//			empHighest - highest expense, employee-only
//			famHighest - highest family plan expense
//			empOverAvg - amount of emp-only expenses over average
//			famOverAvg - amount of fam expenses over avg
//			avgFamExp - the average family expense
//			avgEmpExp - average employee-only expense
//
//
//	Return:	void
//--------------------------------------------------------

void displayResult(int amntFam, int amntEmpOnly, double empHighest, double famHighest, int empOverAvg, int famOverAvg,
	double avgFamExp, double avgEmpExp) {
	// we want to average these out now
	
	// if over 0, then we should be able to
	// test for average, over avg, and highest
	if(amntEmpOnly > 0) {
		cout << "For " << amntEmpOnly << " employees with employee only coverage:" << endl;

		
		cout << fixed << showpoint << setprecision(2);
		cout << '\t' << "Average expenses were $" << setw(5) << avgEmpExp << endl;
		cout << '\t' << "Highest expenses were $" << setw(5) << empHighest << endl;
		cout << '\t' << empOverAvg << " employee(s) expenses were over the average" << endl << endl;
		
	} else { // otherwise, there's nothing in there
		cout << "There were NO employees with employee-only coverage." << endl;
	}
	
	if(amntFam > 0) {
		cout << "For " << amntFam << " employees with family coverage:" << endl;
		
		
		cout << fixed << showpoint << setprecision(2);
		cout << '\t' << "Average expenses were $" << setw(5) << avgFamExp << endl;
		cout << '\t' << "Highest expenses were $" << setw(5) << famHighest << endl;
		cout << '\t' << famOverAvg << " employee(s) expenses were over the average" << endl;
	} else { 
		cout << "There were NO employees with family coverage." << endl;
	}
}
