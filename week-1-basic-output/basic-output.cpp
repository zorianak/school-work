#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/* 
*	Student: Kim Holmes
*	Assignment: Week 1 Program 2
*
*	Input the number of shares, and price per share
*	
*	Output prompts for input and display the results
*	of inputting the number of shares and price per
*	share
*
*	Processes input for commission over min shares as
*		(total shares purchased - minimum shares) * the 
*		commission for each share over 100
*
*	Calculates total order by multiplying shares purchased
*		by the total per share plus the minimum order commission
*		plus the amount of over minimum commission 
 */

int main() {
	
	// Define constants for min shares (int), min order comission (f),
	// each share over minimum order(f), investor's name (str), investor's
	// initials (char)
	const int MIN_SHARES = 100;
	const float MIN_ORDER_COMM = 2.55;
	const float OVER_MIN_COMM = 0.02;
	const string INVESTOR_NAME = "Kim Holmes";
	const char INVESTOR_INITIALS_FIRST = 'K';
	const char INVESTOR_INITIALS_SECOND = 'H';
	
	// non-const variables totalPurchased (int), single share cost (f),
	// total cost (f), over minimum comission charged (f)
	int totalPurchased;
	float singleShareCost;
	float totalOrderCost;
	float overMinCommission;
	
	// output initial prompt
	std::cout << "Stock Purchase Invoice Program" << endl << endl;
	
	// input the amount and cost of shares
	std::cout << "Enter number of shares purchased: ";
	std::cin >> totalPurchased;
	std::cout << "Enter the price per share: ";
	std::cin >> singleShareCost;
	
	// find commission for over min
	overMinCommission = (totalPurchased - MIN_SHARES) * OVER_MIN_COMM;
	
	// total order cost is totalPurchased * singleShareCost + base commission
	// + over min comission
	totalOrderCost = (totalPurchased * singleShareCost) + MIN_ORDER_COMM + overMinCommission;
	
	
	// newline to put space between input and output
	std::cout << '\n';
	std::cout << "Investor:" << setw(20) << INVESTOR_NAME << " (" << INVESTOR_INITIALS_FIRST << INVESTOR_INITIALS_SECOND << ")" << endl;
	std::cout << "Shares purchased:" << setw(5) << totalPurchased << endl;
	std::cout << "Price per share:" << setw(7) << singleShareCost << endl;
	
	// format and output results
	std::cout << fixed << showpoint << setprecision(2);
	std::cout << '\n';	// put some distance between investor/results
	std::cout << "Cost for all shares" << setw(23) << totalPurchased * singleShareCost << endl;
	std::cout << "Commission for minimum order" << setw(14) << MIN_ORDER_COMM << endl;
	std::cout << "Commission for additional shares" << setw(10) << overMinCommission << endl;
	
	// show total order cost
	std::cout << " " << setw(34) << " " << setw(8) << setfill('-') << " " << setfill(' ') << endl;
	std::cout << "Total Billed to Investor Account:" << setw(9) << totalOrderCost << endl;
	
}
