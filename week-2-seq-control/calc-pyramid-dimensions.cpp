#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

///////////////////////////////////////////////////
//	Name: 	Kim Holmes
//	Class: 	CS361 Control Structures
//	Input: 	Base length of pyramid
//			base height of pyramid
//
//	Output:	User inputs of height/length
//			volume of the pyramid
//			Slant height of pyramid
//			Surface area of pyramid
//
//	Desc.:	Input the dimensions of a pyramid,
//			and then it will calculate the volume,
//			slant height, and surface area of the
//			pyramid.
///////////////////////////////////////////////////

/*************************************************
*	@params: height, length, length squared
*	@desc: returns volume (vol) with formula
*			vol = 1/3 * base ^ (2) * h
/************************************************/
double calcVol(double length, double height, double lenSqr){
	double vol;
	
	vol = (1/3.0) * (lenSqr * height);
	
	return vol;
}

/*************************************************
*	@params: height, length, length squared
*	@desc: returns the surface area (SA) with
*			formula
*			SA = b(b+ sqrt(b^2 + (4*h^2))
/************************************************/
double calcSA(double length, double height, double lenSqr){
	double sa;
	
	sa = length * ( length + sqrt( lenSqr + 4 * pow(height, 2) ) );
	
	return sa;
}

/*************************************************
*	@params: height, length squared
*	@desc: returns the slant height (SH) of pyr
*			with formula
*			SH = sqrt(h^2 + (1/4) l^2
/************************************************/
double calcSH(double lenSqr, double height){
	double sh;
	
	sh = sqrt(pow(height, 2) + ( (1/4) * lenSqr ) );
	
	return sh;
}

/*************************************************
*	@params: volume, surface area, surface height,
				height, length
*	@desc: outputs the results of volume, surface
*			area, and slant height
/************************************************/
void showOutput(double vol, double sa, double sh, double height, double length){
	// output stuff with a precison of 2
	cout << fixed << showpoint << setprecision(2);
	
	cout << '\n' << "RESULTS:" << endl;
	cout << "For a Right Pyramid with" << endl;
	cout << setw(19) << "Base Length of" << setw(15) << length << " inches" << endl;
	cout << setw(15) << "Height of" << setw(19) << height << " inches" << endl;
	
	// output results
	cout << '\n' << "Pyramid Slant Height is" << setw(11) << sh << " inches" << endl;
	cout << "Pyramid Surface Area is" << setw(11) << sa << " inches" << endl;
	cout << "Pyramid Volume is" << setw(17) << vol << " cubic inches" << endl;
}

int main() {
	double length,
			height;
	
	
	cout << "Right Pyramid Calculations" << endl;
	cout << '\n' << "Enter the pyramid base length (in inches): ";
	cin >> length;
	cout << endl << "Enter the pyramid height (in inches): ";
	cin >> height;
	cout << endl;
	
	// set the b^2
	double lenSqr = pow(length,2);
	
	double vol = calcVol(length, height, lenSqr);
	double sa = calcSA(length, height, lenSqr);
	double sh = calcSH(lenSqr, height);
	
	showOutput(vol, sa, sh, height, length);
	
	return 0;
}
