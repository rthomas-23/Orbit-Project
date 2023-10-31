// OrbitPlotting.cpp : Defines the entry point for the application.
//

#include "OrbitPlotting.h"
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <type_traits>

#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gldraw.h>



#include "Matrix.h"

using namespace std;

// Defining variables
double I = 0.715585;
double RAAN = 0.9;
double AOP = 1.5708;
double f = 0;
double e = 0.4; // eccentricity
double a = 12792.865; // semi major axis(km)
double	Tp = 4 * 3600; // time persiod of chosen orbit(s)
int mu = 398600; // gravitational constant
int Re = 6378; // radius of Earth(km)
double pi = 3.14159265359;

// F and G setup
vector< double> r0 = { -5016.8, 2896.5, 5035.7 }; // km. ECI
vector < double> v0 = { -4.2633, -7.3842,0 }; // km/sec
int ti = 100; // time step



template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type // VARIADIC TEMPLATE. proceed if the type, T, is arithmetic (including double!)
magnitude(T a)
{
	if (a < 0) {
		a = a * -1; // if "a" is negative
	}
	return (a*a)/a;
}

template <typename T>
typename std::enable_if<std::is_same<T, std::vector<double>>::value, double>::type // VARIADIC TEMPLATE. proceed if the type, T, is a vector<double> (including double!)
magnitude(T a)
{
	double sum = 0;
	for (int i = 0; i < a.size(); i++)
	{
		sum += a[i] * a[i];
	}
	return sqrt(sum);
}

vector<double> crossProduct(const vector<double>& vector1, const vector<double>& vector2) {
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

	vector<double> h = crossProduct(r, v); // angular momentum
	double hmag = magnitude(h); 
	
	double e = sqrt(1 - ((hmag*hmag) / (mu * a)));

	double p = a * (1 - (e * e));

	if (acos(((p / rmag) - 1) / e) < 0.001) {
		double f = 0; // true anomaly, rad
	} else if (dot_product(r, v) >= 0) {
		f = acos(((p / rmag) - 1) / e); // true anomaly, rad
	}
	else if (dot_product(r, v) < 0) {
		f = 2 * pi - acos(((p / rmag) - 1) / e); // true anomaly, rad
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
		 sol = x0 - ((x0 - e * sin(x0) - n*dt) / (1 - e * cos(x0)));
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
	 /////////////// MAKE THIS OPERATOR OVERLOADED IN "MATRIX" class
 }
 vector<double> scale_vector(vector<double>a, double s) {
	 // s is a scale factor
	 vector<double> result(a.size()); // create a vector of the same size as the inputs
	 for (int i = 0; i < a.size(); i++) {
		 result[i] = a[i] * s;
	 }
	 return result;
	 ////// ALSO MAKE THIS OPERATOR OVERLAODED
 }

int main()
{


	vector<double> OEs = RV2OE(r0, v0, mu);
	a = OEs[0];
	e = OEs[1];
	double dt0 = 0, dt = 0, E0 = 0;

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

	pangolin::CreateWindowAndBind("Main", 640, 480);
	glEnable(GL_DEPTH_TEST);

	// Define Projection and initial ModelView matrix
	pangolin::OpenGlRenderState s_cam(
		pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.2, 100),
		pangolin::ModelViewLookAt(0, 0, 20, 0, 0, 0, pangolin::AxisY)
	);

	// Create Interactive View in window
	pangolin::Handler3D handler(s_cam);
	pangolin::View& d_cam = pangolin::CreateDisplay()
		.SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f)
		.SetHandler(&handler);

	int i = 1;
	double x0 = pi;
	double r0mag = magnitude(r0);
	while (dt < Tp)
	{
		dt = dt0 + (i * ti); // increment by ti sec
		double E = EccAnomalyNR(e, x0, n, dt);
		double dE = E - E0;

		double F = (1 - (a / r0mag) * (1 - cos(dE)));
		double G = dt - (sqrt((a*a*a)/mu) * (dE - sin(dE)));
		rs.dynamicMatrix[i] = add_vectors(scale_vector(r0, F), scale_vector(v0, G));

		double rmag = magnitude(rs.dynamicMatrix[i]);
		double Fdot = -(sqrt(mu * a) / (rmag * r0mag)) * sin(dE);
		double Gdot = 1 - (a / rmag) * (1 - cos(dE));
		cout << "F,G,FDOT,GDOT " << F << " " << G << " " << Fdot << " " << Gdot << endl;
		vs.dynamicMatrix[i] = add_vectors(scale_vector(r0, Fdot), scale_vector(v0, Gdot));

		i = i + 1;
		cout << "time = " << dt << " i = "<< i<< endl;

		
	}




	for (int i = 0; i < rows; i++) {
		std::cout << rs.dynamicMatrix[i][0] << " " << rs.dynamicMatrix[i][1] << " " << rs.dynamicMatrix[i][2] << endl; // this is x y z coordinate, need to plot at time t
	}


	//demo using the matrix class. i can modify the num of rows/columns 
	
	Matrix A;
	int rowsA = 10;
	A.set_rows(rowsA);
	A.set_columns(5);
	cout << "rows/cols" << A.num_rows << " " << A.num_columns << endl;
	A.resize_matrix(); // resize to "num_rows" and "num_columns"
	cout << "size" << A.dynamicMatrix[9].size() << endl;

	/*for (int i = 0; i < rows; i++) {
		std::cout << A.dynamicMatrix[i][0] << " ";
	}*/

	//int size = 5; // Define the initial size

	//// Allocate memory for a dynamic array using new
	//int* dynamicArray = new int[size,size];

	//for (int i = 0; i < size; i++) {
	//	dynamicArray[i,0] = i * 2;
	//}

	//for (int i = 0; i < size; i++) {
	//	std::cout << dynamicArray[i] << " ";
	//}


	//cout << "Hello CMake." << endl;
	//vector<double> OEs = RV2OE(r0, v0, mu);
	//for (const double& OEs : OEs) {
	//	std::cout << OEs << " ";
	

	for (int i = 0; i < rows; i++) {
		// Clear screen and activate view to render into
		glClearColor(1, 1, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		d_cam.Activate(s_cam);

		// Render OpenGL Sphere
		glColor3f(1, 0, 0);
		GLUquadric* quad;
		quad = gluNewQuadric();
		glTranslatef(0, 0, 0);
		gluSphere(quad, 1, 20, 10);


		double x = rs.dynamicMatrix[i][0];
		double y = rs.dynamicMatrix[i][1];
		double z = rs.dynamicMatrix[i][2];

		glColor3f(0, 0, 1);
		GLUquadric* satellite;
		satellite = gluNewQuadric();
		glTranslatef(x/1000, y/1000, z/1000);
		gluSphere(satellite, 0.5, 20, 10);


		// Swap frames and Process Events
		pangolin::FinishFrame();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	

	return 0;
}
