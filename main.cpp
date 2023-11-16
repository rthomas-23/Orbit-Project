#pragma once
#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gldraw.h>
#include <pangolin/pangolin.h>
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <type_traits>
#include "string"
#include "MathTools.h"
#include "OEs.h"
#include "OrbitCall.h"
#include "F_and_G.h"
#include <typeindex>
#include "GUI.h"
#include "WriteTextFile.h"

using namespace std;

// Global variables:
int Re = 6378; // radius of Earth (km)
double pi = 3.14159265359;


int main() { // NB: instead of plotting "n" orbits, initiate x objects (such as 5) and only allow 1-5 orbits in the GUI. Assign to each object at the start of the program
	
	int ti = 100;
	const int max_objects = 5;
	Matrix aa; Matrix bb; Matrix cc; Matrix dd; Matrix ee;
	Matrix Matrixes[max_objects] = { aa,bb,cc,dd,ee};

	int num_orbits=0;
	string orb_cmd_rqst = "Hello There... How many orbits do you wish to plot? Choose between 1 - 5.";
	num_orbits = enterData(num_orbits, orb_cmd_rqst, max_objects);
	cout << "OK! " << num_orbits << " orbits it is!\n" << endl;
	cout << "Let's specify each orbit: " << endl;

	for (int i = 0; i < num_orbits; i++) {
		double a = 0; double e = 0; double f=0; double RAAN=0; double AOP=0; double I=0; char colour='x';
		cout << "\nOrbit: " << i+1 << "..." << endl;

		string a_cmd_rqst = "Semi-Major axis, a (km): \nMust be greater than the radius of the Earth (6378km)\n";
		a = enterData(a, 'a', a_cmd_rqst, 6378);
		string e_cmd_rqst = "\nEccentricity, e: \nMust be 0 <= e < 1\n";
		e = enterData(e, 'e', e_cmd_rqst, 1);
		string f_cmd_rqst = "\nInitial True Anomaly, f (rad): \nMust be 0 <= e < 2*pi\n";
		f = enterData(f, 'ang', f_cmd_rqst, 2*pi);
		string RAAN_cmd_rqst = "\nRight Ascension of the Ascending Node, RAAN (rad): \nMust be 0 <= RAAN < 2*pi\n";
		RAAN = enterData(RAAN, 'ang', RAAN_cmd_rqst, 2 * pi);
		string AOP_cmd_rqst = "\nArgument of Perigee, AOP (rad): \nMust be 0 <= AOP < 2*pi\n";
		AOP = enterData(AOP, 'ang', AOP_cmd_rqst, 2 * pi);
		string I_cmd_rqst = "\nInclination, I (rad) : \nMust be 0 <= I < pi\n";
		I = enterData(I, 'ang', I_cmd_rqst,  pi);
		string colour_cmd_rqst = "\nSet the colour. Choose from: \nblue (b), red (r), green (g), yellow (y), pink (p), turquoise (t), white (w)\n";
		colour = enterData(colour, colour_cmd_rqst);

		Matrixes[i].set_OEs(a, e, f, RAAN, AOP, I);

		// Write File
		cout << "\nSummary...\n" << endl;
		string fileName = "Orbit_" + to_string(i+1) + ".txt";
		displayAndSaveOrbitalInformation(Matrixes[i].return_OEs()[0], Matrixes[i].return_OEs()[1], Matrixes[i].return_OEs()[2], Matrixes[i].return_OEs()[5],
			Matrixes[i].return_OEs()[3], Matrixes[i].return_OEs()[4], 398600, fileName);
		cout << "--> File Written! <--" << endl;
		cout << "---------------------------------------------------------------------------------------\n" << endl;

		// Continue orbit Calculations
		Matrixes[i].OE2RV0();
		Matrixes[i].calc_Tp();
		int rows = 1 + ceil(Matrixes[i].return_Tp() / ti);
		Matrixes[i].set_columns(3);
		Matrixes[i].set_rows(rows);
		Matrixes[i].resize_matrix();
		Matrixes[i] = F_and_G(rows, ti, Matrixes[i].return_OEs()[0], Matrixes[i].return_OEs()[1], Matrixes[i].return_RV0()[0], Matrixes[i].return_RV0()[1]);
		Matrixes[i].set_colour(colour);
	}


	////////////  Plotting //////////////////////////
	// Now drawing animation
	pangolin::CreateWindowAndBind("Main", 640, 480);
	glEnable(GL_DEPTH_TEST);

	// Define projection and initial Modelview matrix
	pangolin::OpenGlRenderState s_cam(
		pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 10000),
		pangolin::ModelViewLookAt(0, 0, 40, 0, 0, 0, pangolin::AxisY)
	);

	// Create interactive view in window
	pangolin::Handler3D handler(s_cam);
	pangolin::View& d_cam = pangolin::CreateDisplay()
		.SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f)
		.SetHandler(&handler);


	while (true) {

		// Clear screen and activate view to render into
		glClearColor(0, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		d_cam.Activate(s_cam);

		// Render OpenGL Sphere
		glColor3f(0, 0, 1); // set the color of the brush - to be used for all further plots -- add this to the drawcircle plot
		GLUquadric* quad;
		quad = gluNewQuadric();
		glTranslatef(0, 0, 0);
		gluSphere(quad, 1, 20, 10); // loook up function definitions to set the size of the earth 
			

		for (int i = 0; i < num_orbits; i++) {
			Matrixes[i].plotobject(ti);
		}

		// Swap frames and Process Events
		pangolin::FinishFrame();
		std::this_thread::sleep_for(std::chrono::microseconds(100));
	}
	return 0;
}