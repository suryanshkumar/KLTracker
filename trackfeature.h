/**
 * Author: Suryansh Kumar
 *
 **/

#ifndef TRACKFEATURE_H
#define TRACKFEATURE_H

#include <iostream>
#include <string.h>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>


using namespace std;
using namespace cv;


class trackfeature{

 private:
    double qualityLevel;
    double minDistance;
    int blockSize;
    bool useHarrisDetector;
    double k;
    int maxCorners;

protected:
    cv::Mat image1, image2;
    std::vector<Point2f> goodFeatures;
    std::vector<Point2f> trackedFeatures;
    void match();


public:
    cv::Mat HMatrix;
    trackfeature(cv::Mat, cv::Mat);
    void detectfeature();
    cv::Mat drawfeaturePoints();
    cv::Mat drawfeatureTrack();
    cv::Mat getWarpImage();

};




#endif // TRACKFEATURE_H
