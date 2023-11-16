#pragma once
#include "OEs.h"
#include "MathTools.h"


Matrix F_and_G(int rows, int ti, double a, double e, vector<double> r0, vector<double> v0) {

	// This function propogates an orbit around Earth, from perigee (E0=0), given:
	// - Tp: the time of the simulation
	// - OEs: inital orbital elements
	// It will return a matrix, rs, which will contain the position in x, y, z of the orbit.

	double dt0 = 0, dt = 0, E0 = 0;
	int mu = 398600;

	double n = sqrt(mu / (a * a * a)); // mean motion

	// initialising r and v arrays
	Matrix rs; // position vectors
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
	//while (dt < Tp)
	int j = 0;
	while (j<rows-1)
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
		i = i + 1;
		j = j + 1;
	}
	return rs;
}
