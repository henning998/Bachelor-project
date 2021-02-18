#ifndef BLOB_H
#define BLOB_H

#include "include.h"

void BlobSetup(int minThresh, int maxThresh, bool filtercolor, int color, bool filterarea, int minimumArea, int maximumArea, cv::SimpleBlobDetector::Params* sbdPar)
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



#endif