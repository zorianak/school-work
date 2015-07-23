#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

/* File of credit hours for copmleted students called CREDITS.TXT

Has student's ID in 8-char string w/ 2 letters followed by 6 digits

Stauts - U for UG, G for Grad, A for Alumni

Number of completed credit


* Display short description of what this does

* Verify input exists - if not, exit immediately

* Read data from input file
	- if UG, call to convert credits completed to class level
	- Store student data into two separate parallel arrays

* 1st array has string-type ID number
* second has class level
	- store enumerated type value in second array, NOT integer
	
* If student is not UG, ID or class will not be saved anywhere

* Arrays can hold up to 1k items each
	- Count variable for both arrays, as they hold the same amount of things 
	
* Selection to sort both parallel arrays in descending order, based on ID
	- Strings in arrays can be compared same as njumbers, using less than/greater than
	
* Write data from sorted arrays into SORTED.TXT
	- ordinal value of the credit rating enum type is stored in data file. Enables 
	program to just write the data from enum type filed, with no conversion
	
* After sorting and storing, loop to display class level for specific students
	- First show all student ID numbers in the array (horizontal, 5 per line)
	- Prompt user for a student ID (or X to exit)
	- After reading ID, and before searching, error check the ID 
		- 2 letters and 6 digits
		- Do this with a loop, not by brute force against each individual character
		- can access individual characters within a string
		- If an invalid ID is entered, give error message explaining correct format
	- Use a binary search to assume ordered array is ascending order. Modify the searh for arrays that are in descending
	- If found, display corresponding class level in words for specific student. If not found, show proper error
	
* Lopo displaying student ID choices, asking for an ID number, and displaying the student's class level,
 until X is entered to exit*/
 
 // apaprently this has to be global to not blow up.
 enum classLevel { FRESH, SOPH, JUNIOR, SEN	};
 
 bool readData(string studentNum[], classLevel studentLevel[], int MAX_STUDENTS, int& amntStudents);
 
 void selectSort(string studentNum[], classLevel studentLevel[], int amntStudents);
 
 void saveSorted(string studentNum[], classLevel studentLevel[], int amntStudents);
 
 void displayStudents(string studentNum[], int amntStudents);
 
 string getFindStudent();
 
 int findStudent(string findMe, string studentNum[], classLevel studentLevel[], int amntStudents);
 
 void showOutput(string findMe, int foundLvl);

int main() {
	
	const int MAX_STUDENTS = 1000;
	
	string studentNum[MAX_STUDENTS];
	
	string findMe = "";
	
	classLevel studentLevel[MAX_STUDENTS];
	
	int amntStudents = 0,
		foundLvl;
	
	bool success;
	
	
	cout << "This will convert the number of completed credits for all Undergraduate students ";
	cout << "into class levels, and allow you to search for a student by their ID number." << endl << endl;
	
	success = readData(studentNum, studentLevel, MAX_STUDENTS, amntStudents);
	
	if(success){
		// sort the arrays
		selectSort(studentNum, studentLevel, amntStudents);
		
		// save them
		saveSorted(studentNum, studentLevel, amntStudents);
		
		// display students
		displayStudents(studentNum, amntStudents);
		
		do{
			findMe = "";	// reset to be safe// prompt for input
			findMe = getFindStudent();
			
			if(findMe != "X" && findMe != "x") {
				// not an exit
				// search for the student
				foundLvl = findStudent(findMe, studentNum, studentLevel, amntStudents);
				
				// ensure we got it good
				if(foundLvl > -1) {
					//output
					showOutput(findMe, studentLevel[foundLvl]);
					
				} else {
					// reprompt
					cout << "No student with ID " << findMe << " was found." << endl;
				}
			}
			
			
		} while(findMe != "X" && findMe != "x");
		
		
		
//		// test for exit
//		if(findMe != "X" || findMe != "x") {
//			
//		} 
	} else {
		return 5;
	}
	
	return 0;
}

//--------------------------------------------------------
//	Description: 	Validates the read data and puts it into
//					arrays
//	Input params: 	studentNum - array of studentNumbers
//					studentLevel - array fo student level
//					MAX_STUDENTS - const with how many students
//						can be in arrays
//					amntStudents - count of students
//	Output Params:	studentNum, studentLvl
//
//	Return: bool
//--------------------------------------------------------

 bool readData(string studentNum[], classLevel studentLevel[], int MAX_STUDENTS, int& amntStudents){
 	const string FILENAME = "CREDITS.txt";
 	
 	char stuType, ch;
 	string id;
 	int amntCredits;
 	ifstream creditFile;
 	
 	creditFile.open(FILENAME.c_str());
 	
 	if(creditFile){
 		while(creditFile){
 			creditFile >> id >> stuType >> amntCredits;
 			if(stuType == 'U'){
 				// undergrad student, do things
 				studentNum[amntStudents] = id;
 				
 				// store the class level by amount of credits
 				// None are specified, so chunks of 30 should be "right"
 				if(amntCredits < 30) {
 					studentLevel[amntStudents] = FRESH;
// 					cout << amntStudents << " " << studentNum[amntStudents] << endl;
				 } else if (amntCredits < 60) {
				 	studentLevel[amntStudents] = SOPH;
// 					cout << amntStudents << " " << studentNum[amntStudents] << endl;
				 } else if(amntCredits < 90) {
				 	studentLevel[amntStudents] = JUNIOR;
// 					cout << amntStudents << " " << studentNum[amntStudents] << endl;
				 } else {
				 	studentLevel[amntStudents] = SEN;
// 					cout << amntStudents << " " << studentNum[amntStudents] << endl;
				 }
				 
 				
			 amntStudents++;
			 }
			 
			 if(amntStudents > MAX_STUDENTS) {
			 	// exit out of loop - too many students now
			 	cout << "Too many students!" << endl;
			 	break;
			 }
		 }
		 // No need for an "else", as we will not worry about
		 // grads or alumni
		 
		 // we also want to decrement amntStudents, because
		 // we incremented one extra time
		 amntStudents--;
		 
		 // it opened successfully, we can continue
 		return true;
	 } else {
	 	cout << FILENAME << " does not exist!" << endl;
	 	return false;
	 }
 }
 
 
 //--------------------------------------------------------
//	Description: 	Select sorts through students into
//						desendign order
//	Input params: 	studentNum - array of studentNumbers
//					studentLevel - array fo student level
//					amntStudents - count of students
//	Output Params:	studentNum, studentLvl
//
//	Return: void
//--------------------------------------------------------

  void selectSort(string studentNum[], classLevel studentLevel[], int amntStudents){
  	int curTop,		// bottom of unsorted
  		tryIndx, 	// index to compare value to
  		minPos;		//position of smallest value
  		
  	string tempId;	// temp val for swapping
  	
  	classLevel tempLev;
  		
  	// loop through each item from top to bottom
  	for (curTop = 0; curTop < amntStudents - 1; curTop++) {
  		// put minimum pos. as the current first index
		minPos = curTop;
		// now find the next smallest index
		
		for(tryIndx = curTop + 1; tryIndx < amntStudents; tryIndx++) {
			// we want to sort in DESCENDING ,thuuus we just have to swap this c:
			if(studentNum[tryIndx] > studentNum[minPos])
				minPos = tryIndx;
		}
		// if the smallest isn't at curTop, swap with curTop
		if(minPos != curTop) {
			tempId = studentNum[curTop]; // put curTop in temp
			studentNum[curTop] = studentNum[minPos];	// put minPos in first idx
			studentNum[minPos] = tempId;	// put curTop in minPos
			// they're swapped!
			
			// swap for our other one, too
			tempLev = studentLevel[curTop];
			studentLevel[curTop] = studentLevel[minPos];
			studentLevel[minPos] = tempLev;
		}
		
//		cout << studentNum[curTop] << " " << studentLevel[curTop] << endl;
	}
	return;
  }
  
  
  //--------------------------------------------------------
//	Description: 	Saves the sorted array into a text file
//	Input params: 	studentNum - array of studentNumbers
//					studentLevel - array fo student level
//					amntStudents - count of students
//	Output Params:	none, file
//
//	Return: void
//--------------------------------------------------------

  void saveSorted(string studentNum[], classLevel studentLevel[], int amntStudents){
  	 // file name
  	 const string SAVEFILE = "SORTED.txt";
  	 
  	 ofstream saveData;	// output stream var
  	 
  	 saveData.open(SAVEFILE.c_str());	// open for writing
  	 
  	 char skip = ' ';
  	 
  	 for(int i = 0; i < amntStudents; i++){
  	 	// write each to the file
//  	 	cout << studentLevel[i] << skip;
  	 	saveData << studentNum[i] << skip << studentLevel[i] << endl;
	 }
	 
	 // close the file
	 saveData.close();
  }
  
  //--------------------------------------------------------
//	Description: 	Displays the students
//	Input params: 	studentNum - array of studentNumbers
//					amntStudents - count of students
//	Output Params:	none
//
//	Return: void
//--------------------------------------------------------

  void displayStudents(string studentNum[], int amntStudents) {
  	// loop through and display the students, 5 per line
  	for(int i = 0; i < amntStudents; i++) {
  		cout << studentNum[i] << " ";
		
		// test for endl
		if((i + 1) % 5 == 0) {
			cout << endl;
		}	
	}
  }
  
  //--------------------------------------------------------
//	Description: 	Gets user input for what student to find
//	Input params: 	none
//	Output Params:	none
//
//	Return: string findMe - student to find
//--------------------------------------------------------
   string getFindStudent() {
   		string findMe = "";
   		bool goodEntry = true;
   		
   		const int MAX_LENGTH = 8;
   		
   		do{
   			cout << endl << endl << "Enter ID number of student to find (or X to exit): ";
   			cin >> findMe;
   			
   			// uppercase it for ease of testing
//   			toupper(findMe);
   			
   			// first, test the length
   			
   			if(findMe.length() > MAX_LENGTH) {
   				cout << "Entry is too long!" << endl;
			} else if (findMe.length() < MAX_LENGTH){
				if(findMe == "X" || findMe == "x") {
					//exit
					goodEntry = true;
				
				} else {
						cout << "Entry is too short!" << endl;
					}
			 	
			} else {
				// test each individual now
	   			for(int i = 0; i < findMe.length(); i++){
	   				
	   				// first, test that we've not encountered a bad index
	   				
	   				if(goodEntry) {
	   					// test first two indices as chars
		   				if(i <= 1) {
		   					if(isalpha(findMe[i])) {
		   						goodEntry = true;
		   						
		   						// uppercase?
		   						findMe[i] = toupper(findMe[i]);
							} else {
								goodEntry = false;
							}
						} else {
							if(isdigit(findMe[i])) {
								goodEntry = true;
							} else {
								goodEntry = false;
							}
						}
					}
	   				
					// if this is set to false,
					// we have to break the loop because we found something bad
					// otherwise, itll go true
				}
			}
			
			if(!goodEntry) {
				cout << "Incorrect format for a student number. Student numberss begin with ";
				cout << "two letterse and are followed by six digits. Please try again." << endl;
			}
   			
		} while(!goodEntry);
   
   		return findMe;
   }
   
   //--------------------------------------------------------
//	Description: 	Finds the index in the array of the
//					student searched for
//	Input params: 	studentNum - array of studentNumbers
//					studentLevel - array fo student level
//					findMe - the student numbet to find
//					amntStudents - count of students
//	Output Params:	none
//
//	Return: infoPlace - where the info was!
//--------------------------------------------------------
int findStudent(string findMe, string studentNum[], classLevel studentLevel[], int amntStudents){
	// binary search through this all
	// so the size will be amntStudents
	// to return if not found
	const int NOT_FOUND = -1;
	
	// target is in findMe
	// we're searching through studentNum, and returning studentLevel
	
	// index where found
	int infoPlace = NOT_FOUND;
	int high, low, middle;		// target indices
	
	low = 0;	// lowest to search
	high = amntStudents - 1;	// upperbound
	
	while( (low <= high) && (infoPlace == NOT_FOUND)) {
		// get midpoint
		middle = (low + high) / 2;
		
		// since we have a list in descending order, we want to reverse
		// how we do binary search here
		if(findMe > studentNum[middle])	// target more than mid value
			high = middle - 1;
		else if(findMe < studentNum[middle]) // target less than mid value
			low = middle + 1;
		else
			infoPlace = middle;	// found it
	}
	
	return infoPlace;
}

//--------------------------------------------------------
//	Description: 	Displays the results of the search
//	Input params: 	findMe - student num searched for
//					foundLvl - the found student level
//	Output Params:	none
//
//	Return: 		none
//--------------------------------------------------------

 void showOutput(string findMe, int foundLvl) {
 	// so we show this depending on the found level
 	
 	cout << "The student with ID " << findMe << " is a ";
 	
 	switch(foundLvl) {
 		case 0:
 			cout << "freshman." << endl;
 			break;
 		case 1:
 			cout << "sophomore." << endl;
 			break;
 		case 2:
 			cout << "junior." << endl;
 			break;
 		default:
 			cout << "senior." << endl;
 			break;
	 }
 		
 }
