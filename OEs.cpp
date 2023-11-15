#include "OEs.h"
#include <vector>
#include "OrbitCall.h"
//#include "MathTools.h"

using namespace std;

OEs::OEs() {
	a = 0;
	e = 0;
	f = 0;
	RAAN = 0;
	AOP = 0;
	I = 0;
	r0 = { 0,1,0 };
	v0 = { 0,0,0 };
	colourints;

}
void OEs::set_OEs(double a, double e, double f, double RAAN, double AOP, double I) {
	this->a = a;
	this->e = e;
	this->f = f;
	this->RAAN = RAAN;
	this->AOP = AOP;
	this->I = I;
}
void OEs::set_colour(char a) {
	this->colour = a;
	     if (a == 'b') { colourints[0] = 0; colourints[1] = 0; colourints[2] = 1;} // blue
	else if (a == 'r') { colourints[0] = 1; colourints[1] = 0; colourints[2] = 0; } // red
	else if (a == 'g') { colourints[0] = 0; colourints[1] = 1; colourints[2] = 0; } // green
	else if (a == 'y') { colourints[0] = 1; colourints[1] = 1; colourints[2] = 0; } // yellow
	else if (a == 'p') { colourints[0] = 1; colourints[1] = 0; colourints[2] = 1; } // pink
	else if (a == 't') { colourints[0] = 0; colourints[1] = 1; colourints[2] = 1; } // turquoise
	else if (a == 'w') { colourints[0] = 1; colourints[1] = 1; colourints[2] = 1; } // white
	else if (a == 'o') { colourints[0] = 1; colourints[1] = 0.5; colourints[2] = 0; } // orange
}

vector<double> OEs::return_OEs() {
	return {this->a, this->e, this->f, this->RAAN, this->AOP, this->I };
}

void OEs::OE2RV0() {
	// This function updates the r0 and v0 vectors using the orbital elements.
	RAAN = this->RAAN;
	a = this->a;
	e = this->e;
	f = this->f;
	AOP = this->AOP;
	I = this->I;
	r0 = this->r0;
	v0 = this->v0;

	double r_mag = a * (1 - e * e) / (1 + e * cos(f));
	std::vector<double> rpf = { r_mag * cos(f), r_mag * sin(f), 0 };
	std::vector<double> vpf = { (-mu * sin(f)) / (sqrt(mu * a * (1 - e * e))), (mu * (e + cos(f))) / (sqrt(mu * a * (1 - e * e))), 0 };	

	vector<vector<double>> R = { {(cos(RAAN) * cos(AOP) - sin(RAAN) * sin(AOP) * cos(I)), (-cos(RAAN) * sin(AOP) - sin(RAAN) * cos(AOP) * cos(I)), (sin(RAAN) * sin(I))},
					{(sin(RAAN) * cos(AOP) + cos(RAAN) * sin(AOP) * cos(I)), (-sin(RAAN) * sin(AOP) + cos(RAAN) * cos(AOP) * cos(I)),(cos(RAAN) * sin(I))},
					{(sin(AOP) * sin(I)), (cos(AOP) * sin(I)), (cos(I))} }; // The transpose of R

	for (int i = 0; i < 3; i++) {
		// compute R*rpf, R*vpf
		r0[i] = (R[i][0] * rpf[0]) + (R[i][1] * rpf[1]) + (R[i][2] * rpf[2]);
		v0[i] = (R[i][0] * vpf[0]) + (R[i][1] * vpf[1]) + (R[i][2] * vpf[2]);
	}
}

std::vector<std::vector<double>> OEs::return_RV0() {
	return { r0,v0 };
}


Matrix::Matrix() : OEs() {
	num_rows = 0;
	num_columns = 0;
	dynamicMatrix = { {0}, {0} };
	i = 0;
}
void Matrix::set_rows(int x) {
	num_rows = x;
}
void Matrix::set_columns(int x) {
	num_columns = x;
}
void Matrix::resize_matrix() {
	dynamicMatrix.resize(num_rows);
	for (int i = 0; i < num_rows; i++) {
		dynamicMatrix[i].resize(num_columns);
	}
}

void Matrix::calc_Tp() {
	Tp = ceil(sqrt(4 * pow(3.14159265359, 2) * pow(magnitude(a), 3) / mu)); // Orbital period. Rounded up to the nearest integer
}
int Matrix::return_Tp() {
	return Tp;
}

void Matrix::plotobject(int ti) {
	if (i < this->num_rows) {
		double x = dynamicMatrix[i][0];
		double y = dynamicMatrix[i][1];
		double z = dynamicMatrix[i][2];
		cout << x << y << z << endl;
		plot(x, y, z, colourints[0], colourints[1], colourints[2]);
		DrawCircle(dynamicMatrix);
		i += 1;
	}
	else {
		i = 0;
		double x = dynamicMatrix[i][0];
		double y = dynamicMatrix[i][1];
		double z = dynamicMatrix[i][2];
		plot(x, y, z, colourints[0], colourints[1], colourints[2]);
		DrawCircle(dynamicMatrix);
	}
}