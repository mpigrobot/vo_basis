#include "estimateMotion.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

 void estimateMotion(vector<Point2f>& imgpoints1, vector<Point2f>& imgpoints2, Matx34d& P1) {

   
  // create calibration matrix. 
  Mat K = (Mat_<double>(3, 3) << 718.856,0,607.1928,0,718.856,185.2517,0,0,1);
    

  // initial RANSAC estimate of F
vector<uchar> mask;

Mat F=findFundamentalMat( imgpoints1, imgpoints2,mask,FM_RANSAC, 0.88, 0.99);

 
Mat_<double> E = K.t() * F * K;

SVD svd(E,SVD::MODIFY_A);
Mat svd_u = svd.u;
Mat svd_vt = svd.vt;
Mat svd_w = svd.w;
Matx33d W(0,-1,0,//HZ 9.13
1,0,0,
0,0,1);

Mat_<double> R = svd_u * Mat(W) * svd_vt; //HZ 9.19
Mat_<double> t = svd_u.col(2); //u3

P1 = Matx34d(R(0,0),R(0,1),R(0,2),t(0),
R(1,0),R(1,1),R(1,2),t(1),
R(2,0),R(2,1),R(2,2),t(2));


}