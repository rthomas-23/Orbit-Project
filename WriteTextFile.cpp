#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void displayAndSaveOrbitalInformation(double semiMajorAxis, double eccentricity, double trueAnomaly, double inclination, double raan, double aop, int gravitationalConstant, const std::string& fileName) {
	double period = 2 * 3.14159265359 * sqrt(pow(semiMajorAxis, 3) / gravitationalConstant); // Period of oscillation
	double radiusOfOrbit = semiMajorAxis * (1 - eccentricity); // Radius of orbit at perigee

	// Display on console
	cout << "Orbital Elements and Information:" << endl;
	cout << "Semi-Major Axis (km): " << semiMajorAxis << endl;
	cout << "Eccentricity: " << eccentricity << endl;
	cout << "True Anomaly (rad): " << trueAnomaly << endl;
	cout << "Inclination (rad): " << inclination << endl;
	cout << "Right Ascension of Ascending Node (RAAN, rad): " << raan << endl;
	cout << "Argument of Perigee (rad): " << aop << endl;
	cout << "Orbital Period (s): " << period << endl;
	cout << "Radius of Orbit at Perigee (km): " << radiusOfOrbit << endl;

	// Save to file
	std::ofstream outFile(fileName);
	if (outFile.is_open()) {
		outFile << "Orbital Elements and Information:" << endl;
		outFile << "Semi-Major Axis (km): " << semiMajorAxis << endl;
		outFile << "Eccentricity: " << eccentricity << endl;
		outFile << "True Anomaly (rad): " << trueAnomaly << endl;
		outFile << "Inclination (rad): " << inclination << endl;
		outFile << "Right Ascension of Ascending Node (RAAN, rad): " << raan << endl;
		outFile << "Argument of Perigee (rad): " << aop << endl;
		outFile << "Orbital Period (s): " << period << endl;
		outFile << "Radius of Orbit at Perigee (km): " << radiusOfOrbit << endl;
		// ... [rest of the outFile << statements, similar to cout statements above] ...
		outFile.close();
	}
	else {
		cout << "Unable to open file: " << fileName << endl;
	}
}