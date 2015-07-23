#include <iostream>
#include <iomanip>
//#include <cmath>
//#include <string>
//#include <cctype>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//
//
//	Desc.:	Calculates a monthly cable bill
//--------------------------------------------------------


// assign constants for things
const double BASIC_SERV = 43,
			PREF_SERV = 58,
			BASIC_BOX = 7.5,
			PREF_BOX = 11.25,
			HBO_COST = 9.99,
			DISCOUNT = 0.14;

//--------------------------------------------------------
//	Description: 	Computes and oupts final cable bill
//	Input params: 	isBasic = if basic account type
//					hasPremium - if they have HBO
//					isEmp - if to apply discount
//					boxes - amount of cable boxes
//					acctId - account ID
//
//	Return: none
//--------------------------------------------------------

void displayBill(bool isBasic, bool hasPremium, bool isEmp, int boxes, int acctId) {
	double monthlyRate = PREF_SERV,
		premChannels = 0,
		discount = 0,
		finalTotal = 0,
		subtotal = 0,
		boxFees = PREF_BOX;
		
	string serviceType = "Preferred Digital";
		
	// monthlyRate is initiated at the preferred level. If they have a basic account,
	// we can just reassign it to the basic rate. Also, we reassign the box fee
	// to being the basic rate.
	if(isBasic) {
		monthlyRate = BASIC_SERV;
		boxFees = BASIC_BOX;
		serviceType = "Basic Digital";
	}
	
	// If we have 2 or less boxes, we need to have a 0 fee. We have this init'd at the
	// value we actually want to multiply it by, which is great actually.
	if(boxes > 2 ) {
		boxFees = boxFees * (boxes - 2);
	} else {
		boxFees = 0;
	}
	
	// set up output
	cout << '\n' << setw(32) << "CABLEASTIC MONTHLY CABLE BILL" << '\n' << endl;
	cout << left << setw(19) << "Customer Id:" << acctId << endl;
	cout << setw(19) << "Service:" << serviceType << endl;
	cout << setw(19) << "Cable Boxes:" << boxes << endl;
	
	// If there are more than 4 boxes, display a warning. If there are less than
	// 2, let the user know they can have more. If 2-4 boxes, display
	// nothing.
	if (boxes > 4) {
		// this is what the warning will look like
		cout << '\n' << setw(19) << " " << "WARNING:" << endl;
		cout << setw(19) << " " << "Using more than 4 cable boxes may degrade your signal." << '\n' << endl;
	} else if (boxes < 2) {
		// this is what the warning will look like
		cout << '\n' << setw(19) << " " << "NOTE:" << endl;
		cout << setw(19) << " " << "Currently you have less than 2 cable boxes." << endl;
		cout << setw(19) << " " << "You may have up to 2 cable boxes for free." << '\n' << endl;
	}
	
	cout << fixed << showpoint << setprecision(2);
	cout << '\n' << right << "Monthly Rate:" << setw(14) << monthlyRate << endl;
	cout << "Cable Box Fees:" << setw(12) << boxFees << endl;
	
	// if they have HBO, then we want to show this
	if(hasPremium) {
		cout << "Premium Channels:" << setw(10) << HBO_COST << endl;
		subtotal = subtotal + premChannels;
	}
	
	// now we want to determine the subtotal (total before employee discount).
	subtotal = subtotal + monthlyRate + boxFees;
	
	// get discount amount
	if(isEmp) {
		discount = subtotal * DISCOUNT;
	}
	
	finalTotal = subtotal - discount;
	
	cout << setw(20) << '-' << setfill('-') << setw(8) << '-' << setfill(' ') << endl;
	cout << "Subtotal:" << setw(18) << subtotal << endl;
	cout << "Employee Discount:" << setw(9) << discount << endl;
	cout << setw(20) << '-' << setfill('-') << setw(8) << '-' << setfill(' ') << endl;
	cout << "Total:" << setw(21) << finalTotal << endl;
}

int main() {
	
	char acctTypeIn,
		 hboIn;

	int acctId = 0,
		cableBoxes = 0;
	
	bool hasPremium = false,
		 isBasic = false,
		 isEmp = false;
		 
	string empIn;
	
	cout << "CableTastic Bill Calculation Program" << '\n' << endl;
	cout << "Enter the customer id: ";
	cin >> acctId;
	cout << endl << "Service level ([B]asic, [P]referred)?: ";
	cin >> acctTypeIn;
	cout << endl << "Enter the number of cable boxes: " ;
	cin >> cableBoxes;
	cout << endl << "H = HBO premium channels" << endl;
	cout << "N = No premium channels" << endl;
	cout << "Premium channels (H/N)? ";
	cin >> hboIn;
	
	cout << endl << "Cabletastic employee? (yes or no, all lowercase): ";
	cin >> empIn;
	cout << endl;
				
	// so the assignment wants us to check for if its basic or preferred.
	// The thing here is that it is better to test a bool for either/or.
	acctTypeIn = toupper(acctTypeIn);
	hboIn = toupper (hboIn);
	
	if(acctTypeIn == 'B') {
		isBasic = true;
	}
	if (hasPremium == 'H') {
		hasPremium = true;
	}
	
	if (empIn == "yes") {
		isEmp = true;
	}
	
	displayBill(isBasic, hasPremium, isEmp, cableBoxes, acctId);
	return 0;
}
