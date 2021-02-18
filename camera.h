#ifndef CAMERA_H
#define CAMERA_H

#include "include.h"

void printParameter(raspicam::RaspiCam Camera)
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

void setupCamera(int width, int height, bool vert, bool hori, raspicam::RaspiCam* Camera)
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

#endif