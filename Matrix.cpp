#include "Matrix.h"
#include <vector>

Matrix::Matrix() {
	num_rows = 0;
	num_columns = 0;
	dynamicMatrix = { {0}, {0} };
}
void Matrix::set_rows(int x) {
	num_rows = x;
}
void Matrix::set_columns(int x) {
	num_columns = x;
}
void Matrix::resize_matrix() {
	dynamicMatrix.resize(num_rows);
	for (int i = 0; i < num_rows; i++) {
		dynamicMatrix[i].resize(num_columns);
	}
}
