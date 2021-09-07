#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <cstdlib>
#include <Windows.h>
#include <commdlg.h>
#include <cmath>
#include <tuple>
#include <random>
#include <cstring>
#include <numeric>



void text_output() {
	std::cout << "\nEnter the number corresponding to the menu item you are interested." << std::endl << std::endl;
	std::cout << "1 -> Notes." << std::endl;
	std::cout << "2 -> Salt Pepper noize." << std::endl;
	std::cout << "3 -> Gaussian noise." << std::endl;
	std::cout << "4 -> Smoothing filter." << std::endl;
	std::cout << "5 -> Gaussian filter." << std::endl;
	std::cout << "6 -> Median filter." << std::endl;
	std::cout << "7 -> Border selection filter(Sobel)." << std::endl;
	std::cout << "8 -> *Equalizing histogram(In development).*" << std::endl;
	std::cout << "9 -> Displaying the main menu and cleaning the console." << std::endl;
	std::cout << "0 -> Exit." << std::endl;
}



void Notes() {
	int x;
	system("CLS");
	std::cout << "Notes:" << std::endl;
	std::cout << "\n2 - Salt & Pepper:" << std::endl;
	std::cout << "\nWhen you select this item, you will be offered a choice of 3 functions:" << std::endl;
	std::cout << "\nA) - Self-contained noise, without entering any values;" << std::endl;
	std::cout << "\nB) - Noise, where you can specify the probability of pixels occurring \n\n(the probability is the same for white and black);" << std::endl;
	std::cout << "\nC) - Noise, where you can specify the probability of both pixels occurring\n\n(the probability for white is different from the probability for black);" << std::endl;
	std::cout << "\nAfter selecting a function (and entering the desired values, if required), a file selection window will open.\nSelect the file you want and wait." << std::endl;
	std::cout << "\nAfter that, a window with the result will open, and a second later a window will appear with the saving of the file." << std::endl;
	std::cout << "\n\n3 - Noise, where you are prompted to enter the mean and value for the standard deviation." << std::endl;
	std::cout << "\n\n4 - Smoothing_filter:\nThere is no way to enter your own values. You open the file with a window and wait, then save it." << std::endl;
	std::cout << "\n\n5 - Gaussian filter:\nThere is no way to enter your own values. You open the file with a window and wait, then save it." << std::endl;
	std::cout << "\n\n6 - Median filter:\nThere is no way to enter your own values. You open the file with a window and wait, then save it." << std::endl;
	std::cout << "\n\n7 - Border selection filter(Sobel):\nThere is no way to enter your own values. You open the file with a window and wait, then save it." << std::endl;
	std::cout << "\n\n8 - In development." << std::endl;
	std::cout << "\n\n!!! AFTER THE FILTER IS EXECUTED OR NOISE, A WINDOW WILL APPEAR IN WHICH A PICTURE WILL BE DISPLAYED FOR A SECOND.\n";
	std::cout << "DO NOT NEED TO CLOSE IT, IT WILL BE CLOSED BY ITSELF AFTER SAVING THE FILE (OR REFUSING TO SAVE) !!!" << std::endl;
	std::cout << "Also, DO NOT USE Cyrillic in paths and / or file names." << std::endl;
	std::cout << "\n\n\nEnter 0 -> to go to the main menu." << std::endl << std::endl;
	std::cin >> x;
	switch (x) {
	case 0:
		system("CLS");
		text_output();
		break;
		
	default:
		std::cout << "\nIncorrect value entered!" << std::endl;
		Notes();
		break;
	}
}



bool Comparison(double prob) { //prob is pixels probability
	return (std::numeric_limits<double>::epsilon() * std::fabs(prob)) > 0 ? true : false;
}



std::string open_file() {
	OPENFILENAME open_file = {sizeof open_file};
	wchar_t file[1024] = { 0 };
	file[0] = '\0';
	open_file.lpstrFilter = L".*jpg, .*jpeg";
	open_file.lpstrFile = &file[0];
	open_file.nMaxCustFilter = 1024;
	open_file.nMaxFile = 1024;
	open_file.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER;
	if (GetOpenFileName(&open_file)) {
		HWND owner = GetForegroundWindow();
		std::wstring temp_wstring(file);
		std::string picture_name;
		picture_name.resize(temp_wstring.size());
		std::transform(std::begin(temp_wstring), std::end(temp_wstring), std::begin(picture_name), wctob);
		if (DestroyWindow(owner)) {
			exit(1);
		}
		else {
			return picture_name;
		}
	}
	else {
		return "";
	}
}



void save_file(cv::Mat& img) {
		OPENFILENAME save_file = { sizeof save_file };
		wchar_t file[1024] = { 0 };
		file[0] = '\0';
		save_file.lpstrFilter = L".*jpg, .*jpeg";
		save_file.lpstrFile = &file[0];
		save_file.nMaxCustFilter = 1024;
		save_file.nMaxFile = 1024;
		save_file.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER;
		if (GetSaveFileName(&save_file)) {
			std::wstring wfile_name = &file[0];
			std::string nfile_name;
			nfile_name.resize(wfile_name.size());
			std::transform(std::begin(wfile_name), std::end(wfile_name), std::begin(nfile_name), wctob);
			wfile_name.resize(0);
			nfile_name += ".jpg";
			cv::imwrite(nfile_name, img);
			std::cout << "\nPicture saved successfully!" << std::endl;
		}
		else {
			std::cout << "\nSaving failed!" << std::endl;
		}
	text_output();
}



void Salt_Pepper() {
	cv::Mat img = cv::imread(open_file(), cv::IMREAD_COLOR);
	if (img.data) {
		int numb_o_w, numb_o_b, count_w, count_b;
		srand(time(0));
		for (int i = 0; i < img.rows; i++) {
			count_w = rand() % static_cast<int>(img.cols * 0.1);
			count_b = rand() % static_cast<int>(img.cols * 0.1);
			while (count_w > 0 || count_b > 0) {
				numb_o_w = rand() % img.cols;
				numb_o_b = rand() % img.cols;
				img.at<cv::Vec3b>(i, numb_o_w)[0] = 255;
				img.at<cv::Vec3b>(i, numb_o_w)[1] = 255;
				img.at<cv::Vec3b>(i, numb_o_w)[2] = 255;
				img.at<cv::Vec3b>(i, numb_o_b)[0] = 0;
				img.at<cv::Vec3b>(i, numb_o_b)[1] = 0;
				img.at<cv::Vec3b>(i, numb_o_b)[2] = 0;
				count_w--, count_b--;
			}
		}
		cv::namedWindow("image", cv::WINDOW_NORMAL);
		cv::imshow("image", img);
		cv::waitKey(1000);
		save_file(img);
		cv::destroyWindow("image");
	}
	else {
		std::cout << "\nOpening error!" << std::endl;
		text_output();
	}
}

void Salt_Pepper(double prob) { //prob is pixels probability 
	cv::Mat img = cv::imread(open_file(), cv::IMREAD_COLOR);
	if (img.data) {
		int numb_o_w, numb_o_b, count_w, count_b;
		srand(time(0));
		if (Comparison(prob)) {
			for (int i = 0; i < img.rows; i++) {
				count_w = rand() % static_cast<int>(((img.cols * prob) < 1) ? 1 : (img.cols * prob));
				count_b = rand() % static_cast<int>(((img.cols * prob) < 1) ? 1 : (img.cols * prob));
				while (count_w > 0 || count_b > 0) {
					numb_o_w = rand() % img.cols;
					numb_o_b = rand() % img.cols;
					img.at<cv::Vec3b>(i, numb_o_w)[0] = 255;
					img.at<cv::Vec3b>(i, numb_o_w)[1] = 255;
					img.at<cv::Vec3b>(i, numb_o_w)[2] = 255;
					img.at<cv::Vec3b>(i, numb_o_b)[0] = 0;
					img.at<cv::Vec3b>(i, numb_o_b)[1] = 0;
					img.at<cv::Vec3b>(i, numb_o_b)[2] = 0;
					count_w--, count_b--;
				}
			}
		}
		cv::namedWindow("image", cv::WINDOW_NORMAL);
		cv::imshow("image", img);
		cv::waitKey(1000);
		save_file(img);
		cv::destroyWindow("image");
	}
	else {
		std::cout << "\nOpening error!" << std::endl;
		text_output();
	}
}

void Salt_Pepper(double prob_w, double prob_b) { //prob_f_w(b) is probability of white(and black) pixels
	cv::Mat img = cv::imread(open_file(), cv::IMREAD_COLOR);
	if (img.data) {
		int numb_o_w, numb_o_b, count_w, count_b;
		srand(time(0));
		if (!Comparison(prob_w) && Comparison(prob_b)) {
			for (int i = 0; i < img.rows; i++) {
				count_b = rand() % static_cast<int>(((img.cols * prob_b) < 1) ? 1 : (img.cols * prob_b));
				while (count_b > 0) {
					numb_o_b = rand() % img.cols;
					img.at<cv::Vec3b>(i, numb_o_b)[0] = 0;
					img.at<cv::Vec3b>(i, numb_o_b)[1] = 0;
					img.at<cv::Vec3b>(i, numb_o_b)[2] = 0;
					count_b--;
				}
			}
		}
		else if (Comparison(prob_w) && !Comparison(prob_b)) {
			for (int i = 0; i < img.rows; i++) {
				count_w = rand() % static_cast<int>(((img.cols * prob_w) < 1) ? 1 : (img.cols * prob_w));
				while (count_w > 0) {
					numb_o_w = rand() % img.cols;
					numb_o_b = rand() % img.cols;
					img.at<cv::Vec3b>(i, numb_o_w)[0] = 255;
					img.at<cv::Vec3b>(i, numb_o_w)[1] = 255;
					img.at<cv::Vec3b>(i, numb_o_w)[2] = 255;
					count_w--;
				}
			}
		}
		else {
			for (int i = 0; i < img.rows; i++) {
				count_w = rand() % static_cast<int>(((img.cols * prob_w) < 1) ? 1 : (img.cols * prob_w));
				count_b = rand() % static_cast<int>(((img.cols * prob_b) < 1) ? 1 : (img.cols * prob_b));
				while (count_w > 0 || count_b > 0) {
					numb_o_w = rand() % img.cols;
					numb_o_b = rand() % img.cols;
					img.at<cv::Vec3b>(i, numb_o_w)[0] = 255;
					img.at<cv::Vec3b>(i, numb_o_w)[1] = 255;
					img.at<cv::Vec3b>(i, numb_o_w)[2] = 255;
					img.at<cv::Vec3b>(i, numb_o_b)[0] = 0;
					img.at<cv::Vec3b>(i, numb_o_b)[1] = 0;
					img.at<cv::Vec3b>(i, numb_o_b)[2] = 0;
					count_w--, count_b--;
				}
			}
		}
		cv::namedWindow("image", cv::WINDOW_NORMAL);
		cv::imshow("image", img);
		cv::waitKey(1000);
		save_file(img);
		cv::destroyWindow("image");
	}
	else {
		std::cout << "\nOpening error!" << std::endl;
		text_output();
	}
}

void Selecting_Salt_Pepper() { //Selecting a Salt&Pepper noise variation
	system("CLS");
	int x;
	std::cout << "\nSelect a noise option:" << std::endl;
	std::cout << "1 -> Noise without the need to specify the probability." << std::endl;
	std::cout << "2 -> Noise with an indication of equal probability." << std::endl;
	std::cout << "3 -> Noise with two probabilities." << std::endl;
	std::cout << "9 -> Closing this menu." << std::endl;
	std::cout << "0 -> Closing the application." << std::endl << std::endl;
	std::cin >> x;
	switch (x) {
	case 1:
		Salt_Pepper();
		break;

	case 2:
		double prob;
		std::cout << "\nNow enter the probability: ";
		std::cin >> prob;
		Salt_Pepper(prob);
		break;

	case 3:
		double prob_w, prob_b;
		std::cout << "\nNow enter the probability of white: ";
		std::cin >> prob_w;
		std::cout << "\nNow enter the probability of black: ";
		std::cin >> prob_b;
		Salt_Pepper(prob_w, prob_b);
		break;

	case 9:
		system("CLS");
		text_output();
		break;

	case 0:
		exit(0);
		break;

	default:
		std::cout << "\nIncorrect value entered!" << std::endl << std::endl;
		text_output();
		break;
	}
}




void Gaussian_noise() {
	double mean = 0, stddev = 0; //mean & standard deviation (stddev)
	cv::Mat img = cv::imread(open_file(), cv::IMREAD_COLOR);

	if (img.data) {
		cv::Mat image = img.clone();
		std::cout << "\nThe recommended value for the mean is 1, for the standard deviation(stddev) is 128." << std::endl;
		std::cout << "\nEnter the mean: ";
		std::cin >> mean;
		std::cout << "\nEnter the stddev: ";
		std::cin >> stddev;

		if (!Comparison(stddev)) {
			std::cout << "\nInvalid value for stddev!" << std::endl;
			text_output();
			return;
		}

		std::default_random_engine generator;
		std::normal_distribution<double> dist(mean, stddev);

		for (int y = img.rows; y >= 0; y--) {
			for (int x = img.cols; x >= 0; x--) {
				//For channel 0
				if ((image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
					                     x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[0] + fabs(dist(generator))) > 255) {

					image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
						                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[0] = 255;
				}
				else if ((image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
					                          x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[0] + fabs(dist(generator)) < 0)) {

					image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
						                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[0] = 0;
				}
				else {
					image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
						                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[0] += fabs(dist(generator));
				}

				//For channel 1
				if ((image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
					                     x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[1] + fabs(dist(generator))) > 255) {

					image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
						                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[1] = 255;
				}
				else if ((image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
					                          x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[1] + fabs(dist(generator)) < 0)) {

					image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
						                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[1] = 0;
				}
				else {
					image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
						                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[1] += fabs(dist(generator));
				}

				//For channel 2
				if ((image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
					                     x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[2] + fabs(dist(generator))) > 255) {

					image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
						                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[2] = 255;
				}
				else if ((image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
					                                      x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[2] + fabs(dist(generator)) < 0)) {

					image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
						                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[2] = 0;
				}
				else {
					image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
						                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[2] += fabs(dist(generator));
				}
			}
		}
		cv::namedWindow("image", cv::WINDOW_NORMAL);
		cv::imshow("image", image);
		cv::waitKey(1000);
		save_file(image);
		cv::destroyWindow("image");
	}
	else {
		std::cout << "\nOpening error!" << std::endl;
		text_output();
	}
}



void mean(cv::Mat& img, int x, int y) {
	int count = 0, mean_B, mean_G, mean_R, arr_B[9] = { 0 }, arr_G[9] = { 0 }, arr_R[9] = { 0 };
	for (int i = x; i < x + 3; i++) {
		for (int j = y; j < y + 3; j++) {
			arr_B[count] = img.at<cv::Vec3b>(i, j)[0];
			arr_G[count] = img.at<cv::Vec3b>(i, j)[1];
			arr_R[count] = img.at<cv::Vec3b>(i, j)[2];
			count++;
		}
	}
	mean_B = (arr_B[0] + arr_B[1] + arr_B[2] + arr_B[3] + arr_B[4] + arr_B[5] + arr_B[6] + arr_B[7] + arr_B[8]) / 9;
	mean_G = (arr_G[0] + arr_G[1] + arr_G[2] + arr_G[3] + arr_G[4] + arr_G[5] + arr_G[6] + arr_G[7] + arr_G[8]) / 9;
	mean_R = (arr_R[0] + arr_R[1] + arr_R[2] + arr_R[3] + arr_R[4] + arr_R[5] + arr_R[6] + arr_R[7] + arr_R[8]) / 9;

	for (int i = x; i < x + 3; i++) {
		for (int j = y; j < y + 3; j++) {
			img.at<cv::Vec3b>(i, j)[0] = mean_B;
			img.at<cv::Vec3b>(i, j)[1] = mean_G;
			img.at<cv::Vec3b>(i, j)[2] = mean_R;
		}
	}
}

void Smoothing_filter() {
	cv::Mat img = cv::imread(open_file(), cv::IMREAD_COLOR);
	if (img.data) {
		for (int x = 0; x < img.rows - 2; x++) {
			for (int y = 0; y < img.cols - 2; y++) {
				mean(img, x, y);
			}
		}
		cv::namedWindow("image", cv::WINDOW_NORMAL);
		cv::imshow("image", img);
		cv::waitKey(1000);
		save_file(img);
		cv::destroyWindow("image");
	}
	else {
		std::cout << "\nOpening error!" << std::endl;
		text_output();
	}
}



void G_F(cv::Mat& img, cv::Mat& image, int y, int x) {
	int count = 0, x1 = x, y1 = y;
	double dim = 5, kernel[5][5] = { 0 }, arr_B[5][5] = { 0 }, arr_G[5][5] = { 0 }, arr_R[5][5] = { 0 }, s_B = 0, s_G = 0, s_R = 0, mean = dim / 2, sigma = 1, sum = 0;
	const double PI = 3.1415;

	cv::Vec3b& pix = img.at<cv::Vec3b>(0, 0);

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			kernel[i][j] = exp(-0.5 * (((i - mean) / sigma) * ((i - mean) / sigma)) + (((j - mean) / sigma) * ((j - mean) / sigma))) / 2 * PI * sigma * sigma;
			sum += kernel[i][j];
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			kernel[i][j] /= sum;
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			pix = img.at<cv::Vec3b>(y1 < 0 ? 0 : y1 >= img.rows ? img.rows - 1 : y1,
				                    x1 < 0 ? 0 : x1 >= img.cols ? img.cols - 1 : x1);
			arr_B[i][j] = pix[0];
			arr_G[i][j] = pix[1];
			arr_R[i][j] = pix[2];
			x1--;
		}
		x1 = x;
		y1--;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			arr_B[i][j] *= kernel[i][j];
			s_B += arr_B[i][j];
			
			arr_G[i][j] *= kernel[i][j];
			s_G += arr_G[i][j];

			arr_R[i][j] *= kernel[i][j];
			s_R += arr_R[i][j];
		}
	}

	image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
		                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[0] = s_B;
	image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
		                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[1] = s_G;
	image.at<cv::Vec3b>(y < 0 ? 0 : y >= img.rows ? img.rows - 1 : y,
		                x < 0 ? 0 : x >= img.cols ? img.cols - 1 : x)[2] = s_R;
}

void Gaussian_filter() {
	cv::Mat img = cv::imread(open_file(), cv::IMREAD_COLOR);
	if (img.data) {
		cv::Mat image = img.clone();
		for (int y = img.rows; y >= 0; y--) {
			for (int x = img.cols; x >= 0; x--) {
				G_F(img, image, y, x);
			}
		}
		cv::namedWindow("image", cv::WINDOW_NORMAL);
		cv::imshow("image", image);
		cv::waitKey(1000);
		save_file(image);
		cv::destroyWindow("image");
	}
	else {
		std::cout << "\nOpening error!" << std::endl;
		text_output();
	}
}



std::tuple <int, int, int> median(cv::Mat& img, int i, int j) { //Calculating the median
	int count = 0, mean_B = 0, mean_G = 0, mean_R = 0, arr_B[9] = { 0 }, arr_G[9] = { 0 }, arr_R[9] = { 0 };
	cv::Vec3b& color = img.at<cv::Vec3b>(0, 0);
	
	for (int x = i; x < i + 3; x++) {
		for (int y = j; y < j + 3; y++) {
			color = img.at<cv::Vec3b>(x, y);
			arr_B[count] = color[0];
			arr_G[count] = color[1];
			arr_R[count] = color[2];
			count++;
		}
	}
	
	for (int g = 0; g < 9; g++) {
		for (int h = 0; h < 9; h++) {
			if (arr_B[g] < arr_B[h]) {
				std::swap(arr_B[g], arr_B[h]);
			}
			if (arr_G[g] < arr_G[h]) {
				std::swap(arr_G[g], arr_G[h]);
			}
			if (arr_R[g] < arr_R[h]) {
				std::swap(arr_R[g], arr_R[h]);
			}
		}
	}

	mean_B = (arr_B[0] + arr_B[1] + arr_B[2] + arr_B[3] + arr_B[4] + arr_B[5] + arr_B[6] + arr_B[7] + arr_B[8]) / 9;
	mean_B = (arr_G[0] + arr_G[1] + arr_G[2] + arr_G[3] + arr_G[4] + arr_G[5] + arr_G[6] + arr_G[7] + arr_G[8]) / 9;
	mean_B = (arr_R[0] + arr_R[1] + arr_R[2] + arr_R[3] + arr_R[4] + arr_R[5] + arr_R[6] + arr_R[7] + arr_R[8]) / 9;

	if (fabs(mean_B - arr_B[4]) < fabs(mean_B - arr_B[5])) {
		mean_B = arr_B[4];
	}
	else {
		mean_B = arr_B[5];
	}

	if (fabs(mean_G - arr_G[4]) < fabs(mean_G - arr_G[5])) {
		mean_G = arr_G[4];
	}
	else {
		mean_G = arr_G[5];
	}

	if (fabs(mean_R - arr_R[4]) < fabs(mean_R - arr_R[5])) {
		mean_R = arr_R[4];
	}
	else {
		mean_R = arr_R[5];
	}
	std::tuple <int, int, int> tupl(mean_B, mean_G, mean_R);
	return tupl;
}

void Median_filter() {
	int mean_B, mean_G, mean_R;
	cv::Mat img = cv::imread(open_file(), cv::IMREAD_COLOR);
	if (img.data) {
		for (int x = 0; x < img.rows - 2; x++) {
			for (int y = 0; y < img.cols - 2; y++) {
				std::tuple <int, int, int> tupl(median(img, x, y));
				mean_B = std::get<0>(tupl), mean_G = std::get<1>(tupl), mean_R = std::get<2>(tupl);
				img.at<cv::Vec3b>(x + 1, y + 1)[0] = mean_B;
				img.at<cv::Vec3b>(x + 1, y + 1)[1] = mean_G;
				img.at<cv::Vec3b>(x + 1, y + 1)[2] = mean_R;
			}
		}
		cv::namedWindow("image", cv::WINDOW_NORMAL);
		cv::imshow("image", img);
		cv::waitKey(1000);
		save_file(img);
		cv::destroyWindow("image");
	}
	else {
		std::cout << "\nOpening error!" << std::endl;
		text_output();
	}
	
}



void Sobel(cv::Mat& img, cv::Mat& image, int x, int y) {
	int count = 0, second_count = 0;
	double arr_P[3][3] = { 0 }, Gx, Gy, f;
	for (int i = x - 1; i < x + 2; i++) {
		for (int j = y - 1; j < y + 2; j++) {
			arr_P[count][second_count] = img.at<uchar>(i < 0 ? 0 : i >= img.rows ? img.rows - 1 : i,
													   j < 0 ? 0 : j >= img.cols ? img.cols - 1 : j);
			second_count++;
		}
		second_count = 0;
		count++;
	}

	Gy = (arr_P[0][2] + 2 * arr_P[1][2] + arr_P[2][2]) - (arr_P[0][0] + 2 * arr_P[1][0] + arr_P[2][0]);
	Gx = (arr_P[2][0] + 2 * arr_P[2][1] + arr_P[2][2]) - (arr_P[0][0] + 2 * arr_P[0][1] + arr_P[0][2]);
	f = sqrt(Gx * Gx + Gy * Gy);

	image.at<uchar>(x, y) = f;
}

void Border_selection_filter_Sobel() {
	cv::Mat img = cv::imread(open_file(), cv::IMREAD_GRAYSCALE);
	if (img.data) {
		cv::Mat image = img.clone();
		for (int i = 0; i < img.rows; i++) {
			for (int j = 0; j < img.cols; j++) {
				Sobel(img, image, i, j);
			}
		}
		cv::namedWindow("image", cv::WINDOW_NORMAL);
		cv::imshow("image", image);
		cv::waitKey(1000);
		save_file(image);
		cv::destroyWindow("image");
	}
	else {
		std::cout << "\nOpening error!" << std::endl;
		text_output();
	}
}



void Equalizing_histogram() {
	cv::Mat img = cv::imread(open_file(), cv::IMREAD_GRAYSCALE);
	if (img.data) {
		exit(1);
	}
	else {
		std::cout << "\nOpening error!" << std::endl;
		text_output();
	}
}
