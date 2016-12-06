#include <stdio.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;

int main( int argc, char** argv )
{
	Mat img1 = imread( "..//images//chapel00.png");//change the path if it was wrong in your computer.
    Mat img2 = imread("..//images//chapel01.png");

	// detectingkeypoints
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

// matching descriptors

FlannBasedMatcher matcher; //Brute-Force use this: BruteForceMatcher<L2<float>> matcher;
  std::vector< DMatch > matches;
  matcher.match(descriptors1,descriptors2,matches);

  //-- Draw matches
  Mat img_matches;
  drawMatches( img1, keypoints1, img2, keypoints2, matches, img_matches );

  //-- Show detected matches
  imshow("Matches", img_matches );
  
  //that's one of the methods to the eliminate errors of matching:
  /*
  double max_dist = 0; double min_dist = 100;

  //-- Quick calculation of max and min distances between keypoints
  for( int i=0; i<descriptors1.rows; i++ )
  { double dist = matches[i].distance;
    if( dist < min_dist ) min_dist = dist;
    if( dist > max_dist ) max_dist = dist;
  }

  //-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist )
  std::vector< DMatch > good_matches;

  for( int i = 0; i < descriptors1.rows; i++ )
  { if( matches[i].distance < 2*min_dist )
    { good_matches.push_back( matches[i]); }
  }

  //-- Draw only "good" matches
  Mat img_matches;
  drawMatches( img1, keypoints1, img2, keypoints2,
               good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
               vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

  //-- Show detected matches
  imshow( "Good Matches", img_matches );
  */

  waitKey(0);

  return 0;
}