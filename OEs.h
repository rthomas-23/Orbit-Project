#pragma once
#include <vector>
#ifndef OEs.h

class OEs {
public:
	OEs();
	double a;
	double e;
	double f;
	double RAAN;
	double AOP;
	double I;
	std::vector<double> r0;
	std::vector<double> v0;

	void set_OEs(double a, double e, double f, double RAAN, double AOP, double I);
	std::vector <double> return_OEs();
	void OE2RV0();
	std::vector<std::vector<double>> return_RV0();

private:

};
#endif