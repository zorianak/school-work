#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

///////////////////////////////////////////////////
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//	Input: 	Radius of coil loops
//			Turns of each coil
//			current from coils
//
//	Output:	Calcs magnetic field
//			One or two blank lines from reading all
//			inputs
//			data similar to format in sample
//
//	Desc.:	Input the turns, radius, and coil of
//			the coils, and then calculate the magnetic
//			field and vacuum permeability
///////////////////////////////////////////////////

/*************************************************
*	This user-defined function outputs the header
*	prior to prompting for user input.
/************************************************/

 void outputName() {
 	cout << setw(45) << "Mangetic Field within Helmholtz coils" << endl;
 	cout << setw(23) << "by" << endl;
 	cout << setw(28) << "Kim Holmes" << '\n' << endl;
 }
 
 /*************************************************
*	Input: user-defined coil turns, radius, current
*	Output: the magnetic flux
*	Desc.: This takes in the coil's turns, radius,
*			and current in order to calculate the 
*			magnetic flux.
/************************************************/
 
 double calcMagFlux(double turns, double radius, double current, const double VAC_PERM) {
 	double magFlux;
 	
 	// B = (4/5) ^ (3/2) * (unI / R)
 	magFlux = (pow((4/5),(3/2))) * ((VAC_PERM * turns * current) / radius);
 	
 	return magFlux;
 }
 
int main() {
	
	double turns,
			radius,
			current;
	const double VAC_PERM =  1.2566370614e-6;
	
	outputName();
	
	cout << "Enter the number of tunrns per coil: ";
	cin >> turns;
	cout << endl << "Enter the radius of the coils (in meters): ";
	cin >> radius;
	cout << endl << "Enter the current in the coils (in amperes): ";
	cin >> current;
	
	double magFlux = calcMagFlux(turns, radius, current, VAC_PERM);

	cout << '\n' << "RESULTS:" << endl;
	cout << setw(17) << "Turns per coil:" << setw(23) << turns << " turns" << endl;
	
	// output stuff with a precison of 3
	cout << fixed << showpoint << setprecision(3);
	cout << setw(22) << "Radius of the coils:" << setw(18) << radius << " meters" << endl;
	cout << setw(23) << "Current in the coils:" << setw(17) << current << " amps" << endl;
	
	// set our precision to sceintific notation
	cout << scientific << setprecision(5);
	cout << '\n' << setw(22) << "Vacuum Permeability:" << setw(18) << VAC_PERM << " tesla meter/ampere" << endl;
	cout << '\n' << setw(19) << "Magnetic Field:" << setw(21) << magFlux << " tesla" << endl;
	
	return 0;
}


