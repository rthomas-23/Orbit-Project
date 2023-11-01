#pragma once

#include <vector>
#include "string"

#include <pangolin/display/display.h>
#include <pangolin/display/view.h>
#include <pangolin/handler/handler.h>
#include <pangolin/gl/gldraw.h>

using namespace std;

void DrawCircle(float cx, float cy, float r, int num_segments);

void plot(double x, double y, double z, int r, int g, int b);