#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;


void estimateMotion(vector<Point2f>& imgpoints1, vector<Point2f>& imgpoints2, Matx34d& P1);
