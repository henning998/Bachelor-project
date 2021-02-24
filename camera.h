#ifndef CAMERA_H
#define CAMERA_H

#include "include.h"

class camera
{
private:
	raspicam::RaspiCam Camera;
	int img_buf_len;
	unsigned char *img_buf;
	cv::Mat imageMat;
	cv::Mat imageThreshold;
	cv::SimpleBlobDetector::Params sbdPara;
	cv::Ptr<cv::SimpleBlobDetector> sbd;
	std::vector<cv::KeyPoint> keypts;
	int iLowH = 160;
	int iHighH = 175;

	int iLowS = 60;
	int iHighS = 230;

	int iLowV = 0;
	int iHighV = 255;
	cv::Mat imageKeypoints;
	std::vector<cv::Point2f> keyptXY;

	void printParameter(raspicam::RaspiCam camera);											   // print parameter
	void setupCamera(int width, int height, bool vert, bool hori, raspicam::RaspiCam *Camera); // setup camera
	// setup blobdetection
	void BlobSetup(int minThresh, int maxThresh, bool filtercolor, int color, bool filterarea, int minimumArea, int maximumArea, cv::SimpleBlobDetector::Params *sbdPar);

public:
	float x = 320, size;
	camera(/* args */); // handle setup of everything related to the camera
	~camera();			// release the pi camera
	void getpicture();	// handle everything related to getting af pivture from the camera
	void change2red();	// look for red blob
	void change2blue(); // look for blue blob
	void change2green();
};

#endif