//709Assignment.cpp
/*

the aim of this project is to identify and read resistor values in a set of given images.

written by: David Shi


*/

#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include <opencv2\imgproc.hpp>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace cv;
using namespace std;


//enum for colour code
enum colourCode {
	black, //0
	brown, //1
	red, //2
	orange, //3
	yellow, //4
	green, //5
	blue, //6
	violet, //7
	gray, //8
	white, //9
	gold, //0.1
	silver, //0.01
};

//convert string to colourcode
colourCode translate(string input) {
	if (input == "black")    return black;
	if (input == "brown")    return brown;
	if (input == "red")      return red;
	if (input == "orange")   return orange;
	if (input == "yellow")   return yellow;
	if (input == "green")    return green;
	if (input == "blue")     return blue;
	if (input == "violet")   return violet;
	if (input == "gray")     return gray;
	if (input == "white")    return white;
	if (input == "gold")     return gold;
	if (input == "silver")   return silver;
};

//this takes an input area of pixels and then determines the best colour that describes that area by finding a mask of each colour
//and the mask with the highest value (most pixels within threshold ranges) will be returned.
string decodeBlue(Mat input) {
	//this should takes an input array of pixels 
	vector<double> colourPredictions;
	vector<string> colour;

	//for each section of the image, take the best estimate of colour by doing an inrange for every single colour
	//and then return the colour with the highest average inrange output

	//black
	Mat black;
	inRange(input, Scalar(0, 0, 0), Scalar(180, 255, 50), black);
	colourPredictions.push_back(mean(black).val[0]);
	colour.push_back("black");

	//brown
	Mat brown;
	inRange(input, Scalar(0, 61, 0), Scalar(16, 255, 100), brown);
	colourPredictions.push_back(mean(brown).val[0]);
	colour.push_back("brown");

	//red
	Mat red;
	inRange(input, Scalar(131, 28, 45), Scalar(180, 255, 204), red);
	colourPredictions.push_back(mean(red).val[0]);
	colour.push_back("red");

	//orange
	Mat orange;
	inRange(input, Scalar(0, 73, 109), Scalar(18, 255, 255), orange);
	colourPredictions.push_back(mean(orange).val[0]);
	colour.push_back("orange");

	//yellow
	Mat yellow;
	inRange(input, Scalar(29, 0, 0), Scalar(39, 255, 255), yellow);
	colourPredictions.push_back(mean(yellow).val[0]);
	colour.push_back("yellow");

	//green
	Mat green;
	inRange(input, Scalar(39, 93, 31), Scalar(68, 255, 255), green);
	colourPredictions.push_back(mean(green).val[0]);
	colour.push_back("green");

	//blue
	Mat blue;
	inRange(input, Scalar(104, 141, 0), Scalar(113, 255, 155), blue);
	colourPredictions.push_back(mean(blue).val[0]);
	colour.push_back("blue");

	//violet
	Mat violet;
	inRange(input, Scalar(113, 47, 37), Scalar(135, 171, 216), violet);
	colourPredictions.push_back(mean(violet).val[0]);
	colour.push_back("violet");

	//gray
	Mat gray;
	inRange(input, Scalar(96, 0, 43), Scalar(138, 55, 255), gray);
	colourPredictions.push_back(mean(gray).val[0]);
	colour.push_back("gray");

	//gold
	Mat gold;
	inRange(input, Scalar(18, 48, 0), Scalar(39, 255, 255), gold);
	colourPredictions.push_back(mean(gold).val[0]);
	colour.push_back("gold");

	//silver -- to hard to distinguish from white or grey, just pretend this colour doesn't exist :)
	//Mat silver;
	//inRange(input, Scalar(48, 2, 98), Scalar(101, 59, 255), silver);
	//colourPredictions.push_back(mean(silver).val[0]);
	//colour.push_back("silver");

	//white
	Mat white;
	inRange(input, Scalar(84, 0, 105), Scalar(110, 75, 255), white);
	colourPredictions.push_back(mean(white).val[0]);
	colour.push_back("white");

	//resistor
	Mat resistor;
	inRange(input, Scalar(41, 29, 80), Scalar(107, 143, 207), resistor);
	colourPredictions.push_back(mean(resistor).val[0]);
	colour.push_back("resistor");

	//get the index for the highest match
	int index = distance(colourPredictions.begin(), max_element(colourPredictions.begin(), colourPredictions.end()));
	//return the colour of that index
	return(colour[index]);
};

//this is needed because colour read on blue and green resistors are different, hence, have different thresholds.
string decodeGreen(Mat input) {
	//this should takes an input array of pixels 
	vector<double> colourPredictions;
	vector<string> colour;

	//for each section of the image, take the best estimate of colour by doing an inrange for every single colour
	//and then return the colour with the highest average inrange output

	//black
	Mat black;
	inRange(input, Scalar(30, 0, 0), Scalar(180, 255, 66), black);
	colourPredictions.push_back(mean(black).val[0]);
	colour.push_back("black");

	//brown
	Mat brown;
	inRange(input, Scalar(8, 102, 0), Scalar(39, 255, 125), brown);
	colourPredictions.push_back(mean(brown).val[0]);
	colour.push_back("brown");

	//red
	Mat red;
	inRange(input, Scalar(0, 0, 0), Scalar(6, 255, 255), red);
	colourPredictions.push_back(mean(red).val[0]);
	colour.push_back("red");

	//orange
	Mat orange;
	inRange(input, Scalar(10, 180, 0), Scalar(18, 255, 255), orange);
	colourPredictions.push_back(mean(orange).val[0]);
	colour.push_back("orange");

	//yellow
	Mat yellow;
	inRange(input, Scalar(29, 116, 0), Scalar(39, 255, 255), yellow);
	colourPredictions.push_back(mean(yellow).val[0]);
	colour.push_back("yellow");

	//green
	Mat green;
	inRange(input, Scalar(47, 87, 0), Scalar(76, 255, 255), green);
	colourPredictions.push_back(mean(green).val[0]);
	colour.push_back("green");

	//blue
	Mat blue;
	inRange(input, Scalar(100, 125, 0), Scalar(108, 255, 255), blue);
	colourPredictions.push_back(mean(blue).val[0]);
	colour.push_back("blue");

	//violet
	Mat violet;
	inRange(input, Scalar(84, 80, 46), Scalar(137, 132, 164), violet);
	colourPredictions.push_back(mean(violet).val[0]);
	colour.push_back("violet");

	//gray
	Mat gray;
	inRange(input, Scalar(27, 0, 46), Scalar(98, 35, 150), gray);
	colourPredictions.push_back(mean(gray).val[0]);
	colour.push_back("gray");

	//gold -- NO GOLD IN GREEN RESISTORS
	//Mat gold;
	//inRange(input, Scalar(18, 48, 0), Scalar(39, 255, 255), gold);
	//colourPredictions.push_back(mean(gold).val[0]);
	//colour.push_back("gold");

	//silver -- to hard to distinguish from white or grey, just pretend this colour doesn't exist :)
	//Mat silver;
	//inRange(input, Scalar(48, 2, 98), Scalar(101, 59, 255), silver);
	//colourPredictions.push_back(mean(silver).val[0]);
	//colour.push_back("silver");

	//white
	Mat white;
	inRange(input, Scalar(84, 0, 105), Scalar(110, 75, 255), white);
	colourPredictions.push_back(mean(white).val[0]);
	colour.push_back("white");

	//resistor
	Mat resistor;
	inRange(input, Scalar(41, 29, 80), Scalar(107, 143, 207), resistor);
	colourPredictions.push_back(mean(resistor).val[0]);
	colour.push_back("resistor");

	int index = distance(colourPredictions.begin(), max_element(colourPredictions.begin(), colourPredictions.end()));

	return(colour[index]);
};


/*
how to read resistors :
First 3 bands : make up the 3 digits of the resistor
4th band : is the multiplier(black = 10 ^ 0, white = 10 ^ 9)
last band : brown 1 % tolerance
*/
__int64 getResistance(vector<string> bands) {

	if (translate(bands.back()) != brown)
	{
		//reverse the vector
		reverse(bands.begin(), bands.end());
	}

	if (translate(bands[0]) >= 10 || translate(bands[1]) >= 10 || translate(bands[2]) >= 10)
	{
		//reverse the vector back if you find gold or silver in the first 3 bands
		reverse(bands.begin(), bands.end());
	}

	int power = 0;

	if (translate(bands[3]) >= 10)
	{
		//when there is a gold or silver band present 
		power = -(translate(bands[3]) - 9);
	}
	else
	{
		power = translate(bands[3]);
	}

	//int64 needed as some resistances value overflows normal int
	__int64 multiplier = translate(bands[0]) * 100 + translate(bands[1]) * 10 + translate(bands[2]);
	return multiplier * pow(10, power);
};



// --------------- THIS SECTION IS FOR FINDING THE THRESHOLD VALUES OF EACH COLOUR-----------------

int low_h = 100, low_s = 0, low_v = 0;
int high_h = 180, high_s = 255, high_v = 255;

int thresh = 25;
int max_thresh = 255;
RNG rng(12345);

void on_low_h_thresh_trackbar(int, void *)
{
	low_h = min(high_h - 1, low_h);
	setTrackbarPos("Low H", "Object Detection", low_h);
}
void on_high_h_thresh_trackbar(int, void *)
{
	high_h = max(high_h, low_h + 1);
	setTrackbarPos("High H", "Object Detection", high_h);
}
void on_low_s_thresh_trackbar(int, void *)
{
	low_s = min(high_s - 1, low_s);
	setTrackbarPos("Low S", "Object Detection", low_s);
}
void on_high_s_thresh_trackbar(int, void *)
{
	high_s = max(high_s, low_s + 1);
	setTrackbarPos("High S", "Object Detection", high_s);
}
void on_low_v_thresh_trackbar(int, void *)
{
	low_v = min(high_v - 1, low_v);
	setTrackbarPos("Low V", "Object Detection", low_v);
}
void on_high_v_thresh_trackbar(int, void *)
{
	high_v = max(high_v, low_v + 1);
	setTrackbarPos("High V", "Object Detection", high_v);
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TASK 1 2 and 3
int main()
{

	/*////////////////////////////////////////////////////////////////////////////////////////////////////////

	//----------CODE FOR GETTING HSV UPPER AND LOWER LIMITS, UNCOMMENT THIS AND COMMENT OUT REST OF CODE TO SEE IT IN ACTION----------
	// how to use: select an image to read and then adjust the H S V upper and lower bands so that most of the colour you want lies within
	// that range, once you're comfortable, copy these values into the decode functions.


	Mat src = imread("combined.jpg", 1);
	Mat src_hsv;
	cvtColor(src, src_hsv, CV_BGR2HSV);
	Mat src_threshold;

	namedWindow("Object Detection", WINDOW_GUI_NORMAL);
	//-- Trackbars to set thresholds for RGB values
	createTrackbar("Low H", "Object Detection", &low_h, 180, on_low_h_thresh_trackbar);
	createTrackbar("High H", "Object Detection", &high_h, 180, on_high_h_thresh_trackbar);
	createTrackbar("Low S", "Object Detection", &low_s, 255, on_low_s_thresh_trackbar);
	createTrackbar("High S", "Object Detection", &high_s, 255, on_high_s_thresh_trackbar);
	createTrackbar("Low V", "Object Detection", &low_v, 255, on_low_v_thresh_trackbar);
	createTrackbar("High V", "Object Detection", &high_v, 255, on_high_v_thresh_trackbar);

	while ((char)waitKey(1) != 'q')
	{
	if (src.empty())
	break;
	//-- Detect the object based on RGB Range Values
	inRange(src_hsv, Scalar(low_h, low_s, low_v), Scalar(high_h, high_s, high_v), src_threshold);
	//-- Show the frames
	imshow("Object Detection", src_threshold);
	}
	
	*////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	ofstream myfile;
	//----------------------UNCOMMENT FOR TASK 1------------------------------------
	//Mat src = imread("single_s.jpg", 1);
	//myfile.open("Task1.txt");

	//----------------------UNCOMMENT FOR TASK 2------------------------------------
	//Mat src = imread("regular_s.jpg", 1);
	//myfile.open("Task2.txt");

	//----------------------UNCOMMENT FOR TASK 3------------------------------------
	Mat src = imread("irregular_s.jpg", 1);
	myfile.open("Task3.txt");


	Mat src_hsv;
	cvtColor(src, src_hsv, CV_BGR2HSV);
	Mat src_threshold;

	Scalar Resistor_low = Scalar(41, 29, 30);
	Scalar Resistor_high = Scalar(107, 143, 207);

	//in order to find the resistor positions, we open the image up first to get rid of noise pixels and then 
	// we close the image using a very large kernal so that the bands in between the resistors gets blurred so that
	// the resistor looks like a rectangle
	inRange(src_hsv, Resistor_low, Resistor_high, src_threshold);

	morphologyEx(src_threshold, src_threshold, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(5, 5)));
	morphologyEx(src_threshold, src_threshold, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(5, 5)));
	morphologyEx(src_threshold, src_threshold, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(25, 25)));

	Mat canny_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	// Detect edges using canny
	Canny(src_threshold, canny_output, thresh, thresh * 2, 3);

	// Find contours
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	// Matrix array for drawing contours
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);

	//create a vector of rotated rectangles for it to surround the resistor
	vector<RotatedRect> boundRect(0);

	for (int i = 0; i< contours.size(); i++)
	{

		double area = contourArea(contours[i], false);
		if (area > 3000)
		{
			//draw a bounding rectangle if the area of a contour meets the minimum threshold
			boundRect.push_back(minAreaRect(Mat(contours[i])));
		}

	}

	Mat rot_mat;
	Mat rotated;
	Mat cropped;
	vector<__int64> resistances;
	
	for (int i = 0; i < boundRect.size(); i = i + 2)
	{

		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		Point2f rect_points[4]; boundRect[i].points(rect_points);

		//-------------------------UNCOMMENT TO SEE RECTANGLES OF THE RESISTORS----------------------------
		//for (int j = 0; j < 4; j++)
		//{
		//	line(drawing, rect_points[j], rect_points[(j + 1) % 4], color, 2, 8);
		//}

		// get the rotation matrix
		rot_mat = getRotationMatrix2D(boundRect[i].center, boundRect[i].angle, 1);

		// perform the affine transformation
		warpAffine(src, rotated, rot_mat, src.size(), INTER_CUBIC);

		// crop the resulting image
		getRectSubPix(rotated, boundRect[i].size, boundRect[i].center, cropped);

		//rotating vertical resistors
		if (cropped.rows > cropped.cols)
		{
			rotate(cropped, cropped, ROTATE_90_CLOCKWISE);
		}

		//SPECIFIC CASE FOR RESISTOR 52 - the one with the wire across it
		//flip it because it cant see the resistor colour in 1 direction, but can in the other direction

		Mat temp = cropped;

		if (i == 52)
		{
			flip(cropped, temp, 1);
		}

		cropped = temp;


		int cropPx = 6;
		//cropping the image to get rid of excess background
		Mat croppedImage = cropped(Rect(cropPx, cropPx * 2, cropped.cols - cropPx, cropped.rows - cropPx * 3));

		//-------------------UNCOMMMENT TO SEE EACH INDIVIDUAL RESISTOR-------------------
		//imwrite("Cropped Resistor " + to_string(i) + ".jpg", croppedImage);

		//now i need to read along the resistor

		//converting  resistor to HSV domain
		Mat resistor_hsv;
		cvtColor(croppedImage, resistor_hsv, CV_BGR2HSV);

		//okay so if i physically took the average pixel colour of every pixel in each row and read across the resistor
		//i first need to find the resistor band. that means we can start storing bands found
		//once i find a colour that matches one of the colours in the colour library, i then need to the resistor band again before i can store it.
		//restart cycle, once i am currently reading resistor band, i will then try find a colour within the library


		//store the decoded colour sequence
		vector<string> columnColours;
		vector<string> bandSequence;

		// DIFFERENT RESISTORS HAVE DIFFERENT COLOUR THRESHOLDS, SO NEED TO DISTINGUISH BETWEEN THE TWO
		Scalar BlueResistor_low = Scalar(64, 68, 77);
		Scalar BlueResistor_high = Scalar(101, 123, 157);
		Scalar GreenResistor_low = Scalar(40, 43, 80);
		Scalar GreenResistor_high = Scalar(68, 73, 207);

		Mat BlueResistor;
		Mat GreenResistor;
		inRange(resistor_hsv, BlueResistor_low, BlueResistor_high, BlueResistor);
		inRange(resistor_hsv, GreenResistor_low, GreenResistor_high, GreenResistor);

		//if the resistor is blue
		if (mean(BlueResistor).val[0] > mean(GreenResistor).val[0])
		{
			for (int i = 1; i < resistor_hsv.cols - 1; i++)
			{

				Mat colPix = resistor_hsv(Rect(i-1, 0, 3, resistor_hsv.rows));
				//store the colour of each column of the resistor
				columnColours.push_back(decodeBlue(colPix));
			}
		}
		else //if resistor is green
		{
			for (int i = 1; i < resistor_hsv.cols - 1; i++)
			{
				Mat colPix = resistor_hsv(Rect(i-1, 0, 3, resistor_hsv.rows));
				//store the colour of each column of the resistor
				columnColours.push_back(decodeGreen(colPix));
			}
		}


		//getting colour sequence
		for (int j = 1; j < columnColours.size() - 1; j++)
		{
			if (columnColours[j - 1] == "resistor")
			{
				if ((columnColours[j + 1] != "resistor") && (columnColours[j] != "resistor") && (bandSequence.size() <5))
				{
					bandSequence.push_back(columnColours[j + 1]);
				}
			}

			//for diagnosing resistor values
			if (i == 52)
			{
				//cout << columnColours[j] << endl;
			}
			
		}
		
		//for diagnosing resistor values
		if (i == 52)
		{
			for (int j = 0; j < bandSequence.size(); j++)
			{
				//cout << bandSequence[j] << endl;
			}
			
		}

		//get the resistance
		__int64 resistance = getResistance(bandSequence);
		resistances.push_back(resistance);

		//write to image
		string text = to_string(resistance) + " Ohms, 1%";
		putText(src, text, rect_points[1], FONT_HERSHEY_PLAIN, 2, Scalar(0, 0, 255, 255),2);
	}

	//draw on rectangles
	src = src + drawing;
	
	//sorting resistances from lowest to highest. 
	sort(resistances.begin(), resistances.end());

	//pushing a value to the end of the vector so that it can print the last value
	resistances.push_back(0);

	//writing data into a file
	int n = 1;
	for (int i = 0; i < resistances.size(); i++)
	{
		
		if (i != resistances.size() - 1)
		{
			if (resistances[i + 1] == resistances[i])
			{
				n++;
			}
			else
			{
				//print each unique value
				myfile << to_string(resistances[i]) + " x" + to_string(n) + "\n";
				n = 1;
			}
		}
		
	}

	//output results
	myfile.close();
	cv::imwrite("Output.jpg", src);

	return 0;
}