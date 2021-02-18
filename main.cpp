#include "include.h"

//using namespace std;
//using namespace cv;

int main (int argc, char** argv)
{
	// Create Raspberry Pi camera object
	raspicam::RaspiCam Camera;
	
	printParameter(Camera);

	cv::SimpleBlobDetector::Params sbdPara;
	
	BlobSetup(1, 1000, true, 255, true, 10000, 160000, sbdPara);

	setupCamera(640, 480, true, true, &Camera);

	cv::Ptr<cv::SimpleBlobDetector> sbd = cv::SimpleBlobDetector::create(sbdPara);
	std::vector<cv::KeyPoint> keypts;

	// Open camera
	if (!Camera.open())
	{
		std::cerr << "Error opening camera." << std::endl;
		return -1;
	}

	// Wait 3 seconds for camera image to stabilise
	std::cout << "Waiting for camera stabilisation...";
	usleep(3000000);
	std::cout << "done" << std::endl;

	// Create buffer of correct size to store image data
	int img_buf_len = Camera.getImageTypeSize(raspicam::RASPICAM_FORMAT_BGR);
	unsigned char *img_buf=new unsigned char[img_buf_len];

	// Set minimum and maximum values for hue, saturation and value
	std::vector<int> HSV_vector = {170, 179, 0, 255, 0 ,255};

	HSV(HSV_vector); 

	while(true)
	{
	// Grab image into internal buffer
	Camera.grab();

	// Copy latest camera buffer into our buffer
	Camera.retrieve(img_buf);

	// Create OpenCV Mat image from image buffer
	cv::Mat imageMat = cv::Mat(Camera.getHeight(),Camera.getWidth(),CV_8UC3,img_buf);

	if (!imageMat.data)
	{
		std::cout << "No data in Mat imageMat." << std::endl;
		return -1;
	}

	// Convert image from BGR to HSV
	cv::cvtColor(imageMat,imageMat,cv::COLOR_BGR2HSV);

	// Create new image Mat that holds the thresholded image data
	cv::Mat imageThreshold;
	// Threshold image
	cv::inRange(imageMat,cv::Scalar(HSV_vector[0],HSV_vector[2],HSV_vector[4]),cv::Scalar(HSV_vector[1],HSV_vector[3],HSV_vector[5]),imageThreshold);

	//morphological opening (remove small objects from the foreground)
	erode(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
	dilate(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

	//morphological closing (fill small holes in the foreground)
	dilate(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );
 	erode(imageThreshold, imageThreshold, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)) );

	// Create window and display OpenCV Mat image
	cv::namedWindow("HSV image",cv::WINDOW_AUTOSIZE);
	cv::imshow("HSV image", imageMat);

	// Display thresholded image, window is automatically created
	cv::namedWindow("Thresholded image",cv::WINDOW_AUTOSIZE);
	cv::imshow("Thresholded image",imageThreshold);

	cv::Mat imageKeypoints;

	sbd->detect(imageThreshold,keypts);

	cv::drawKeypoints(imageThreshold,keypts,imageKeypoints,cv::Scalar(0,0,255),cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	cv::namedWindow("Blobs",cv::WINDOW_AUTOSIZE);
	cv::imshow("Blobs",imageKeypoints);

	std::vector<cv::Point2f> keyptXY;
	cv::KeyPoint::convert(keypts,keyptXY);

	if (keyptXY.size() == 1)
		std::cout << "[x,y] = " << "[" << keyptXY.front().x << "," << keyptXY.front().y << "]" << std::endl;

	if (cv::waitKey(30) == 27)
	{
		// Release camera resources
		Camera.release();
		break;
	}
	}

	return 0;
}
