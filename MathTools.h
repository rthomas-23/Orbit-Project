#pragma once
#include "MathTools.h"
#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <type_traits>
#include "Matrix.h"

using namespace std;

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type // VARIADIC TEMPLATE. proceed if the type, T, is arithmetic (including double!)
magnitude(T a);

template <typename T>
typename std::enable_if<std::is_same<T, std::vector<double>>::value, double>::type // VARIADIC TEMPLATE. proceed if the type, T, is a vector<double> 
magnitude(T a);

vector<double> cross_product(const vector<double>& vector1, const vector<double>& vector2);

double dot_product(std::vector<double> w, std::vector<double> x);

vector<double> RV2OE(vector< double> r, vector< double> v, int mu);

double EccAnomalyNR(double e, double x0, double n, int dt);

vector<double> add_vectors(vector<double> a, vector<double> b);

vector<double> scale_vector(vector<double>a, double s);

Matrix F_and_G(int Tp, int ti, double a, double e, vector<double> r0, vector<double> v0);