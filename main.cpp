#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gldraw.h>
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <type_traits>
#include "string"
#include "Matrix.h"
#include "MathTools.h"
#include "OEs.h"
#include "OrbitCall.h"

using namespace std;

int main() {

	// Demonstration to show it all working. using the MATLAB example
	double I = 0.715585;
	double RAAN = 1.0472;
	double AOP = 1.5708;
	double f = 0;
	double e = 0.4; // eccentricity
	double a = 12792.865; // semi major axis (km)
	int mu = 398600; // gravitational constant
	int Re = 6378; // radius of Earth(km)
	double pi = 3.14159265359;

	OEs demo;
	demo.set_OEs(a, e, f, RAAN, AOP, I);
	demo.OE2RV0();
	vector<vector<double>> rv = demo.return_RV0();
	vector<double> r0 = rv[0];
	vector<double> v0 = rv[1];

	int ti = 100; // timestep, sec
	int Tp = 4 * 3600; // Orbit period

	Matrix rs = F_and_G(Tp, ti, a, e, r0, v0);

	// Printing rs to the console
	for (int i = 0; i < (1 + Tp / ti); i++) {
		cout << "r = " << rs.dynamicMatrix[i][0] << " " << rs.dynamicMatrix[i][1] << " " << rs.dynamicMatrix[i][2] << endl;
	}


	////////////  Plotting //////////////////////////
	// Now drawing animation
	pangolin::CreateWindowAndBind("Main", 640, 480);
	glEnable(GL_DEPTH_TEST);

	// Define projection and initial Modelview matrix
	pangolin::OpenGlRenderState s_cam(
		pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
		pangolin::ModelViewLookAt(0, 0, 40, 0, 0, 0, pangolin::AxisY)
	);

	// Create interactive view in window
	pangolin::Handler3D handler(s_cam);
	pangolin::View& d_cam = pangolin::CreateDisplay()
		.SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f)
		.SetHandler(&handler);
	while (true) {
		for (int i = 0; i < (1 + Tp / ti); i++) { 

			// Clear screen and activate view to render into
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			d_cam.Activate(s_cam);

			// Render OpenGL Sphere
			glColor3f(1, 0, 0); // set the color of the brush - to be used for all further plots -- add this to the drawcircle plot
			GLUquadric* quad;
			quad = gluNewQuadric();
			glTranslatef(0, 0, 0);
			gluSphere(quad, 1, 20, 10); // loook up function definitions to set the size of the earth 


			double x = rs.dynamicMatrix[i][0];
			double y = rs.dynamicMatrix[i][1];
			double z = rs.dynamicMatrix[i][2];


			DrawCircle(rs.dynamicMatrix);
			//plot(x, y, z, 0, 0, 1); // inputs 4,5,6 are rbg
			plot(x, y, z, 1, 0, 1); // give coordinate for the pink 

			vector < vector<double>> p2(rs.dynamicMatrix);
			for (int j = 0; j < p2.size(); j++) {
				p2[j][0] = p2[j][0] * 2;
				p2[j][1] = p2[j][1] * 2;
				p2[j][2] = p2[j][2] * 2;
			}
			DrawCircle(p2);
			plot(x * 2, y * 2, z * 2, 0, 1, 1); // give coordinate for the pink 

			// Swap frames and Process Events
			pangolin::FinishFrame();

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		};
	}

	return 0;
}