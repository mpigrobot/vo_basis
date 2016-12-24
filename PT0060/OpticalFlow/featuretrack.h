#include <iostream>
#include <fstream>
#include <string>
#include "opencv2/opencv.hpp"

using  namespace std;
using namespace cv;

void featureTracking(Mat img_1, Mat img_2, vector<Point2f>& points1, vector<Point2f>& points2, vector<uchar>& status)	{ 

//this function automatically gets rid of points for which tracking fails

  vector<float> err;					
  Size winSize=Size(15,15);																								
  TermCriteria termcrit=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, 0.01);

  calcOpticalFlowPyrLK(img_1, img_2, points1, points2, status, err, winSize, 3, termcrit, 0, 0.001);

  //getting rid of points for which the KLT tracking failed or those who have gone outside the frame
  int indexCorrection = 0;
  for( int i=0; i<status.size(); i++)

     {  
		Point p1 = Point (points1[i].x,points1[i].y);
		Point p2 = Point (points2[i].x,points2[i].y);
		 Point2f pt = points2.at(i- indexCorrection);
     	if ((status.at(i) == 0)||(pt.x<0)||(pt.y<0))	{
			line(img_2,p1,p2,Scalar(0,0,255));
     		 if((pt.x<0)||(pt.y<0))	{
     		  	status.at(i) = 0;
     		  }
     		/*  points1.erase (points1.begin() + i - indexCorrection);
     		  points2.erase (points2.begin() + i - indexCorrection);
     		  indexCorrection++;*/
     	}
		else{
		line(img_2,p1,p2,Scalar(0,255,0));
		}
     }
}