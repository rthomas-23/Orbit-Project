#include <iostream>
using namespace std;

double enterData(double x, char param, string cmd_rqst, int min_val) {
	// param: to determine what parameter is being assigned. 
	// 'e' = eccentricity
	// 'a' = semi-major axis
	// 'ang' = angle

	if (param == 'a') { // semi-major axis 
		char yn;
		while (true) {
			cout << cmd_rqst << endl;
			while (!(std::cin >> x)) {
				std::cout << "Invalid input. Please enter a valid double: ";

				// Clear the input buffer
				std::cin.clear();

				// Ignore any remaining characters in the buffer
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			if (x <= min_val) {
				while (true) {
					cout << "Entry Not-Applicable... End program? (y/n)" << endl;
					cin >> yn;
					if (yn == 'y') { yn = ' '; return 0; }
					else if (yn == 'n') { yn = ' '; break; }
					yn = ' ';
				}
			} 
			else { break; }
		}
	}

	else if (param == 'e') { // eccentricity 
		char yn;
		while (true) {
			cout << cmd_rqst << endl;
			while (!(std::cin >> x)) {
				std::cout << "Invalid input. Please enter a valid double: ";

				// Clear the input buffer
				std::cin.clear();

				// Ignore any remaining characters in the buffer
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} 
			if (x<0 || x >=1) {
				while (true) {
					cout << "Entry Not-Applicable... End program? (y/n)" << endl;
					cin >> yn;
					if (yn == 'y') { yn = ' '; return 0; }
					else if (yn == 'n') { yn = ' '; break; }
					yn = ' ';
				}
			}
			else { break; }
		}
	}
	
	else if (param == 'ang') { // angle 
		char yn;
		while (true) {
			cout << cmd_rqst << endl;
			while (!(std::cin >> x)) {
				std::cout << "Invalid input. Please enter a valid double: ";

				// Clear the input buffer
				std::cin.clear();

				// Ignore any remaining characters in the buffer
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} //RAAN < 0 || RAAN>2 * pi
			if (x < 0 || x >= min_val) {
				while (true) {
					cout << "Entry Not-Applicable... End program? (y/n)" << endl;
					cin >> yn;
					if (yn == 'y') { yn = ' '; return 0; }
					else if (yn == 'n') { yn = ' '; break; }
					yn = ' ';
				}
			}
			else { break; }
		}
	}


	// this is for angles:
	else {
		char yn;
		while (true) {
			cout << cmd_rqst << endl;
			while (!(std::cin >> x)) {
				std::cout << "Invalid input. Please enter a valid double: ";

				// Clear the input buffer
				std::cin.clear();

				// Ignore any remaining characters in the buffer
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			if (x < 0 || x>min_val) {
				while (true) {
					cout << "Entry Not-Applicable... End program? (y/n)" << endl;
					cin >> yn;
					if (yn == 'y') { yn = ' '; return 0; }
					else if (yn == 'n') { yn = ' '; break; }
					yn = ' ';
				}
			}
			else { break; }
		}
	}
	return x;
}

char enterData(char x, string cmd_rqst) {
	char yn;
	while (true) {
			cout << cmd_rqst << endl;

			while (!(std::cin >> x)) {
				std::cout << "Invalid input. Please enter a valid char: ";

				// Clear the input buffer
				std::cin.clear();

				// Ignore any remaining characters in the buffer
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			if (x != 'b' && x != 'r' && x != 'g' && x != 'y' && x != 'p' && x != 't' && x != 'w' && x != 'o')
			{while (true) {
					cout << "Entry Not-Applicable... End program? (y/n)" << endl;
					cin >> yn;
					if (yn == 'y') { yn = ' '; return 0; }
					else if (yn == 'n') { yn = ' '; break; }
					yn = ' ';
				}
		}
			else { break; }
		}
	return x;
}