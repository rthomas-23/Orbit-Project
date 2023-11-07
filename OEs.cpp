#include "OEs.h"
#include <vector>
#include "MathTools.h"

using namespace std;

OEs::OEs() {
	a = 0;
	e = 0;
	f = 0;
	RAAN = 0;
	AOP = 0;
	I = 0;
	//vector<double> OE = { a,e,f,RAAN,AOP,I };
	r0 = { 0,1,0 };
	v0 = { 0,0,0 };
}
void OEs::set_OEs(double a, double e, double f, double RAAN, double AOP, double I) {
	this->a = a;
	this->e = e;
	this->f = f;
	this->RAAN = RAAN;
	this->AOP = AOP;
	this->I = I;
	//vector<double> OE = { a,e,f,RAAN,AOP,I };
}

vector<double> OEs::return_OEs() {
	return { this->a, this->e, this->f, this->RAAN, this->AOP, this->I };
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

	int mu = 398600;
	double r_mag = a * (1 - e * e) / (1 + e * cos(f));
	std::vector<double> rpf = { r_mag * cos(f), r_mag * sin(f), 0 };
	std::vector<double> vpf = { (-mu * sin(f)) / (sqrt(mu * a * (1 - e * e))), (mu * (e + cos(f))) / (sqrt(mu * a * (1 - e * e))), 0 };
	Matrix R;
	R.set_columns(3);
	R.set_columns(3);
	R.resize_matrix();

	R.dynamicMatrix = { {(cos(RAAN) * cos(AOP) - sin(RAAN) * sin(AOP) * cos(I)), (-cos(RAAN) * sin(AOP) - sin(RAAN) * cos(AOP) * cos(I)), (sin(RAAN) * sin(I))},
					{(sin(RAAN) * cos(AOP) + cos(RAAN) * sin(AOP) * cos(I)), (-sin(RAAN) * sin(AOP) + cos(RAAN) * cos(AOP) * cos(I)),(cos(RAAN) * sin(I))},
					{(sin(AOP) * sin(I)), (cos(AOP) * sin(I)), (cos(I))} }; // The transpose of R

	for (int i = 0; i < 3; i++) {
		// compute R*rpf, R*vpf
		r0[i] = (R.dynamicMatrix[i][0] * rpf[0]) + (R.dynamicMatrix[i][1] * rpf[1]) + (R.dynamicMatrix[i][2] * rpf[2]);
		v0[i] = (R.dynamicMatrix[i][0] * vpf[0]) + (R.dynamicMatrix[i][1] * vpf[1]) + (R.dynamicMatrix[i][2] * vpf[2]);
	}
}

std::vector<std::vector<double>> OEs::return_RV0() {
	return { r0,v0 };
}