#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//
//
//	Desc.:	Calculates bill for monthly car rental
//--------------------------------------------------------

/* It now charges per day */
/* Discounts are now 6.3 * daily rate */
/* at over 30 days, 5% more discount */
/* tax is now 12.5% */

void validateSize(char& carSize, double& dailyRate);

int valMilesDays(string prompt);

void billParts(int& daysRented, double& carCharge, double& tax, double& total, int& weeksRented, int& monthsRented,
	double& weeklyRate, double& monthlyRate, double& dailyRate, double& rentalFee, double& totalWith30Day);

void dispayBill(int weeksRented, int daysRented, double rentalFee, double weeklyRate, double dailyRate,
			double tax, double totalBill, double monthlyRate, double totalWith30Day);

int getDaysInMonth(int month, int year);

int GetValidNumber(string description, int lower, int upper);

void getDate(int day, int month, int year);

int dayOfWeek(int day, int month, int year);

int maxDaysInMonth(int month, int year);

void getReturnDay(int& dropoffDay, int& month, int& year, int max_days, int daysHad);

void englishDay(int dayNum);

int main() {
	 // Define constants for all the car related things
	 const double COMPACT_FEE = 26.82,
	 			  MID_FEE = 29.91,
	 			  FULL_FEE = 33.79,
	 			  SUV_FEE = 105.22;
				  
	const int COMPACT_MILES = 20,
			  MID_MILES = 25,
			  FULL_MILES = 30,
			  MIN_YEAR = 2013,
			  MAX_YEAR = 2023,
			  MIN_MONTH = 1,
			  MAX_MONTH = 12;
		  
	char carSize = NULL;
		 
	
	do {
		// initiate these at 0: otherwise, it endlessly loops the next times this runs
		int daysRented = 0,
			milesDriven = 0,
			mileLim = 0,
			pickupYear = 0,
			pickupMon = 0,
			pickupDay = 0,
			dropoffYear = 0,
			dropoffMon = 0,
			dropoffDay = 0,
			max_days = 0,
			dayNum = 0,
			returnDay= 0,
			weeksRented = 0,
			monthsRented = 0;
	
		double carCharge = 0,
			   milesCharge = 0,
			   tax = 0,
			   totalBill = 0,
			   overageRate = 0,
			   dailyRate = 0,
			weeklyRate = 0,
			monthlyRate = 0,
			rentalFee = 0,
			totalWith30Day = 0;
		carSize = NULL;
		string firstName,
				dayPrompt,
				lastName,
				engDayPickup,
				engDayDropoff;
			 
		cout << "RentItNow Car Rental Bill Calculation Program" << endl << endl;
	
		validateSize(carSize, dailyRate);
		
		// get first and last name
		cout << "Enter customer first name: ";
		cin.ignore();
		getline(cin, firstName);
		cout << "Enter customer last name: ";
		// I need this for first name because it munches the \n, but
		// it doesn't seem to have that issue with lastname and
		// having it in seems to munch the first letter instead
//		cin.ignore();
		getline(cin, lastName);
		
		cout << endl;
		
		// get valid numer of days
		daysRented = GetValidNumber("Enter number of days rented (1-365): ", 1, 365);
		cout << endl;
		// snip out miles driven, as its now per day
		
		/// Get the date that the car was returned
		cout << "Enter the date of pick up below" << endl << '\t';
		dropoffYear = GetValidNumber("Enter pickup year (2013 - 2023): ", MIN_YEAR, MAX_YEAR);
		cout << '\t';
		dropoffMon = GetValidNumber("Enter pickup month (1-12): ", MIN_MONTH, MAX_MONTH);
		cout << '\t';
		
		max_days = maxDaysInMonth(dropoffMon, dropoffYear);
		dayPrompt = "Enter the pick up day (1-" + to_string(max_days) + "): ";
		
		dropoffDay = GetValidNumber(dayPrompt, 1, max_days);
		
		// determine int value for the day of the week it was dropped off
		dayNum = dayOfWeek(dropoffDay, dropoffMon, dropoffYear);
		cout << endl << endl;
		
		
		
		
		cout << "RENTAL DETAILS" << endl;
		cout << '\t' << left << setw(17) << "Customer:" << left << lastName << ", " << firstName << endl;
		
		cout << '\t' << setw(17) << "Car Size: ";
		// compact and miles over compact limit
		if (carSize == 'C') {
			cout  << setw(22) << left << "Compact" << endl;
			carCharge = COMPACT_FEE;
		} else if(carSize == 'M') {
			cout  << setw(22) << left << "Mid size" << endl;
			carCharge = MID_FEE;
		} else if(carSize == 'F') {
			cout  << setw(22) << left  << "Full size" << endl;
			carCharge = FULL_FEE;
		} else {
			cout  << setw(22) << left << "SUV size" << endl;
			carCharge =SUV_FEE;
		}
		
		// going to shove this into its own function, because main is getting
		// VERY messy right now
		cout << '\t' << setw(17) << "Pickup Date:";
		
		englishDay(dayNum);
		
		cout << ", " << dropoffMon << '/' << dropoffDay << '/' << dropoffYear << endl;
		
		cout << '\t' << setw(17) << "Days Rented:" << daysRented << endl;
		
		cout << '\t' << setw(17) << "Return Date:";
		
		// a new function to determine the day returned
		getReturnDay(dropoffDay, dropoffMon, dropoffYear, max_days, daysRented);
		// and then get it as a weekday
		englishDay(dropoffDay);
		cout << ", " << dropoffMon << '/' << dropoffDay << '/' << dropoffYear << endl;;
		
		billParts(daysRented, carCharge, tax, totalBill, weeksRented, monthsRented, weeklyRate, monthlyRate, dailyRate, rentalFee, totalWith30Day);
		//billParts(int daysRented, double& carCharge, double& tax, double& total, int& weeksRented, int& monthsRented,
	//int& weeklyRate, int& monthlyRate, int& dailyRate, int& rentalFee);

		// dispayBill(int weeksRented, int daysRented, double rentalFee, double weeklyRate, double dailyRate,
//			double tax, double totalBill, double monthlyRate)
		dispayBill(weeksRented, daysRented, rentalFee, weeklyRate, dailyRate, tax, totalBill, monthlyRate, totalWith30Day);
		
		// could use system pause, but I think this is more user friendly:
		cout << "Press any key to continue...";
		cin.sync();
		cin.ignore();
			
	} while(carSize != 'E');
	
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
	while(!(carSize == 'C' || carSize == 'M' || carSize == 'F' || carSize == 'S')  || !(carSize == 'E')) {
		cout << "Car sizes:" << endl;
		cout << setw(25) << "C - Compact size at $ " << COMPACT_RATE << " per day" << endl;
		cout << setw(21) << "M - Mid size at $ " << MID_RATE << " per day" << endl;
		cout << setw(22) << "F - Full size at $ " << FULL_RATE << " per day" << endl;
		cout << setw(16) << "S - SUV at $ " << SUV_RATE << " per day" << endl;
		cout << setw(19) << "E - Exit Program" << endl << endl;
		
		cout << "Enter the letter for the car size rented: ";
		cin >> carSize;
		// uppercase for easy testing
		carSize = toupper(carSize);
		
		// at the end of the loop, if it is still not valid, reprompt and inform user they
		// did not use valid input
		if(!(carSize == 'C' || carSize == 'M' || carSize == 'F' || carSize == 'S') && !(carSize == 'E')){
			cout << "Please enter a valid car size: " << endl;
		} else if (carSize == 'E') {
			// exit
			exit(0);
		} else {
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
		
	}
	
	
}

//--------------------------------------------------------
//	Description: 	Prompts and validates input
//	Input params: 	description - prompt
//					lower - lowest value for input
//					upper - highst value for input
//
//	Return: daysRented
//--------------------------------------------------------
int GetValidNumber(string description, int lower, int upper){
	int userInput;
	
	do {
		cout << description;
		cin >> userInput;
		if(userInput < lower || userInput > upper) {
			cout << "Input: " << userInput << " lower: " << lower << endl;
			cout << "Please enter a value between " << lower << " and " << upper << "." << endl;
		}
	}while(userInput < lower || userInput > upper);
	return userInput;
}
//--------------------------------------------------------
//	Description: 	Determines the day of the week
//	Input params: 	day - the actual date
//					month - month returned
//					year - year returned
//
//	Return: dayNum, numeric value for day car was rented
//--------------------------------------------------------
int dayOfWeek(int day, int month, int year){
	int dayNum = 0,
		additionFactor,
		sum;
	
	if(month <= 3) { // Before March
		year--;
	} 
	
	if(month == 1 || month == 5) {
		additionFactor = 0;
	} else if(month == 8) { // August
		additionFactor = 1;
	} else if(month == 3 || month == 11) { // March or Nov
		additionFactor = 2;
	} else if(month == 2 || month == 6) { // Feb or June
		additionFactor = 3;
	} else if(month == 10 || month == 12) { // October or Dec
		additionFactor = 4;
	} else if(month == 4 || month == 7) { // April or July
		additionFactor = 5; // October
	} else {
		additionFactor == 6;
	}
	
	sum = year + (year/4 ) - (year/100) + (year/400) + additionFactor + day;
	dayNum = sum % 7;
	return dayNum;
}

//--------------------------------------------------------
//	Description: 	Calculates charges on the bill
//	Input params: 	see output
//	Output params:	daysRented - the days rented, without months/weeks
//					carCharge - the total charge by car size
//					tax - the tax charged
//					total - the total bill
//					weeksRented - amount of weeks rented
//					monthsRented - how many months were rented
//					weeklyRate - weekly rate charge
//					monthlyRate - the discount for renting 30+ days
//					dailyRate - the rate for the amount of days
//					rentalFee - rentalFee, without monthly discount
//					totalWith30Day - the rentalFee without 30+ day discount
//
//	Return: 		void
//--------------------------------------------------------
void billParts(int& daysRented, double& carCharge, double& tax, double& total, int& weeksRented, int& monthsRented,
	double& weeklyRate, double& monthlyRate, double& dailyRate, double& rentalFee, double& totalWith30Day) {
		
	const double TAX_RATE = 0.125;
	const double WEEKLY_RATE = .063;
	const double MONTHLY_RATE = .005;
	// a temp to hold daysRented since we need it more than once
	int tempDays = daysRented;
	
	// so this changes completely...
	// first, let's determine how many months we rented
	while(daysRented > 7){
		weeksRented++;
		daysRented = daysRented - 7;
	}
	
//	daysRented = tempDays;
	
	// determine how many months, using the term for 30 days rented
	while(tempDays > 30) {
		monthsRented++;
		tempDays = tempDays - 30;
	}
	
	// determine weekly rate
	weeklyRate = (weeksRented * 7 * carCharge);
	// apply discount
	weeklyRate = weeklyRate - (weeklyRate * WEEKLY_RATE);
	
	// calculate the daily rate
	dailyRate = daysRented * carCharge;
	
	// rental fee is all the things combined now
	rentalFee = weeklyRate + dailyRate;
	
	// determine if monthly discount applied
	if(monthsRented > 0) {
		monthlyRate = rentalFee * MONTHLY_RATE;
		totalWith30Day = rentalFee - monthlyRate;
		// calculate tax
		tax = totalWith30Day * TAX_RATE;
		// and total it up
		total = tax + totalWith30Day;
		
	} else {
		totalWith30Day = 0;
		// calculate tax
		tax = rentalFee * TAX_RATE;
		// and total it up
		total = tax + rentalFee;
	}
	
}

//--------------------------------------------------------
//	Description: 	Displays the final bill
//	Input params: 	weeksRented - weeks that were rented
//					daysRented - days that were rented
//					rentalFee - total rental fee (weeklyRate + dailyRate)
//					weeklyRate - rate for weeks rented
//					dailyRate - Rate for days rented
//					tax - the total tax charged
//					totalBill - the total bill
//					monthlyRate - discount for having rented 30+ days
//					totalWith30Day - total, including monthlyRate discount
//
//	Return: 		void
//--------------------------------------------------------
void dispayBill(int weeksRented, int daysRented, double rentalFee, double weeklyRate, double dailyRate,
			double tax, double totalBill, double monthlyRate, double totalWith30Day){
	
	
	cout << endl << "BILL" << endl;
	cout << fixed << showpoint << setprecision(2);
	
	// weeks rented
	if(weeksRented != 0) {
		cout << right << setw(4) << "$" << setw(12) << weeklyRate << setw(7) << weeksRented << " week";
		if(weeksRented > 1) {
			cout << "s";
		}
		cout << endl;
	}
	
	// days rented
	cout << setw(4) << "$" << setw(12) << dailyRate << " +" << setw(5)<< daysRented << " day";
	if(daysRented > 1) {
		cout << "s";
	}
	cout << endl;
	cout << setw(4) << "-" << setfill('-') << setw(12) << "-" << setfill(' ') << endl;
	
	// show rental fee
	cout << setw(4) << "$" << setw(12) << rentalFee << setw(16) << "rental fee" << endl;
	
	// display if there's a monthly rebate
	if(monthlyRate > 0) {
		cout << setw(4) << "$" << setw(12) << monthlyRate << setw(21) << "30 day discount" << endl;
		cout << setw(4) << "$" << setw(12) << totalWith30Day << setw(25) << "total with discount" << endl;
	}
	cout << setw(4) << "$" << setw(12) << tax << " +" << setw(7) << "tax" << endl;
	cout << setw(4) << "-" << setfill('-') << setw(12) << "-" << setfill(' ') << endl;
	
	cout << setw(4) << "$" << setw(12) << totalBill << setw(11) << "total" << endl << endl;
	
	
}

//--------------------------------------------------------
//	Description: 	Calculates maximum amount of days in given month
//	Input params: 	month - numeric month value
//					year - numeric year value
//	Output params:	none
//
//	Return: 		max_days - the max # days of the month
//--------------------------------------------------------
int maxDaysInMonth(int month, int year) {
	int max_days;
	
	// test month to determine the max amount of days
		if(year % 4 == 0 && month == 2) {
			max_days = 29;
			
		} else if(month == 2) {
			max_days = 28;
		} else if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 
		|| month == 10 || month == 12) {
			max_days = 31;
		} else {
			max_days = 30;
		}
	
	return max_days;
}

//--------------------------------------------------------
//	Description: 	calculates the day the car was returned,
//					month it was returned, and year returned
//	Input params: 	max_days - max days in the month
//					daysHad - amount of days it was rented
//	Output params:	dropoffDay - the day dropped off
//					month - the month dropped off
//					year - year dropped off
//
//	Return: 		void
//--------------------------------------------------------
void getReturnDay(int& dropoffDay, int& month, int& year, int max_days, int daysHad) {
	
	// so we have to know what month it is.
	// Month will determine how much past max days in it
	
	// so we want to basically add the days that the car
	// is in the person's possession to the day that it
	// was picked up. THen take max days, compare, subtract
	// if necessary.
	
	// the hard part is handling multiple months and weeks :/
	
	// also, it can be held dec -> jan, so let's just pass
	// of them to compare...
	dropoffDay = dropoffDay + daysHad;
	
	// so while the dropoff days are higher than max
	// days, we need to subtract current max days,
	// increment the month (and year if month goes to
	// 1), subtract max days, and compare the new
	// values
	while(dropoffDay > max_days) {
		// so subtract original max_days
		dropoffDay = dropoffDay - max_days;
		
		// make sure it's not december
		if(month < 12) {
			month++;
		} else {
			month = 1;
			year++;
		}
		
		// and now get a new value for max_days
		max_days = maxDaysInMonth(month, year);
	}
}

//--------------------------------------------------------
//	Description: 	outputs in english the day by number
//	Input params: 	dayNum - numeric value of hte day in the week
//	Output params:	none
//
//	Return: 		void
//--------------------------------------------------------
void englishDay(int dayNum) {
	switch(dayNum) {
		case 0:
			cout << "Sunday";
			break;
		case 1:
			cout << "Monday";
			break;
		case 2:
			cout << "Tuesday";
			break;
		case 3:
			cout << "Wednesday";
			break;
		case 4:
			cout << "Thursday";
			break;
		case 5:
			cout << "Friday";
			break;
		default:
			cout << "Saturday";
			break;
	}
}

