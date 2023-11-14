#include "MathTools.h"
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <type_traits>
#include "OEs.h"

using namespace std;

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type // VARIADIC TEMPLATE. proceed if the type, T, is arithmetic (including double!)
magnitude(T a)
{
	if (a < 0) {
		a = a * -1; // if "a" is negative
	}
	return (a * a) / a;
}

template <typename T>
typename std::enable_if<std::is_same<T, std::vector<double>>::value, double>::type // VARIADIC TEMPLATE. proceed if the type, T, is a vector<double> 
magnitude(T a)
{
	double sum = 0;
	for (int i = 0; i < a.size(); i++)
	{
		sum += a[i] * a[i];
	}
	return sqrt(sum);
}

vector<double> cross_product(const vector<double>& vector1, const vector<double>& vector2) {
	if (vector1.size() != 3 || vector2.size() != 3) {
		std::cerr << "Both vectors must have exactly 3 components for cross product calculation." << std::endl;
		return vector<double>(3, 0.0);
	}

	vector<double> result(3);
	result[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
	result[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
	result[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
	return result;
}

double dot_product(std::vector<double> w, std::vector<double> x)
{
	double z = 0;
	for (uint8_t i = 0; i < x.size(); i++)
	{
		z += w[i] * x[i];
	}
	return z;
}

vector<double> RV2OE(vector< double> r, vector< double> v, int mu)
{
	double rmag = magnitude(r);
	double vmag = magnitude(v);

	double vmag2 = pow(vmag, 2);
	double a = 1 / ((2 / rmag) - ((vmag2) / mu)); // semi-major axis, km

	vector<double> h = cross_product(r, v); // angular momentum
	double hmag = magnitude(h);

	double e = sqrt(1 - ((hmag * hmag) / (mu * a)));

	double p = a * (1 - (e * e));

	//if (acos(((p / rmag) - 1) / e) < 0.001) {
	double f = 0; // true anomaly, rad
	//}
	if (dot_product(r, v) >= 0) {
		double f = acos(((p / rmag) - 1) / e); // true anomaly, rad
	}
	else if (dot_product(r, v) < 0) {
		double f = 2 * 3.14159 - acos(((p / rmag) - 1) / e); // true anomaly, rad
	}

	double I = acos(h[2] / hmag); // inclination, rad
	double RAAN = asin(h[0] / (hmag * sin(I))); // right ascencion of the ascending node, rad
	double AOP = asin(r[2] / (rmag * sin(I))) - f; // Arg. of perigee, rad

	return  { a,e,f,I,RAAN , AOP };
}

double EccAnomalyNR(double e, double x0, double n, int dt)
{
	double tol = 0.00001;
	double error = 99999;
	double sol = 0;
	while (magnitude(error) > tol) {
		sol = x0 - ((x0 - e * sin(x0) - n * dt) / (1 - e * cos(x0)));
		error = sol - x0;
		x0 = sol;
	}
	return sol;
}

vector<double> add_vectors(vector<double> a, vector<double> b) {
	// a and b must be the same size
	vector<double> result(a.size()); // create a vector of the same size as the inputs
	for (int i = 0; i < a.size(); i++) {
		result[i] = (a[i] + b[i]);
	}
	return result;
}

vector<double> scale_vector(vector<double>a, double s) {
	// s is a scale factor
	vector<double> result(a.size()); // create a vector of the same size as the inputs
	for (int i = 0; i < a.size(); i++) {
		result[i] = a[i] * s;
	}
	return result;
}