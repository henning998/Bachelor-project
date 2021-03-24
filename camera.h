#ifndef CAMERA_H
#define CAMERA_H

#include "include.h"

class camera
{
private:
	raspicam::RaspiCam Camera;				//Raspberry pi camera object
	int img_buf_len;						// Length of the image buffer
	unsigned char *img_buf;					// Data from the picam
	cv::Mat imageMat;						// Opencv Matrix to hold the image from the raspberry pi camera
	cv::Mat imageThreshold;					// Holds the thresholded image
	cv::SimpleBlobDetector::Params sbdPara; // Parameters for simpel blob detection
	cv::Ptr<cv::SimpleBlobDetector> sbd;	// Pointer to simple blob detection
	std::vector<cv::KeyPoint> keypts;		// Vector that holds the keypoints from blob detection
	//Values for HSV
	int iLowH = 160;
	int iHighH = 175;

	int iLowS = 60;
	int iHighS = 230;

	int iLowV = 0;
	int iHighV = 255;

	cv::Mat imageKeypoints;			  //Matrix that holds the keypoint image
	std::vector<cv::Point2f> keyptXY; //Vector that hold the keypoints transformed to x-y-coordinates

	// Print parameter
	void printParameter(raspicam::RaspiCam camera);
	// Setup camera
	void setupCamera(int width, int height, bool vert, bool hori, raspicam::RaspiCam *Camera);
	// Setup blobdetection
	void BlobSetup(int minThresh, int maxThresh, bool filtercolor, int color, bool filterarea, int minimumArea, int maximumArea, cv::SimpleBlobDetector::Params *sbdPar);

public:
	float x = 160, size = 0; // Hold the x-coordinate and the size of the blob
	bool new_pic = false;	  // Is there a new blob detected, in the newest image
	// Handle setup of everything related to the camera
	camera();
	// Release the pi camera
	~camera();
	// Handle everything related to getting af picture from the camera
	void getpicture();
	// Look for red blob
	void change2red();
	// Look for blue blob
	void change2blue();
	// Look for green blob
	void change2green();
};

#endif