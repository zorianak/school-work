#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//
//	Desc:	Determins IRS 1040 logic
//
//	Input: 	Num of exemptions
//			Adjusted Gross Income
//			Filing status
//				1 Single
//				2 Married, joint
//				3 head of house
//				4 Qualifying widow, married
//				5 filing separately
//
//	Output:	Calcs magnetic field
//			One or two blank lines from reading all
//			inputs
//			data similar to format in sample
//
//--------------------------------------------------------



const double LINE_TWO_AMNT = 3950,
			 LINE_SIX_AMNT_NOT_SEP = 2500,
			 LINE_SIX_AMNT_SEP = 1250,
			 LINE_SEVEN_AMNT = 0.02;

//--------------------------------------------------------
//	Description:	Function determines if over AGI limit 
//					for Line 6
//	Input params:	overLimit - amnt over limit
//					filingStatus - filing status
//	Returns:		amount over AGI
//--------------------------------------------------------

int calcAgi(double overLim, int filingStatus) {
	double agi = 0;
	
	// if it is less than 122500 and not sep, then calc
	if(overLim < 122500 && filingStatus != 5) {
		// not filing sep, AGI is low enough
		agi = overLim / LINE_SIX_AMNT_NOT_SEP;	
	} else if( overLim < 61250 && filingStatus == 5) {
		// filing sep, AGI low enough
		agi = overLim / LINE_SIX_AMNT_SEP;
	}
	
	return ceil(agi);
}

int main() {
	int filingStatus,
		exemptions;
		
	double gross;
	
	cout << "Enter the number of exeptions claimed: ";
	cin >> exemptions;
	cout << endl << "Enter your Adjusted Gross Income (1040, line 38): ";
	cin >> gross;
	cout << endl << "1 - Single" << endl;
	cout << "2 - Married, Filing Jointly" << endl;
	cout << "3 - Head of Household" << endl;
	cout << "4 - Qualifying Widow(er)" << endl;
	cout << "5 - Married, Filing Separately" << endl;
	cout << "Enter your filing status from above (1-5): ";
	cin >> filingStatus;
	
	cout << setw(25) << "Eduction for Exemptions Worksheet" << '\n' << endl;
	
	// calculate line 2
	double lineTwo = exemptions * LINE_TWO_AMNT;
	
	// check to see if Line 1 is satisfied and can exit
	string filingStatusDesc;
	double limit;
	
	switch(filingStatus) {
		case 1 : 
			filingStatusDesc = "(single)           ";
			limit = 254200;
			break;
		case 2 :
			filingStatusDesc = "(filing joint)     ";
			limit = 305050;
			break;	
		case 3 :
			filingStatusDesc = "(head of household)";
			limit = 279650;
			break;
		
		case 5 : 
			filingStatusDesc = "(filing separately) ";
			limit = 152252;
			break;
			
		default :
			filingStatusDesc = "(widow(er))        ";
			limit = 305050;
	}
	
	// If your gross is greater than limits, you're done.
	cout << fixed << showpoint << setprecision(2);
	if(gross < limit) {
		cout << "1." << '\t' << "AGI is not over filing status amount" << endl;
		cout << "2." << '\t' << "Exemptions claimed ( " << exemptions << " x " << LINE_TWO_AMNT << "):" << setw(15) << lineTwo << endl;
		cout << '\n' << "***Enter amount from worksheet line 2 on form 1040 line 42"<< endl;
		return 2;
	} 
	
	cout << "1." << '\t' << "AGI is over filing status amount" << endl;
	cout << "2." << '\t' << "Exemptions claimed ( " << exemptions << " x " << LINE_TWO_AMNT << "):" << setw(21) << lineTwo << '\n' << endl;
	
	
	// Line 3 - show adjusted gross income
	cout << "3." << '\t' << "Adjusted gross income:" << setw(33) << gross << endl;
	cout << "4." << '\t' << "Filing status limit " << filingStatusDesc << setw(16) << limit << endl;
	cout << "" << setfill('-') << setw(63) << "" << setfill(' ') << endl;
	
	// Line 5 - subtract L4 from L3, this is amount over limit
	double amntOver = gross - limit;
	cout << "5." << '\t' << "AGI amount over limit:" << setw(33) << amntOver << endl;
	
	// L6 - test for AGI too high
	int agiResult = calcAgi(amntOver, filingStatus);
	// if we get a result more than 0, keep on keepin' on.
	// Otherwise, end.
	if(agiResult == 0 ) {
		cout << '\n' << "AGI is too high. No exeptions allowed." << endl;
		cout << '\n' << "***Enter 0.0 on form 1040 line 42"<< endl;
		return 6;
	}
	
	cout << "6." << '\t' << "Division result:" << setw(39) << agiResult << endl;
	cout << "" << setfill('-') << setw(63) << "" << setfill(' ') << endl;
	
	// Line 7 - Mult. L6 by .02, enter rounded up to 3 places
	double lineSev = agiResult * LINE_SEVEN_AMNT;
	
	cout << "7." << '\t' << "Multiply line 6 by 2%:" << setw(33) << setprecision(3) << lineSev << endl;;
	
	// Line 8 - mult. L2 by L7
	double lineEig = lineTwo * lineSev;
	cout << "8." << '\t' << "Multiply line 2 by line 7:" << setw(29) << setprecision(2) << lineEig << endl;
	cout << "" << setfill('-') << setw(63) << "" << setfill(' ') << endl;
	
	// Line 9 - Subtract line 8 from line 2
	double lineNine = lineTwo - lineEig;
	cout << "9." << '\t' << "Subtract line 8 from line 2:" << setw(27) << lineNine << '\n' << endl;
	
	cout << "***Enter amount from worksheet line 9 on form 1040 line 42" << endl;
	return 0;
}
