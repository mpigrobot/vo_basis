#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/legacy/legacy.hpp"

using namespace cv;

int main( int argc, char** argv )
{
Mat img1 = imread("..//images//chapel00.png");//change the path if it was wrong in your computer.
Mat img2 = imread("..//images//chapel01.png");

int minHessian = 400; 
SurfFeatureDetector detector( minHessian );

  std::vector<KeyPoint> keypoints1, keypoints2;
detector.detect(img1, keypoints1);
detector.detect(img2, keypoints2);

// computing descriptors
SurfDescriptorExtractor extractor;
Mat descriptors1, descriptors2;
extractor.compute(img1, keypoints1, descriptors1);
extractor.compute(img2, keypoints2, descriptors2);

//-- Draw keypoints
  Mat img_keypoints_1; Mat img_keypoints_2;

 drawKeypoints( img1, keypoints1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
 drawKeypoints( img2, keypoints2, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

  //-- Show detected (drawn) keypoints
  imshow("Keypoints 1", img_keypoints_1 );
  imshow("Keypoints 2", img_keypoints_2 );

  waitKey(0);

  return 0;
}