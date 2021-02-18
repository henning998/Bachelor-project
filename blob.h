#ifndef BLOB_H
#define BLOB_H

#include "include.h"

cv::SimpleBlobDetector::Params BlobSetup(int minThresh, int maxThresh, bool filtercolor, int color, bool filterarea, int minimumArea, int maximumArea, cv::SimpleBlobDetector::Params sbdPar)
{   
    // Change thresholds
	sbdPar.minThreshold = minThresh; // 1
	sbdPar.maxThreshold = maxThresh; // 1000
	// Filter by colour
	sbdPar.filterByColor = filtercolor; // True
	// Look for colours that match grayscale value of 255 (white)
	sbdPar.blobColor=color; // 255
	// Filter by area
	sbdPar.filterByArea = filterarea; // true
	sbdPar.minArea = minimumArea; // 100x100 pixels // 10000
	sbdPar.maxArea = maximumArea; // 400x400 pixels //160000

    return sbdPar;
}

std::vector<int> HSV(std::vector<int> HSV_vector)
{
	// Create a window
	cv::namedWindow("HSV controls",cv::WINDOW_NORMAL);

	// Create trackbars for H, S and V in the window
	cv::createTrackbar("LowH", "HSV controls", &HSV_vector[0], 179); //Hue (0 - 179)
 	cv::createTrackbar("HighH", "HSV controls", &HSV_vector[1], 179);

 	cv::createTrackbar("LowS", "HSV controls", &HSV_vector[2], 255); //Saturation (0 - 255)
 	cv::createTrackbar("HighS", "HSV controls", &HSV_vector[3], 255);

 	cv::createTrackbar("LowV", "HSV controls", &HSV_vector[4], 255); //Value (0 - 255)
 	cv::createTrackbar("HighV", "HSV controls", &HSV_vector[5], 255);    

    return HSV_vector; 
}


#endif