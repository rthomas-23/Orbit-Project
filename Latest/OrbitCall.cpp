//#include "OrbitCall.h"
//
//void DrawCircle(float cx, float cy, float r, int num_segments)
//{
//    float theta = 2 * 3.1415926 / float(num_segments);
//    float c = cosf(theta);//precalculate the sine and cosine
//    float s = sinf(theta);
//    float t;
//
//    float x = r;//we start at angle = 0 
//    float y = 0;
//
//    glBegin(GL_LINE_LOOP);
//    for (int ii = 0; ii < num_segments; ii++)
//    {
//        glVertex2f(x + cx, y + cy);//output vertex 
//
//        //apply the rotation matrix
//        t = x;
//        x = c * x - s * y;
//        y = s * t + c * y;
//    }
//    glEnd();
//}
//
//void plot(double x, double y, double z, int r, int g, int b) {
//
//    glColor3f(r, g, b);
//    GLUquadric* satellite;
//    satellite = gluNewQuadric();
//    glTranslatef(x / 1000, y / 1000, z / 1000);
//    gluSphere(satellite, 0.5, 20, 10);
//
// 
//
//}


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
