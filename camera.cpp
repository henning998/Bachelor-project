#include "camera.h"

camera::camera()
{
	printParameter(Camera);
	setupCamera(320, 240, true, true, &Camera);
	if (!Camera.open()) // Is the camera open
	{
		std::cerr << "Error opening camera." << std::endl;
	}
	std::cout << "Waiting for camera stabilisation...";
	usleep(3000000);
	std::cout << "done" << std::endl;
	img_buf_len = Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_BGR);
	img_buf = new unsigned char[img_buf_len];

	BlobSetup(1, 1000, true, 255, true, 100, 40000, true, 0.01, &sbdPara);
	sbd = cv::SimpleBlobDetector::create(sbdPara);
	cv::namedWindow("HSV controls", cv::WINDOW_NORMAL);

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
	new_pic = false;
	// Grab image into internal buffer
	Camera.grab();
	// Copy latest camera buffer into our buffer
	Camera.retrieve(img_buf);
	// Create OpenCV Mat image from image buffer
	imageMat = cv::Mat(Camera.getHeight(), Camera.getWidth(), CV_8UC3, img_buf);

	if (!imageMat.data)
	{
		std::cout << "No data in Mat imageMat." << std::endl;
	}
	// Convert image from BGR to HSV
	cv::cvtColor(imageMat, imageMat, cv::COLOR_BGR2HSV);

	// Create new image Mat that holds the thresholded image data

	// Threshold image
	cv::inRange(imageMat, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imageThreshold);

	//Morphological opening (remove small objects from the foreground)
	erode(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	dilate(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

	//Morphological closing (fill small holes in the foreground)
	dilate(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	erode(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	sbd->detect(imageThreshold, keypts);

	// Create window and display OpenCV Mat image
	cv::namedWindow("HSV image", cv::WINDOW_AUTOSIZE);
	cv::imshow("HSV image", imageMat);

	// Display thresholded image, window is automatically created
	cv::namedWindow("Thresholded image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Thresholded image", imageThreshold);

	cv::drawKeypoints(imageThreshold, keypts, imageKeypoints, cv::Scalar(0, 0, 255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	cv::namedWindow("Blobs", cv::WINDOW_AUTOSIZE);
	cv::imshow("Blobs", imageKeypoints);

	cv::KeyPoint::convert(keypts, keyptXY);

	// If there are a blob get the x, y & size
	if (keyptXY.size() == 1)
	{
		x = keyptXY.front().x;
		size = keypts.front().size / 150;
		//std::cout << "[x,y] = "
		//		  << "[" << x << "," << keyptXY.front().y << "]" << size << std::endl;
		new_pic = true;
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

void camera::setupCamera(int width, int height, bool vert, bool hori, raspicam::RaspiCam *Camera)
{
	// Set camera image format to BGR as used by  OpenCV
	Camera->setFormat(raspicam::RASPICAM_FORMAT_BGR);

	std::cout << "...changed to 2 (BGR)" << std::endl;

	// Set image resolution
	Camera->setWidth(width);   //640
	Camera->setHeight(height); //480

	// Flip camera image vertically and horizontally
	// because camera is mounted upside down
	Camera->setVerticalFlip(vert);	 //true
	Camera->setHorizontalFlip(hori); //true
}

void camera::BlobSetup(int minThresh, int maxThresh, bool filtercolor, int color, bool filterarea, int minimumArea, int maximumArea, bool filtercircle, float Circularity, cv::SimpleBlobDetector::Params *sbdPar)
{
	// Change thresholds
	sbdPar->minThreshold = minThresh; // 1
	sbdPar->maxThreshold = maxThresh; // 1000
	// Filter by colour
	sbdPar->filterByColor = filtercolor; // True
	// Look for colours that match grayscale value of 255 (white)
	sbdPar->blobColor = color; // 255
	// Filter by area
	sbdPar->filterByArea = filterarea; // True
	sbdPar->minArea = minimumArea;	   // 100x100 pixels // 10000
	sbdPar->maxArea = maximumArea;	   // 400x400 pixels //160000
	// filter by circularity
	sbdPar->filterByCircularity = filtercircle;
	sbdPar->minCircularity = Circularity;
	// Filter by Convexity
	sbdPar->filterByConvexity = true;
	sbdPar->minConvexity = 0.80;
	// Filter by Inertia
	sbdPar->filterByInertia = true;
	sbdPar->minInertiaRatio = 0.01;
}

void camera::change2red()
{
	iLowH = 160;
	iHighH = 179;
	iLowS = 60;
	iHighS = 230;
	iLowV = 0;
	iHighV = 255;
}

void camera::change2blue()
{
	iLowH = 100;
	iHighH = 110;

	iLowS = 110;
	iHighS = 230;

	iLowV = 0;
	iHighV = 255;
}

void camera::change2green()
{
	iLowH = 42;
	iHighH = 86;

	iLowS = 57;
	iHighS = 172;

	iLowV = 25;
	iHighV = 255;
}