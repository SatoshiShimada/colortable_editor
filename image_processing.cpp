
#include <cstdio>

#include "image_processing.h"

ImageProcessing::ImageProcessing() : isAllocatedDataMemory(false), data(NULL), width(0), height(0)
{
}

ImageProcessing::~ImageProcessing()
{
	if(isAllocatedDataMemory) {
		delete data;
		isAllocatedDataMemory = false;
	}
}

void ImageProcessing::setImageData(int width, int height, unsigned char *imageData)
{
	if(isAllocatedDataMemory)
		delete data;
	data = new unsigned char[width * height * 3];
	isAllocatedDataMemory = true;
	this->width = width;
	this->height = height;
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			data[(h * width + w) * 3 + 0] = imageData[(h * width + w) * 3 + 0];
			data[(h * width + w) * 3 + 1] = imageData[(h * width + w) * 3 + 1];
			data[(h * width + w) * 3 + 2] = imageData[(h * width + w) * 3 + 2];
		}
	}
}

