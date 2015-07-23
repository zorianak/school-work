#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//--------------------------------------------------------
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//
//
//	Desc.:	Calculates how long it'll take to pay off
//			a credit card
//--------------------------------------------------------

int getPaymentChoice();
double getBalance();
double getRate();
double calcMonthPayment(double payRate, double balWithInt);
int calcPayTime(int payRate, double balance, double rate);



int main() {
	cout << "This program calculates how long it will take to pay off your ";
	cout << "credit card balance." << endl << endl;
	
	// get the desired rate
	int payRate = getPaymentChoice() * 10;
	cout << endl;
	
	// get the balance
	double balance = getBalance();
	cout << endl;
	
	// get annual interest rate
	double rate = getRate();
	
	// calculate the intiial payment
	int amntMonths = calcPayTime(payRate, balance, rate);
	
	cout << endl << "It will take " << amntMonths << " months to pay off the card";
	return 0;
}

//--------------------------------------------------------
//	Name: 	getPaymentChoice
//	Input: 	n/a
//	output: Prompts for 10/20/30% rate of payment
//	return: Returns double payment amount
//
//
//	Desc.:	prompts user for amount of payment to do
//--------------------------------------------------------
int getPaymentChoice() {
	int userChoice;
	
	while(userChoice > 3 || userChoice < 1) {
		cout << "What will your monthly payment be?" << endl;
		cout << '\t' << "1 - 10% of balance with interest" << endl;
		cout << '\t' << "2 - 20% of balance with interest" << endl;
		cout << '\t' << "3 - 30% of balance with interest" << endl;
		cout << "Enter choice from menu above: ";
		cin >> userChoice;
		
		// no need to re-prompt that it is wrong, due to how this
		// prompt is written
	}
	
	return userChoice;
}

//--------------------------------------------------------
//	Name:	getbalance
//	Input: 	n/a
//	output: Prompts for their beginning balance
//	return: returns the beginning balance
//
//
//	Desc.:	prompts user for beginning balance and validates
//--------------------------------------------------------

double getBalance() {
	double balance;
	const double minBal = 100;
	
	while(balance < minBal) {
		cout << "Enter your beginning balance: ";
		cin >> balance;
	}
	
	return balance;
}

//--------------------------------------------------------
//	Name: 	getRate
//	Input: 	n/a
//	output: Prompts for their annual interest rate
//	return: returns the monthly interest rate
//
//
//	Desc.:	Prompts for annual interest to calculate the
//			monthly rate and return that
//--------------------------------------------------------

double getRate() {
	double rate;
	const double minRate = 5,
				 maxRate = 25;
	
	while(rate > 25 || rate < 5) {
		cout << "Enter the credit card's annual interest rate: ";
		cin >> rate;
	}
	
	rate = (rate / 100.0) / 12.0;
	
	return rate;
}

//--------------------------------------------------------
//	Name:	calcMonthPayment
//	Input: 	payRate - the payment rate to make
//			balWithInt - the balance with interest charge
//	output: n/a
//	return: returns monthly payment
//
//
//	Desc.:	calculates and returns monthly payment
//--------------------------------------------------------
double calcMonthPayment(double payRate, double balWithInt){
	double amntPay = balWithInt * (payRate / 100);;
	const double minPayMonth = 50;
	
	if(balWithInt < minPayMonth) {
		return balWithInt;
	}
	else if(amntPay > minPayMonth){
		return amntPay;
	} else {
		return minPayMonth;
	}
	
}

//--------------------------------------------------------
//	Name:	calcPayTime
//	Input: 	payRate - the selected rate to pay
//			balance - the beginning balance
//			rate - the monthly rate
//	output: display month number, beginning balance,
//			interest charge, balance with interest, payment,
//			and ending balance for each month
//	return: retun number of months required to pay off card
//
//
//	Desc.:	calculates and displays how long it will take to
//			pay off this card
//--------------------------------------------------------
int calcPayTime(int payRate, double balance, double rate) {
	double interestCharge,
			balWithInt,
			endingBal,
			amntPay;
			
	int i = 1;
			
	// Loop through with a while loop, as we want to keep
	// looping until the balance is 0'd out
	
	cout << endl << "RESULTS:" << endl;
	cout << "-" << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
	cout << setw(17) << "Initial" << setw(12) << "Month's" << setw(13) << "Balance" << setw(8) << payRate << "%";
	cout << setw(10) << "End" << endl;
	cout << "Month" << setw(12) << "Balance" << setw(13) << "Interest" << setw(15) << "w/Interest";
	cout << setw(10) << "Payment" << setw(10) << "Balance" << endl;
	cout << "-" << setfill('-') << setw(65) << "-" << setfill(' ') << endl;
	
	while(balance > 0 ) {
		// Calculate the interest charge and balance with interest
		interestCharge = balance * rate;
		balWithInt = balance + interestCharge;
		
		// calculate the payment and adjust for monthly min
		amntPay = calcMonthPayment(payRate, balWithInt);
		
		// calculate ending balance
		endingBal = balWithInt - amntPay;
		
		cout << fixed << showpoint << setprecision(2);
		// Mont - Init. Bal - month's Int - Bal w/ Int - Payment - End Bal
		cout << setw(5) << i << setw(12) << balance << setw(13) << interestCharge;
		cout << setw(15) << balWithInt << setw(10) << amntPay << setw(10) << endingBal << endl;
		
		// set balance to the ending bal
		balance = endingBal;
		// increment counter
		i++;
	}
	
	// so i is going to be 1 more than we actually need due to 
	// incrementing it after we display the months, so subtract 1
	return i - 1;
}
