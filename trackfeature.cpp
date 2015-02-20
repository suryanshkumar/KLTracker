/**
 * Author: Suryansh Kumar
 *
 **/

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/video/tracking.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "trackfeature.h"
#include <iostream>
#include <QDebug>

using namespace cv;
using namespace std;

Mat trackfeature::getWarpImage(){
    Mat warp_src;
    HMatrix = findHomography(goodFeatures, trackedFeatures, CV_RANSAC, 1);
    cv::warpPerspective(image2, warp_src, HMatrix, image2.size(), CV_INTER_LINEAR+CV_WARP_FILL_OUTLIERS+CV_WARP_INVERSE_MAP);
    //std::cout <<HMatrix <<std::endl;
    return warp_src;
}


void trackfeature::detectfeature(){
    qualityLevel = 0.01;
    minDistance = 10;
    blockSize = 3;
    useHarrisDetector = false;
    k = 0.04;
    maxCorners = 5000;
    cv::Mat src_gray;
    cvtColor(image1, src_gray, CV_BGR2GRAY);
    cv::goodFeaturesToTrack( src_gray, goodFeatures, maxCorners, qualityLevel, minDistance, Mat(), blockSize, useHarrisDetector, k );
    cout<<goodFeatures.size()<<endl;
}

void trackfeature::match(){
    vector<uchar> status;
    vector<float> err;
    Size winsize = Size(31,31);
    int maxlevel =3;
    TermCriteria criteria = TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, 0.01);
    double derivlambda=0.5;
    int flags=0;
    cv::calcOpticalFlowPyrLK(image1, image2, goodFeatures, trackedFeatures, status, err, winsize, maxlevel, criteria, derivlambda, flags);
}


Mat trackfeature::drawfeaturePoints(){
    Mat src_copy;
    image1.copyTo(src_copy);
    int thickness =2;
    int radius =1;
    std::vector<cv::Point2f> :: const_iterator it = goodFeatures.begin();
    while(it!=goodFeatures.end()){
    cv::circle(src_copy, *it, radius, Scalar(0, 255, 0), thickness);
        ++it;
        }
   return src_copy;
}


Mat trackfeature::drawfeatureTrack(){
    Mat src_copy;
    image2.copyTo(src_copy);
    std::vector<Point2f> :: const_iterator itc = goodFeatures.begin();
    std::vector<Point2f> :: const_iterator itf = trackedFeatures.begin();
    while(itc!=goodFeatures.end()){
        circle(src_copy, *itc, 1, Scalar(0, 0, 255), 2, 8, 0);
        circle(src_copy, *itf, 1, Scalar(255, 0, 0), 2, 8, 0);
        cv::line(src_copy, *itc, *itf, Scalar(0,255,0) );
        itc++;
        itf++;
            }
        return src_copy;
}


trackfeature::trackfeature(Mat I1, Mat I2){
    I1.copyTo(image1);
    I2.copyTo(image2);
    detectfeature();
    match();
}







