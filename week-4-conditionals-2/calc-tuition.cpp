#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//
//
//	Desc.:	Calculates tuition based upon degree type
//          and amount of credit hours
//--------------------------------------------------------

const double CREDIT_HR = 465,
			NON_DEGREE = 100,
			RATE_1 = .03,
			RATE_2_UG = .028,
			RATE_2_GRAD = .027,
			RATE_3_UG = .025,
			RATE_3_GRAD = .024,
			RATE_4_UG = .022,
			RATE_4_GRAD = .021,
			RATE_5 = .019;
			
const int LIMIT_1 = 3,
			LIMIT_2 = 9,
			LIMIT_3 = 14,
			LIMIT_4 = 18;

//--------------------------------------------------------
//	Desc: 	Determines rate to be used in for students'
//          tuition
//	Input: 	stuType - the type of student (grad, under-grad,
//          not degree seeking)
//          crHours - the amount of credit hours
//
//
//	Return:	rateUsed - the rate used to calculate tuition
//--------------------------------------------------------

double calcRate(char stuType, int crHours){
	double rateUsed;
	
	// determining the student type FIRST
	// will be faster than testing that
	// in addition to the rate, regardless
	// of having two rates the same
	if(stuType == 'g') {
		// cr.hr bracket 1
		if(crHours <= LIMIT_1)
			rateUsed = RATE_1;
		else if(crHours <= LIMIT_2)
			rateUsed = RATE_2_GRAD;
		else if(crHours <= LIMIT_3)
			rateUsed = RATE_3_GRAD;
		else if(crHours <= LIMIT_4)
			rateUsed = RATE_4_GRAD;
		else
			rateUsed = RATE_5;
	} else {
		if(crHours <= LIMIT_1)
			rateUsed = RATE_1;
		else if(crHours <= LIMIT_2)
			rateUsed = RATE_2_UG;
		else if(crHours <= LIMIT_3)
			rateUsed = RATE_3_UG;
		else if(crHours <= LIMIT_4)
			rateUsed = RATE_4_UG;
		else
			rateUsed = RATE_5;
	}
	return rateUsed;
}		

int main() {
	char stuType = 'u';
	int crHours = 0;
	
	cout << "Student Fees Calculation Program" << endl << endl;
	cout << "Student types choices:" << endl;
	cout << '\t' << "U - undergraduate" << endl;
	cout << '\t' << "G - graduate" << endl;
	cout << '\t' << "N - non-degree seeking" << endl << endl;
	
	cout << "Enter student type: ";
	cin >> stuType;
	cout << endl;
	
	// lets make that tolower for easier checks
	stuType = tolower(stuType);
	
    // If they are degree-seeking, then we need some logic
	if(stuType != 'n') {
		cout << "Enter number of credit hours enrolled in: " ;
		cin >> crHours;
		cout << endl;
		double	rateUsed = calcRate(stuType, crHours),
				studentFees = CREDIT_HR * crHours * rateUsed;
		cout << endl << endl << "Student Fees Summary" << endl << endl;
		cout << "Student Type:";
		
		// rather than assign a variable, just test for it - less processor
		if(stuType == 'g' ) {
			cout << setw(18) << "Graduate" << endl;
		} else {
			cout << setw(18) << "Under-graduate" << endl;
		}
		
		cout << "Credit Hours:" << setw(18) << crHours << endl;
		
		cout << "Rate Used:" << setw(20) << showpoint << setprecision(2) << rateUsed * 100 << "%" << endl << endl;
		cout << "Student Fees:" << setw(18) << fixed << showpoint << setprecision(2) << studentFees;
		
	} else {
		double studentFees = NON_DEGREE;
		cout << "Student Fees Summary" << endl << endl;
		cout << "Student Type:" << setw (19) << "Not degree seeking" << endl << endl;
		cout << "Student Fees:" << setw(19) << fixed << showpoint << setprecision(2) <<  NON_DEGREE;
	}
	
	return 0;
}
