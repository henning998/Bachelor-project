#ifndef CAMERA_H
#define CAMERA_H

#include "include.h"


class camera
{
private:
    raspicam::RaspiCam Camera;
    int img_buf_len;
    unsigned char* img_buf;
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

     void printParameter(raspicam::RaspiCam camera);
     void setupCamera(int width, int height, bool vert, bool hori, raspicam::RaspiCam* Camera);
     void BlobSetup(int minThresh, int maxThresh, bool filtercolor, int color, bool filterarea, int minimumArea, int maximumArea, cv::SimpleBlobDetector::Params* sbdPar);
public:
float x, size;
    camera(/* args */);
    ~camera();
    void getpicture();
    void changeGoal();
};

camera::camera(/* args */)
{
    printParameter(Camera);
    setupCamera(640, 480, true, true, &Camera);
    if (!Camera.open())
	{
		std::cerr << "Error opening camera." << std::endl;
		//return -1;
	}
    std::cout << "Waiting for camera stabilisation...";
	usleep(3000000);
	std::cout << "done" << std::endl;
    img_buf_len = Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_BGR);
	img_buf = new unsigned char[img_buf_len];

    BlobSetup(1, 1000, true, 255, true, 400, 160000, &sbdPara);
    sbd = cv::SimpleBlobDetector::create(sbdPara);
    	cv::namedWindow("HSV controls",cv::WINDOW_NORMAL);

	// Create trackbars for H, S and V in the window
	cv::createTrackbar("LowH", "HSV controls", &iLowH, 179); //Hue (0 - 179)
 	cv::createTrackbar("HighH", "HSV controls", &iHighH, 179);

 	cv::createTrackbar("LowS", "HSV controls", &iLowS, 255); //Saturation (0 - 255)
 	cv::createTrackbar("HighS", "HSV controls", &iHighS, 255);

 	cv::createTrackbar("LowV", "HSV controls", &iLowV, 255); //Value (0 - 255)
 	cv::createTrackbar("HighV", "HSV controls", &iHighV, 255);
}

camera::~camera()
{
    Camera.release();
}

void camera::getpicture()
{
    // Grab image into internal buffer
	Camera.grab();
	// Copy latest camera buffer into our buffer
	Camera.retrieve(img_buf);
    // Create OpenCV Mat image from image buffer
	imageMat = cv::Mat(Camera.getHeight(),Camera.getWidth(),CV_8UC3,img_buf);

	if (!imageMat.data)
	{
		std::cout << "No data in Mat imageMat." << std::endl;
		//return -1;
	}
    // Convert image from BGR to HSV
	cv::cvtColor(imageMat,imageMat,cv::COLOR_BGR2HSV);

	// Create new image Mat that holds the thresholded image data
	
	// Threshold image
	cv::inRange(imageMat,cv::Scalar(iLowH,iLowS,iLowV),cv::Scalar(iHighH,iHighS,iHighV),imageThreshold);

	//morphological opening (remove small objects from the foreground)
	erode(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
	dilate(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

	//morphological closing (fill small holes in the foreground)
	dilate(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
 	erode(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
    sbd->detect(imageThreshold,keypts);

    	// Create window and display OpenCV Mat image
	cv::namedWindow("HSV image",cv::WINDOW_AUTOSIZE);
	cv::imshow("HSV image", imageMat);

	// Display thresholded image, window is automatically created
	cv::namedWindow("Thresholded image",cv::WINDOW_AUTOSIZE);
	cv::imshow("Thresholded image",imageThreshold);

	cv::drawKeypoints(imageThreshold,keypts,imageKeypoints,cv::Scalar(0,0,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    	
    cv::namedWindow("Blobs",cv::WINDOW_AUTOSIZE);
	cv::imshow("Blobs",imageKeypoints);

	cv::KeyPoint::convert(keypts,keyptXY);
     
	if (keyptXY.size() == 1){
    x = keyptXY.front().x;
    size = keypts.front().size/300; 
		std::cout << "[x,y] = " << "[" << x << "," << keyptXY.front().y << "]" << size <<std::endl;
  }
}

void camera::printParameter(raspicam::RaspiCam Camera)
{
// Check camera parameters
        std::cout << "Format: " << Camera.getFormat() << std::endl;
        std::cout << "Width: " << Camera.getWidth() << std::endl;
        std::cout << "Height: " << Camera.getHeight() << std::endl;
        std::cout << "Brightness: " << Camera.getBrightness() << std::endl;
        std::cout << "Rotation: " << Camera.getRotation() << std::endl;
        std::cout << "ISO: " << Camera.getISO() << std::endl;
        std::cout << "Sharrpness: " << Camera.getSharpness() << std::endl;
        std::cout << "Contrast: " << Camera.getContrast() << std::endl;
        std::cout << "Saturation: " << Camera.getSaturation() << std::endl;
        std::cout << "ShutterSpeed: " << Camera.getShutterSpeed() << std::endl;
        std::cout << "Exopsure: " << Camera.getExposure() << std::endl;
        std::cout << "AWB: " << Camera.getAWB() << std::endl;
        std::cout << "Image effect: " << Camera.getImageEffect() << std::endl;
        std::cout << "Metering: " << Camera.getMetering() << std::endl;
		std::cout << "Format:" << Camera.getFormat() << std::endl;
}

void camera::setupCamera(int width, int height, bool vert, bool hori, raspicam::RaspiCam* Camera)
{
// Set camera image format to BGR as used by  OpenCV
	Camera->setFormat(raspicam::RASPICAM_FORMAT_BGR);

	std::cout << "...changed to 2 (BGR)" << std::endl;

	// Set image resolution
	Camera->setWidth(width); //640
	Camera->setHeight(height); //480

	// Flip camera image vertically and horizontally
	// because camera is mounted upside down
	Camera->setVerticalFlip(vert); //true
	Camera->setHorizontalFlip(hori); //true
}

void camera::BlobSetup(int minThresh, int maxThresh, bool filtercolor, int color, bool filterarea, int minimumArea, int maximumArea, cv::SimpleBlobDetector::Params* sbdPar)
{   
    // Change thresholds
	sbdPar->minThreshold = minThresh; // 1
	sbdPar->maxThreshold = maxThresh; // 1000
	// Filter by colour
	sbdPar->filterByColor = filtercolor; // True
	// Look for colours that match grayscale value of 255 (white)
	sbdPar->blobColor=color; // 255
	// Filter by area
	sbdPar->filterByArea = filterarea; // true
	sbdPar->minArea = minimumArea; // 100x100 pixels // 10000
	sbdPar->maxArea = maximumArea; // 400x400 pixels //160000
}

void camera::changeGoal()
{
    
}
#endif