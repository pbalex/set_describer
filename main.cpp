#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui.hpp>
#include <iostream>
#include <queue>
using namespace cv;
using namespace std;

class Point_vals {
public: 
	Point_vals(Point p_in, float f_in) : p(p_in), f(f_in) {}
	void set_vals(int x, int y, float f_in) {
		p = Point(x, y);
		f = f_in;
	}
	bool operator>(const Point_vals &rhs) {	return this->f > rhs.f;	}

	Point p;
	float f;
};

const int trackbar_max = 5;
Mat image, templ, out;
int match_method;
priority_queue<Point_vals> pq;

void make_pq();
void move_trackbar(int, void*);
bool Point_vals_comp(const Point_vals &lhs, const Point_vals &rhs);


int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << " Usage: image_to_check image_template" << endl;
		return -1;
	}
	image = imread(argv[1], IMREAD_COLOR); // Read image
	templ = imread(argv[2], IMREAD_COLOR);//Read template

	if (!image.data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	namedWindow("Template Image", WINDOW_NORMAL);
	namedWindow("MMB Member Search", WINDOW_NORMAL);

	imshow("MMB Member Search", image);
	imshow("Template Image", templ);

	string trackbar = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
	createTrackbar(trackbar, "MMB Member Search", &match_method, trackbar_max, move_trackbar);


	waitKey(0); // Wait for a keystroke in the window
	return 0;
}

void make_pq() {
	float result = 0;
	float* row;
	for (int i = 0; i < out.rows; ++i) {
		row = out.ptr<float>(i);
		for (int j = 0; j < out.cols; ++j) {
			pq.push(Point_vals(Point(i,j), row[j]));
		}
	}
}

void move_trackbar(int, void*) {

	/// Create the result matrix
	int result_cols = image.cols - templ.cols + 1;
	int result_rows = image.rows - templ.rows + 1;

	out.create(result_rows, result_cols, CV_32FC1);

	/// Do the Matching and Normalize
	matchTemplate(image, templ, out, match_method);
	normalize(out, out, 0, 1, NORM_MINMAX, -1, Mat());

	Point_vals current_vals();
	
	for (int i = 0; )


	// Show me what you got
	rectangle(out, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 8, 0, 0);

	imshow("MMB Member Search", out);

	//empty pq
	while (!pq.empty()) pq.pop();
}






/*

/// Localizing the best match with minMaxLoc
double minVal, maxVal; Point minLoc, maxLoc, matchLoc;

minMaxLoc(out, &minVal, &maxVal, &minLoc, &maxLoc);


/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED) {
matchLoc = minLoc;
}
else {
matchLoc = maxLoc;
}*/



bool Point_vals_comp(const Point_vals &lhs, const Point_vals &rhs) {
	if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED) {
		return lhs.
}