#include "OrbitCall.h"
	

void DrawCircle(vector<vector<double>> points)
{

	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < points.size(); ii++)
	{
		glVertex3f(points[ii][0] / 1000, points[ii][1] / 1000, points[ii][2] / 1000);//output vertex 
	}
	glEnd();
}

void plot(double x, double y, double z, int r, int g, int b) {

	glColor3f(r, g, b);
	GLUquadric* satellite;
	satellite = gluNewQuadric();
	glPushMatrix();
	glTranslatef(x / 1000, y / 1000, z / 1000);
	gluSphere(satellite, 0.5, 20, 10);
	glPopMatrix();
}

