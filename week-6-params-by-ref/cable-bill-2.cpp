#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//
//
//	Desc.:	Calculates tests for Ulam's algorithm
//--------------------------------------------------------

void validateSize(char& carSize, double& dailyRate);
int valMilesDays(string prompt);
void billParts(int miles, int limit, int days, double overRate, double sizeRate, double& milesCharge, double& carCharge, double& tax, double& total);

void dispayBill(char carSize, int daysRented, int milesDriven, double carCharge, double milesCharge, double tax, double totalBill);

int main() {
	 // Define constants for all the car related things
	 const double COMPACT_OVERAGE = .05,
				  MID_OVERAGE = .07,
				  FULL_OVERAGE = .09;
				  
	const int COMPACT_MILES = 20,
			  MID_MILES = 25,
			  FULL_MILES = 30;
		  
	char goAgain;
		 
	
	do {
		// initiate these at 0: otherwise, it endlessly loops the next times this runs
		int daysRented = 0,
			milesDriven = 0,
			mileLim = 0;
		double carCharge = 0,
			   milesCharge = 0,
			   tax = 0,
			   totalBill = 0,
			   overageRate = 0,
			   dailyRate = 0;
		char carSize = NULL;
			 
		cout << "This program will calculate a car rental bill for Rent2U" << endl << endl;
	
		validateSize(carSize, dailyRate);
		
		daysRented = valMilesDays("Enter number of days rented: ");
		if(carSize != 'S') {
			milesDriven = valMilesDays("Enter number of miles driven: ");
		} else{
			milesDriven = 0;
		}
		
		cout << "RENT2U RENTAL DETAILS" << endl;
		cout << setw(12) << "Car Size:";
		
		// compact and miles over compact limit
		if (carSize == 'C') {
			mileLim = COMPACT_MILES;
			overageRate = COMPACT_OVERAGE;
			cout  << setw(20) << "Compact" << endl;
		} else if(carSize == 'M') {
			mileLim = MID_MILES;
			overageRate = MID_OVERAGE;
			cout  << setw(20) << "Mid size" << endl;
		} else if(carSize == 'F') {
			mileLim = FULL_MILES;
			overageRate = FULL_OVERAGE;
			cout  << setw(20) << "Full size" << endl;
		} else {
			// assume SUV
			mileLim = -1;
			overageRate = -1;
			cout  << setw(20) << "SUV size" << endl;
		}
		
		billParts(milesDriven, mileLim, daysRented, overageRate, dailyRate, milesCharge, carCharge, tax, totalBill);
		
		dispayBill(carSize, daysRented, milesDriven, carCharge, milesCharge, tax, totalBill);
	
			cout << "Calculate another bill (y/n)? ";
			cin >> goAgain;
			if(goAgain != 'n') {
				cout << endl << endl;
			}
			
	} while(goAgain != 'n');
	
	return 0;
	
}

//--------------------------------------------------------
//	Description: 	Validates and reads car size, assings
//					values for the daily rate and car size
//	Input params: 	carSize - reads the car size and
//					validates it
//	Output Params:	carSize, dailyRate
//
//	Return: void
//--------------------------------------------------------

void validateSize(char& carSize, double& dailyRate) {
	
	// going to declare tehse in this scope and simply set
	// the car size and rate here, that way
	// if in the future the rates needed to be changed,
	// they only have to change in one spot.
	const double COMPACT_RATE = 22.91,
	 			  MID_RATE = 25.76,
	 			  FULL_RATE = 28.87,
	 			  SUV_RATE = 98.88;
	
	// initially this should eval to false, until proper input
	while(!(carSize == 'C' || carSize == 'M' || carSize == 'F' || carSize == 'S')) {
		cout << "Car sizes:" << endl;
		cout << setw(25) << "C - Compact size at $ " << COMPACT_RATE << " per day" << endl;
		cout << setw(21) << "M - Mid size at $ " << MID_RATE << " per day" << endl;
		cout << setw(22) << "F - Full size at $ " << FULL_RATE << " per day" << endl;
		cout << setw(16) << "S - SUV at $ " << SUV_RATE << " per day" << endl << endl;
		
		cout << "Enter the letter for the car size rented: ";
		cin >> carSize;
		// uppercase for easy testing
		carSize = toupper(carSize);
		
		// at the end of the loop, if it is still not valid, reprompt and inform user they
		// did not use valid input
		if(!(carSize == 'C' || carSize == 'M' || carSize == 'F' || carSize == 'S')){
			cout << "Please enter a valid car size: " << endl;
		}
		
	}
	
	if(carSize == 'C') {
		dailyRate = COMPACT_RATE;
	} else if(carSize == 'M') {
		dailyRate = MID_RATE;
	} else if(carSize == 'F') {
		dailyRate = FULL_RATE;
	} else {
		dailyRate = SUV_RATE;
	}
	
	cout << endl;
	
	return;
}

//--------------------------------------------------------
//	Description: 	Validates and reads days or miles rented
//	Input params: 	intVali - int being validated
//					prompt - the prompt to display if invalid
//
//	Return: daysRented
//--------------------------------------------------------
int valMilesDays(string prompt) {
	int amntValidate = 0;
	
	while(amntValidate < 1) {
		cout << prompt;
		cin >> amntValidate;
		cout << endl;
		
		if(amntValidate < 1) {
			cout << "Amount must be greater than one." << endl;
		}
	}
	
	return amntValidate;
}
//--------------------------------------------------------
//	Description: 	Calculates charges on the bill
//	Input params: 	limit, days, overRate, sizeRate
//	Output params:	milesCharge, carCharge, tax, total
//
//	Return: 		void
//--------------------------------------------------------
void billParts(int miles, int limit, int days, double overRate, double sizeRate, double& milesCharge, double& carCharge, double& tax, double& total) {
	const double TAX_RATE = 0.115;
	const double WEEKLY_RATE = 6.5;
	
	// SUVs have an unlimited rate. The easy way to test if its an 
	// SUV is to see if we passed a -1 as limit.
	if(limit != -1) {
		// so the limit is actually going to be that size's limit
		// per day
		limit = limit * days;
		
		if(miles > limit) {
			milesCharge = (miles - limit) * overRate;
			
			total = total + milesCharge;
		}
	} else {
		milesCharge = 0;
	}
	
	// so rented for more than 7 days has a lower weekly rate
	 if (days >= 7) {
		// so we want to pull out how many weeks the car was rented
		// away from the daily rate
		int weeks = 0;
		while( days >= 7) {
			// basically, subtract 7 from days til they're gone
			days = days - 7;
			weeks++;
		}
		
		// so now with the amount of weeks, we calculate that
		carCharge = ((WEEKLY_RATE * sizeRate) * weeks) + (days * sizeRate);
	}
	else {
		carCharge = days * sizeRate;
	}
	
	
	
	// tax will be the current tax rate * (milesCarge + carCharge)
	tax = (milesCharge + carCharge) * TAX_RATE;
	
	// calculate the bill total
	total = total + carCharge + tax;
}

//--------------------------------------------------------
//	Description: 	Displays the final bill
//	Input params: 	carsize, daysrented, milesdriven,
//					car carge, milesCharge, tax, totalbill
//
//	Return: 		void
//--------------------------------------------------------
void dispayBill(char carSize, int daysRented, int milesDriven, double carCharge, double milesCharge, double tax, double totalBill){
	cout << setw(15) << "Days Rented:" << setw(17) << daysRented << " days" << endl;
	
	if (carSize != 'S') {
		cout << setw(16) << "Miles Driven:" << setw(16) << milesDriven << " miles" << endl << endl;
	}
	
	cout << endl << "BILL" << endl;
	cout << fixed << showpoint << setprecision(2);
	cout << setw(13) << "Car Charge:" << setw(7) << "$" << setw(10) << carCharge << endl;
	if(milesCharge > 0) {
		cout << setw(17) << "Mileage Charge:" << setw(3) << "$" << setw(10) << milesCharge << endl;
	}
	
	cout << setw(6) << "Tax:" << setw(14) << "$" << setw(10) << tax << endl;
	cout << setw(20) << "-" << setfill('-') << setw(10) << '-' << setfill(' ') << endl;
	cout << setw(13) << "Total Bill:" << setw(7) << "$" << setw(10) << totalBill << endl;
	cout << endl;
}
