#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/opencv.hpp"
#include "featuretrack.h"

using namespace cv;

int main( int argc, char** argv )
{
	Mat img1 = imread( "..//images//chapel00.png");
    Mat img2 = imread("..//images//chapel01.png");

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

  waitKey(0);

  return 0;
}