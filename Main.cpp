#include "Img.h"



int main() {
	int x;
	std::cout << "*SURELY read the notes before using the app!*" << std::endl;
	text_output();
	std::cout << std::endl;
	std::cin >> x;
	while (x != 0) {
		switch (x) {
		case 1:
			Notes();
			break;

		case 2:
			Selecting_Salt_Pepper();
			break;

		case 3:
			//Gaussian_noise();
			break;

		case 4:
			Smoothing_filter();
			break;

		case 5:
			Gaussian_filter();
			break;

		case 6:
			Median_filter();
			break;

		case 7:
			Border_selection_filter_Sobel();
			//std::cout << "7" << std::endl;
			break;

		case 8:
			//Equalizing_histogram();
			break;

		case 9:
			system("CLS");
			text_output();
			break;
		
		case 0:
			text_output();
			break;

		default:
			std::cout << "Incorrect value entered!" << std::endl << std::endl;
			text_output();
			break;
		}
		std::cout << std::endl;
		std::cin >> x;
	}
	return 0;
}