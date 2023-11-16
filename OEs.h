#pragma once
#include <vector>
#include "MathTools.h"
#include "OrbitCall.h"
#include <string>
#ifndef OEs_H
#define OEs_H
class OEs{
public:
	OEs();
	double a;
	double e;
	double f;
	double RAAN;
	double AOP;
	double I;
	static const int mu = 398600;
	char colour;
	double colourints[3] = { 1.0,1.0,1.0 };
	void set_colour(char c);
	std::vector<double> r0;
	std::vector<double> v0;

	void set_OEs(double a, double e, double f, double RAAN, double AOP, double I);
	std::vector <double> return_OEs();
	void OE2RV0();
	std::vector<std::vector<double>> return_RV0();

private:

};
#endif

class Matrix : public OEs {
public:
	Matrix();

	void set_rows(int x);
	void set_columns(int x);
	int num_rows;
	int num_columns;
	int i;
	double Tp;
	std::vector<std::vector<double>> dynamicMatrix;
	void resize_matrix();
	void calc_Tp();
	int return_Tp();

	void plotobject();

private:

};