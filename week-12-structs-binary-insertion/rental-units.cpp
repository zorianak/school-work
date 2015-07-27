#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

/* 
 * Records in RENTALS.TXT
 
 	data stored as:
 		* renter's phone, previous if unoccupied
 		* rent per month
 		* If rented
 		* Ordinal value of bool rented is stored in the txt

1. Display introduction
2. Prompt for using existing information or not
	- If existing, read from previous RENTALS.txt
		- Check if it exists
			- If not, present error message about file and prompt to exit or proceed w/o data
			- If yes, read from the file into an ARRAY OF RECORDS
				- all data in file is valid and formatted
				- Rented field bool is 2-step process
					1. Read int from file into a temp int var
					2. static_cast to convert to a bool and store in array
				- Keep track of number of rentals stored
					- error check not too many data lines in input file
					- Over 500 data lines will issue an error
						- Will not read more data records from file
						
3. After file data's dealt with, give a menu of choices:
	- mneumonic for each option
	- Show rentals
		- if empty array, error that there are none to display
		- Or show it in nice columns, one line per listing
		- show as per 2nd page pdf
	- Add rentals to array
		- add a new apartment to the array (if still room)
			- separate user-defined function to read each item for one record
		- Loop, adding things to the array until they are done, or the max of 500 has been entered
			- once array has 500 listings, do not ask to add more
			- MUST verify user input
				- separate function that validates each data field entred by user
				- Prompt, read, validation should all be in the function
					- If invalid, display error message of WHY
		- call each of three input data reading functions that reads one data item
			- as each reads and validates data, validated data will be returned to Add function to store
		- Required error checking:
			- Phone Number
				- 12 characters long, only digits w/ digits in correct location
					- wants 999-999-9999
			- Monthly rent
				- Posiitve, non-zero value
			- rented
				- is apartment currently rented (y/n)
				- Convert to bool before storing
	- Delete a rental
		- Iff array empty, display message that there are no apartments to delete
		- If has listings:
			- Display phone numbers of rentals as choices
			- Ask user for Phone Numbr of rental to delete
			- Read entered Phone Number and validate format
			- Find Phone Number in the array
			- If the Phone Number is found, delete the record from the ARRAY
			- Display a message confirming that the listing has been removed, or
			  that the number was not found
	- Exit the program
		- When exiting, program should ask whether to save/re-save data to RENTALS.TXT
			- Just overwrite teh original data file if yes
			- If not, just exit, but state that all changes will be lost
			
5. OOP not to be used yet, use lots of structs
 */
 
 // Struct for apartments needs to be set up globally
struct rental {
	string phone;
	double rent;
	bool rented;
};

bool useExistingFile();
bool readData(rental rentalUnits[], int MAX_RENTALS, int& amntRentals);

char doNext(rental rentalUnits[], int amntRentals);

void saveData(rental rentalUnits[], int amntRentals);
void exitOptions(rental rentalUnits[], int amntRentals);

void showRecords(rental rentalUnits[], int amntRentals);

void deleteRecords(rental rentalUnits[], int& amntRentals);

void addRecords(rental rentalUnits[], int& amntRentals, int MAX_RENTALS);

void insertRecords(rental rentalUnits[], string phoneNum, double rent, bool ifAvail, int& amntRentals);

int binarySearch(rental rentalUnits[], int amntRentals, string findNum);

string getPhone(string prompt);
double validRent(string prompt);

bool ifAvailable(string prompt);

int main() {
	// bools
	bool useExisting,
		 dataFileExists;
	
	// set up necessary apartment array
	const int MAX_RENTALS = 500;
	rental rentalUnits[MAX_RENTALS];
	
	int amntRentals = 0;
	
	char userAction,
		 doSave;
	
	cout << "Rental Manager" << endl;
	cout << "This allows you to change rental information." << endl << endl;
	
	// prompt for if they do or don't want to load existing data
	useExisting = useExistingFile();
	
	// so if useExisting set to true, read from file
	if(useExisting){
		dataFileExists = readData(rentalUnits, MAX_RENTALS, amntRentals);
		
		if(dataFileExists) {
			
			do {
				
				// so at this point we either have an empty array, or we 
				// have records
				// So now we want to prompt the user with what to do.
				userAction = doNext(rentalUnits, amntRentals);
				// easiest one to set up is to just exit
				if(userAction == 'E') {
					exitOptions(rentalUnits, amntRentals);
					return 0;
				} else if(userAction == 'A') {
					// add records
					addRecords(rentalUnits, amntRentals, MAX_RENTALS);
				} else if(userAction == 'D') {
					// remove records
					deleteRecords(rentalUnits, amntRentals);
				} else {
					// default to showing them
					showRecords(rentalUnits, amntRentals);
				}
			} while(userAction != 'E');
			
			
			
		} else {
			// if false is returned, then exit
			return 0;
		}
	} else {
		amntRentals = 0;
		do {
				
			// so at this point we either have an empty array, or we 
			// have records
			// So now we want to prompt the user with what to do.
			userAction = doNext(rentalUnits, amntRentals);
			// easiest one to set up is to just exit
			if(userAction == 'E') {
				exitOptions(rentalUnits, amntRentals);
				return 0;
			} else if(userAction == 'A') {
				// add records
				addRecords(rentalUnits, amntRentals, MAX_RENTALS);
			} else if(userAction == 'D') {
				// remove records
				deleteRecords(rentalUnits, amntRentals);
			} else {
				// default to showing them
				showRecords(rentalUnits, amntRentals);
			}
		} while(userAction != 'E');
	}
}

//--------------------------------------------------------
//	Description: 	Asks if user wants to use existing file
//	Input params: 	none
//	Output Params:	none
//
//	Return: 		useExisting - wehther or not to use
//					an existing file
//--------------------------------------------------------

bool useExistingFile(){
	bool useExisting = false;
	char userInput;
	while(toupper(userInput) != 'Y' && toupper(userInput) != 'N') {
		cout << "Load existing data from a file (Y/N)? ";
		cin >> userInput;
		
		// bad input, reprompt
		if(toupper(userInput) != 'Y' && toupper(userInput) != 'N') {
			cout << "Please enter Y for Yes or N for No." << endl;
		} else {
			if(toupper(userInput) == 'Y') {
				useExisting = true;
			}
		}
	}
	
	return useExisting;
}

//--------------------------------------------------------
//	Description: 	Validates the read data and puts it into
//					arrays
//	Input params: 	rentalUnits - rental array of units
//						read from file
//					MAX_RENTALS - max amount of rentals
//					amntRentals - the count of rentals
//	Output Params:	rentalUnits, amntRentals
//
//	Return: bool
//--------------------------------------------------------

bool readData(rental rentalUnits[], int MAX_RENTALS, int& amntRentals){
	const string FILENAME = "RENTALS.txt";
 	
 	double rent,
	 		tempRent;
 	string phoneNum,
	 		tempPhone,
			 key;
 	int rentedInitial,
	 	tempRentedIni,
		j = 1,
		i;
 	ifstream rentFile;
 	
 	char noFile;
 	
 	bool notSorted = true;
 	
 	rentFile.open(FILENAME.c_str());
 	
 	// able to open
 	if(rentFile){
 		// read data
 		while(rentFile && amntRentals < MAX_RENTALS) {
 			rentFile >> phoneNum >> rent >> rentedInitial;
 			
 			// insert with insertion sort
 			insertRecords(rentalUnits, phoneNum, rent, static_cast<bool>(rentedInitial), amntRentals);
//			cout << amntRentals;
			if(amntRentals == MAX_RENTALS ) {
 				// too many rentals!
 				cout << "Maximum amount of rentals reached. All further";
 				cout << " rental records will be ignored." << endl;
			}
			
			notSorted = true; 
		}
 		
 		return true;
	} else {
		cout << FILENAME << " does not exist!" << endl;
		
		while(toupper(noFile) != 'E' && toupper(noFile) != 'P') {
			cout << "(E)Exit or (P)Proceed? ";
			cin >> noFile;
			cout << endl;
			
			if(toupper(noFile) != 'E' && toupper(noFile) != 'P'){
				cout << "Please enter (E) to exit or (P) to proceed. " << endl;
			} else {
				if(toupper(noFile) == 'E') {
					// tell it exit to quit
					return false;
				} else {
					// send back true to proceed
					return true;
				}
			}
		}
	}
}

//--------------------------------------------------------
//	Description: 	Prompt user with the menu
//	Input params: 	rentalUnits - array of rentals (struct)
//					amntRentals - count of amntRentals
//	Output Params:	none
//
//	Return: 		doNext - what to do next
//--------------------------------------------------------

char doNext(rental rentalUnits[], int amntRentals) {
	char ch;
	
	if(amntRentals > 0) {
		// display ONLY if there is not empty array
		while(ch != 'S' && ch != 'A' && ch != 'D' && ch != 'E') {
			cout << "Please select an option: " << endl;
			cout << '\t' << "[S] - Show Rentals" << endl;
			cout << '\t' << "[A] = Add Rentals" << endl;
			cout << '\t' << "[D] - Delete Rentals" << endl;
			cout << '\t' << "[E] - Exit" << endl;
			cin >> ch;
			
			ch = toupper(ch);
			
			if(ch != 'S' && ch != 'A' && ch != 'D' && ch != 'E') {
				cout << endl << "Please select a valid option from the menu." << endl;
			}
		}
	} else {
		// display if empty array
		while(ch != 'A' &&  ch != 'E') {
			cout << "Please select an option: " << endl;
			cout << '\t' << "[A] = Add Rentals" << endl;
			cout << '\t' << "[E] - Exit" << endl;
			cin >> ch;
			
			ch = toupper(ch);
			
			if(ch != 'A' && ch != 'E') {
				cout << endl << "Please select a valid option from the menu." << endl;
			}
		}
	}
	
	
	return ch;
	
}


//--------------------------------------------------------
//	Description: 	Saves the sorted array into a text file
//	Input params: 	rentalUnits - array of rentals (struct)
//					amntRentals - count of rentals
//	Output Params:	none, file
//
//	Return: void
//--------------------------------------------------------

  void saveData(rental rentalUnits[], int amntRentals){
  	 // file name
  	 const string SAVEFILE = "RENTALS.txt";
  	 
  	 ofstream saveData;	// output stream var
  	 
  	 saveData.open(SAVEFILE.c_str());	// open for writing
  	 
  	 char skip = ' ';
  	 
  	 for(int i = 0; i < amntRentals-1; i++){
  	 	// write each to the file
  	 	saveData << rentalUnits[i].phone << skip << rentalUnits[i].rent << skip << rentalUnits[i].rented << endl;
	 }
	 
	 // close the file
	 saveData.close();
  }
  
//--------------------------------------------------------
//	Description: 	Displays options to exit
//	Input params: 	rentalUnits - array of rentals (struct)
//					amntRentals - count of amntRentals
//	Output Params:	none
//
//	Return: void
//--------------------------------------------------------
void exitOptions(rental rentalUnits[], int amntRentals) {
  	char doSave;
  	// prompt for them to save or not
	while(doSave != 'Y' && doSave != 'N') {
		cout << "Would you like to save (Y/N)? ";
		cin >> doSave;
		
		doSave = toupper(doSave);
		
		if(doSave != 'Y' && doSave != 'N') {
			cout << "Please enter Y to save, or N to not save." << endl;
		}
	}
	
	if(doSave == 'N') {
		cout << "All changes will be lost. Goodbye!" << endl;
	} else {
		// function to save
		saveData(rentalUnits, amntRentals);
	}
}

//--------------------------------------------------------
//	Description: 	Displays all records
//	Input params: 	rentalUnits - array of rentals (struct)
//					amntRentals - count of amntRentals
//	Output Params:	none
//
//	Return: void
//--------------------------------------------------------

void showRecords(rental rentalUnits[], int amntRentals) {
		// initial then loop through :o
		
		cout << setw(15) << "Phone Number" << setw(15) << "Monthly Rent" << setw(10) << "Status" << endl;
		cout << setw(3) << "" << setfill('-') << setw(12) << "" << setfill(' ') << setw(3) << "" << setw(12) << setfill('-');
		cout << "" << setfill(' ') << setw(4) << "" << setfill('-') << setw(9) << "" << setfill(' ') << endl;
		
		
		// loop through all and display
		for(int i = 0; i < amntRentals - 1; i++) {
			cout << setw(15) << rentalUnits[i].phone;
			
			cout << setw(15) << rentalUnits[i].rent;
			
			if(rentalUnits[i].rented == true) {
				cout << setw(10) << "rented" << endl;
			} else {
				cout << setw(13) << "available" << endl;
			}
			
		}
}

//--------------------------------------------------------
//	Description: 	Allows deletion of records
//	Input params: 	rentalUnits - array of rentals (struct)
//					amntRentals - count of amntRentals
//	Output Params:	rentalUnits, amntRentals
//
//	Return: void
//--------------------------------------------------------  
void deleteRecords(rental rentalUnits[], int& amntRentals) {
  	// this displays phone numbers
  	// Find the record by its phone number, and delete them
  	string toDelete;
  	
  	int deleteRec;
  	
  	bool notDeleted = true;
  	 
  	// if there are more than 0 first
  	if(amntRentals > 0) {
  		cout << "Phone numbers for current rentals:" << endl;
  	  	for(int i = 0; i < amntRentals - 1; i++) {
  	  		// display all phone numbers
  	  		cout << rentalUnits[i].phone << " ";
  	  		
  	  		if(i+1 % 5 == 0) {
  	  			cout << endl;
			}
		}
		cout << endl;
		toDelete = getPhone("Please enter the number for the rental to be deleted: ");
		
		// now we have to find this to be deleted and well... delete it!
		
		// binary search is generally the BEST option for actually searching for an 
		// item in an array. Take the highest and then the lowest, take their
		// midpoint, and compare it.
		deleteRec = binarySearch(rentalUnits, amntRentals, toDelete);
		if(deleteRec > -1) {
			// it was found
			// NOW THE REAL WORK
			// so at this point, we have the exact index to delete
			// and if we remove that, decrement everything
			
			for(int i = deleteRec; i < amntRentals - 1; i++) {
				// so set i equal to the one before it
				rentalUnits[i].phone = rentalUnits[i+1].phone;
				rentalUnits[i].rent = rentalUnits[i+1].rent;
				rentalUnits[i].rented = rentalUnits[i+1].rented;
			}
			
			amntRentals--;
			
		} else {
			cout << "The number " << toDelete << " could not be found." << endl;
		}
		
	} else {
		// if there aren't any rentals, display error messaging
		cout << "Cannot delete. There are no records to delete!" << endl;
	}
}

//--------------------------------------------------------
//	Description: 	Validates phone number
//	Input params: 	prompt - the prompt to display
//	Output Params:	none
//
//	Return: 		goodPhone - validated phone number
//--------------------------------------------------------
string getPhone(string prompt){
	string goodNum;
	bool inValid = true;
	// flush cin from all other input stuff
	cin.ignore();
	
	while(inValid) {
		cout << prompt;
		getline(cin, goodNum);
		
		// first check length, save some time
		if(goodNum.length() == 12) {
			inValid = false;
			// now we want to compare the input
			for(int i = 0; i < goodNum.length(); i++) {
				if(i == 3 || i == 7) {
					// should be our dashes
					if(goodNum[i] != '-') {
						inValid = true;
					}
				} else {
					// otherwise, test if its a digit
					if(!isdigit(goodNum[i])){
						inValid = true;
					}
				}
			}
		} else {
			cout << goodNum.length() << endl;
		}
		
		
		if(inValid) {
			cout << "You input " << goodNum << endl;
			cout << "Phone numbers must be formatted like so: XXX-XXX-XXXX, where the Xs are numbers. Please try again." << endl;
			goodNum = "";
		}
	}
	
	return goodNum;
}

//--------------------------------------------------------
//	Description: 	Searches for a particular phone number
//	Input params: 	rentalUnits - array of rentals (struct)
//					amntRentals - count of amntRentals
//					findNum - the string to find
//	Output Params:	none
//
//	Return: 		mid - the index where the string was 
//					found, or -1 if it was not found
//--------------------------------------------------------
int binarySearch(rental rentalUnits[], int amntRentals, string findNum) {
	int high,
		low,
		mid;
		
	
	// give some initial values
	high = amntRentals - 1;
	low = 0;
	mid = (high + low)/2;
	
	while((rentalUnits[mid].phone != findNum) && (low <= high)) {
		if(rentalUnits[mid].phone > findNum) {
			// current position is too high!
			high = mid - 1;
		} else {
			// current position is too low!
			low = mid + 1;
		}
		
		// now reset midpoint
		mid = (high + low)/2;
	}
	
	// now test if we found it
	if(rentalUnits[mid].phone == findNum) {
		return mid;
	} else {
		return -1;
	}
	
}

//--------------------------------------------------------
//	Description: 	Allows user to add records
//	Input params: 	rentalUnits - array of rentals (struct)
//					amntRentals - count of amntRentals
//					MAX_RENTALS - max num. rentals
//	Output Params:	amntRentals
//
//	Return: void
//--------------------------------------------------------
void addRecords(rental rentalUnits[], int& amntRentals, int MAX_RENTALS) {
	bool doneAdding = false;
	
	string newNum;
	
	int testNum;
	
	double rent;
	
	bool ifAvail;
	
	char ch;
	
	
	cout << "This allows you to add rentals." << endl;
	
	do {
		ch = ' ';
		
		// prompt and verify phone number
		newNum = getPhone("Please enter the phone number to add, formatted as XXX-XXX-XXXX, where the Xs are numbers: ");
		int testNum = binarySearch(rentalUnits, amntRentals, newNum);
		// verify that it's not already added
		if(testNum == -1) {
			
			rent = validRent("Please enter the monthly rent for the unit: ");
			
			ifAvail = ifAvailable("Is the unit currently rented (Y/N)? ");
			
			insertRecords(rentalUnits, newNum, rent, ifAvail, amntRentals);
			
			// ew have more units now
			amntRentals++;
			// prompt to exit
			while(ch != 'Y' && ch != 'N') {
				cout << "Continue to add rentals (Y/N)? ";
				cin >> ch;
				ch = toupper(ch);
				
				if(ch != 'Y' && ch != 'N') {
					cout << endl << "Please enter Y or N." << endl;
				}
			}
			
		} else {
			while(ch != 'Y' && ch != 'N') {
				cout << newNum << " is already associated with a rental. Would you like to try again (Y/N)? ";
				cin >> ch;
				ch = toupper(ch);
				
				if(ch != 'Y' && ch != 'N') {
					cout << endl << "Please enter Y or N." << endl;
				}
			}
		}
	} while(ch != 'N');
}

//--------------------------------------------------------
//	Description: 	Validates user input for rent
//	Input params: 	prompt - the prompt to be displayed
//	Output Params:	none
//
//	Return: 		goodRent - validated rent
//--------------------------------------------------------

double validRent(string prompt) {
	double goodRent = 0;
	do {
		cout << prompt;
		cin >> goodRent;
		
		if(goodRent <= 0) {
			cout << "Invalid input. Monthly rent must be a positive, non-zero value. Please try again." << endl;
		}
	} while(goodRent <= 0);
	
	return goodRent;
}

//--------------------------------------------------------
//	Description: 	Validates user input for if rental is
//					available
//	Input params: 	prompt - the prompt to be displayed
//	Output Params:	none
//
//	Return: 		ifAvailable - validated if available
//--------------------------------------------------------

bool ifAvailable(string prompt){
	bool ifAvailable;
	char ch;
	do {
		cout << prompt;
		cin >> ch;
		
		ch = toupper(ch);
		
		if(ch != 'Y' && ch != 'N') {
			cout << "Invalid input. Please try again." << endl;
		} else {
			if(ch == 'Y') {
				return true;
			} else {
				return false;
			}
		}
	}while(ch != 'Y' && ch != 'N');
}

//--------------------------------------------------------
//	Description: 	Inserts records into the struct array
//	Input params: 	rentalUnits - array of rentals (struct)
//					amntRentals - count of amntRentals
//					rent - the rent to be added
//					ifAvail - if rental is available
//					phoneNum - the phone number to be added
//	Output Params:	amntRentals, rentalUnits
//
//	Return: 		void
//--------------------------------------------------------

void insertRecords(rental rentalUnits[], string phoneNum, double rent, bool ifAvail, int& amntRentals) {
	int i;
	
	bool notSorted = true;
	if(amntRentals > 0) {
		i = amntRentals-1;
		while(notSorted && i > -1) {
			// so if hte one currently at i is less
			// than the phone we're at,
			// then we can just insert to the right
			// of i
			if(rentalUnits[i].phone < phoneNum) {
				// current i index is less than phoneNum,
				// so phoneNum goes to i+1
				
				// if its the last index, then that should put it final
				rentalUnits[i+1].phone = phoneNum;
				rentalUnits[i+1].rent = rent;
				rentalUnits[i+1].rented = ifAvail;
				
				notSorted = false;
			} else {
				// so if phone is greater than phoneNum, then we
				// need to shift it and go to the next index to compare
				
				// if i is equal to 0, just overwrite
				
				
				
					rentalUnits[i+1].phone = rentalUnits[i].phone;
					rentalUnits[i+1].rent = rentalUnits[i].rent;
					rentalUnits[i+1].rented = rentalUnits[i].rented;
					
				if(i == 0){
					rentalUnits[i].phone = phoneNum;
					rentalUnits[i].rent = rent;
					rentalUnits[i].rented = ifAvail;
					
					notSorted = false;
				} else {
				}
				i--;
			}
		}
	} else {
		// otherwise, we're start of it, and need to add one at 0
		rentalUnits[0].phone = phoneNum;
		rentalUnits[0].rent = rent;
		rentalUnits[0].rented = ifAvail;
	} 
	amntRentals++;
}


