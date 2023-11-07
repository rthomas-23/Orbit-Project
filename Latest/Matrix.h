#pragma once
#include <vector>
#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
	Matrix();
	void set_rows(int x);
	void set_columns(int x);
	int num_rows;
	int num_columns;
	std::vector<std::vector<double>> dynamicMatrix;
	void resize_matrix();
private:

};
#endif
