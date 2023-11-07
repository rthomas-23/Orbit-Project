#include "MathTools.h"
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <type_traits>
#include "Matrix.h"

using namespace std;
int mu = 398600; // gravitational constant
int Re = 6378; // radius of Earth(km)
double pi = 3.14159265359;


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
		double f = 2 * pi - acos(((p / rmag) - 1) / e); // true anomaly, rad
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

Matrix F_and_G(int Tp, int ti, double a, double e, vector<double> r0, vector<double> v0) {

	// This function propogates an orbit around Earth, from perigee (E0=0), given:
	// - Tp: the time of the simulation
	// - OEs: inital orbital elements
	// It will return a matrix, rs, which will contain the position in x, y, z of the orbit.

	double dt0 = 0, dt = 0, E0 = 0;
	int mu = 398600;

	double n = sqrt(mu / (a * a * a)); // mean motion

	// initialising r and v arrays
	Matrix rs; // position vectors
	int rows = 1 + (Tp / ti);
	int columns = 3;
	rs.set_rows(rows);
	rs.set_columns(columns);
	rs.resize_matrix();
	Matrix vs; // velocity vectors
	vs.set_rows(rows);
	vs.set_columns(columns);
	vs.resize_matrix();

	rs.dynamicMatrix[0] = r0; // assigning the initial conditions
	vs.dynamicMatrix[0] = v0;

	int i = 1;
	double pi = 3.14159;
	double x0 = pi;
	double r0mag = magnitude(r0);
	while (dt < Tp)
	{
		dt = dt0 + (i * ti); // increment by ti sec
		double E = EccAnomalyNR(e, x0, n, dt);
		double dE = E - E0;

		double F = (1 - (a / r0mag) * (1 - cos(dE)));
		double G = dt - (sqrt((a * a * a) / mu) * (dE - sin(dE)));
		rs.dynamicMatrix[i] = add_vectors(scale_vector(r0, F), scale_vector(v0, G)); // [0]:rx, [1]:ry, [2]:rz

		double rmag = magnitude(rs.dynamicMatrix[i]);
		double Fdot = -(sqrt(mu * a) / (rmag * r0mag)) * sin(dE);
		double Gdot = 1 - (a / rmag) * (1 - cos(dE));
		vs.dynamicMatrix[i] = add_vectors(scale_vector(r0, Fdot), scale_vector(v0, Gdot)); // [0]:vx, [1]:vy, [2]:vz
		//cout << rs.dynamicMatrix[0][0] << endl;
		i = i + 1;
	}
	return rs;
}