#include "OrbitPlotting.h"
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <type_traits>
#include "Matrix.h"
#include "MathTools.h"
#include "OEs.h"

using namespace std;

// Defining variables
//double I = 0.715585;
//double RAAN = 0.9;
//double AOP = 1.5708;
//double f = 0;
//double e = 0.4; // eccentricity
//double a = 12792.865; // semi major axis(km)
//double	Tp = 4 * 3600; // time persiod of chosen orbit(s)
//int mu = 398600; // gravitational constant
//int Re = 6378; // radius of Earth(km)
//double pi = 3.14159265359;


int main()
{
	//double I = 0.715585;
	//double RAAN = 1.04719;
	//double AOP = 1.5708;
	//double f = 0;
	//double e = 0.4; // eccentricity
	//double a = 12792.865; // semi major axis(km)

	//OEs test;
	//test.set_OEs(a,e,f,RAAN,AOP,I);
	//vector<double> b = test.return_OEs();
	//for (int i = 0; i < 6; i++) {
	//	cout << b[i] << endl;
	//}
	//test.OE2RV0();
	//vector<vector<double>> c = test.return_RV0();
	//vector<double> rtest = c[0];
	//vector<double> vtest = c[1];
	//for (int i = 0; i < 3; i++) {
	//	cout << c[1][i]<<endl;
	//}


	///////////////////////////////////////
	// Orbital elements
	double I = 0.715585;
	double RAAN = 1.04719;
	double AOP = 1.5708;
	double f = 0;
	double e = 0.4; // eccentricity
	double a = 12792.865; // semi major axis(km)

	// Simulation set-up
	int Tp = 4 * 60 * 60; // time for simulation, sec
	int ti = 100; // time step, sec
	int mu = 398600; // gravitational constant
	int Re = 6378; // radius of Earth (km)
	double pi = 3.14159265359;

	OEs test;
	test.set_OEs(a, e, f, RAAN, AOP, I);
	test.OE2RV0();
	vector<double> r0 = test.return_RV0()[0];
	vector<double> v0 = test.return_RV0()[1];

	cout << "r0 and v0 for the given orbital elements = ..." << endl;
	for (int i = 0; i < 3; i++) {
		cout << "r = " << r0[i] << " v = " << v0[i] << endl;
	}

	Matrix rs = F_and_G(Tp, ti, a, e, r0, v0);

	for (int i = 0; i < (1 + Tp / ti); i++) {
		cout << "r = " << rs.dynamicMatrix[i][0] << " "<< rs.dynamicMatrix[i][1] <<" "<< rs.dynamicMatrix[i][2] << endl;
	}




	/*
	vector< double> r0 = { -5016.8, 2896.5, 5035.7 }; // km. ECI
	vector < double> v0 = { -4.2633, -7.3842,0 }; // km/sec
	double e = 0.4; // eccentricity
	double a = 12792.865; // semi major axis(km)

	Matrix ans;
	int Tp = 4 * 60 * 60;
	int ti = 100;
	int rows = 1 + (Tp / ti);
	int columns = 3;
	ans.set_rows(rows);
	ans.set_columns(columns);
	ans.resize_matrix();


	 ans = F_and_G(Tp, ti, a, e, r0, v0);


	for (int i = 0; i < rows; i++) {
		std::cout << ans.dynamicMatrix[i][0] << " " << ans.dynamicMatrix[i][1] << " " << ans.dynamicMatrix[i][2] << endl;;
	}
	*/

	//demo using the matrix class. i can modify the num of rows/columns 
	
	//Matrix A;
	//int rowsA = 10;
	//A.set_rows(rowsA);
	//A.set_columns(5);
	//cout << "rows/cols" << A.num_rows << " " << A.num_columns << endl;
	//A.resize_matrix(); // resize to "num_rows" and "num_columns"
	//cout << "size" << A.dynamicMatrix[9].size() << endl;

	cout << "hello there!!!";

	return 0;
}
