#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "featuretrack.h"
#include "estimateMotion.h"

using namespace cv;

int main( int argc, char** argv )
{
	Mat img1 = imread( "F://Chen Weijie//code//CV//leaningopenCV//leaningopenCV//chapel00.png");
    Mat img2 = imread("F://Chen Weijie//code//CV//leaningopenCV//leaningopenCV//chapel01.png");

	// detectingkeypoints
int minHessian = 400;

  SurfFeatureDetector detector( minHessian );

  std::vector<KeyPoint> keypoints1;
detector.detect(img1, keypoints1);


// matching descriptors

vector<uchar> status;
vector<Point2f>points1,points2;
KeyPoint::convert(keypoints1, points1, vector<int>());
featureTracking(img1,img2, points1,points2,status);


imshow("OpticalFlow",img2);

Matx34d P1;

estimateMotion(points1,points2,P1);
cout<<P1;

  waitKey(0);

  return 0;
}