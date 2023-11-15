#pragma once

#include <vector>
#include "string"

#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gldraw.h>

using namespace std;

void DrawCircle(vector<vector<double>> points);

void plot(double x, double y, double z, int r, int g, int b);

void keyPressed(unsigned char key, int x, int y);