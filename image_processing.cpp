
#include <cstdio>
#include <iostream>

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

void ImageProcessing::getImageData(unsigned char *imageData)
{
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			imageData[(h * width + w) * 3 + 0] = data[(h * width + w) * 3 + 0];
			imageData[(h * width + w) * 3 + 1] = data[(h * width + w) * 3 + 1];
			imageData[(h * width + w) * 3 + 2] = data[(h * width + w) * 3 + 2];
		}
	}
}

void ImageProcessing::erosion(void)
{
	unsigned char *buf = new unsigned char[width * height * 3];
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			int wdec = std::max<int>(w - 1, 0);
			int winc = std::min<int>(w + 1, width - 1);
			int hdec = std::max<int>(h - 1, 0);
			int hinc = std::min<int>(h + 1, height - 1);
			unsigned char p1 = data[(hdec * width + w   ) * 3 + 0];
			unsigned char p2 = data[(h    * width + wdec) * 3 + 0];
			unsigned char p3 = data[(h    * width + w   ) * 3 + 0];
			unsigned char p4 = data[(h    * width + winc) * 3 + 0];
			unsigned char p5 = data[(hinc * width + w   ) * 3 + 0];
			if(p1 && p2 && p3 && p4 && p5) {
				buf[(h * width + w) * 3 + 0] = 255;
			} else {
				buf[(h * width + w) * 3 + 0] = 0;
			}
			buf[(h*width+w)*3+1] = 0;
		}
	}
	delete data;
	data = buf;
}

void ImageProcessing::dilation(void)
{
	unsigned char *buf = new unsigned char[width * height * 3];
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			int wdec = std::max<int>(w - 1, 0);
			int winc = std::min<int>(w + 1, width - 1);
			int hdec = std::max<int>(h - 1, 0);
			int hinc = std::min<int>(h + 1, height - 1);
			unsigned char value = 255;
			if(data[(h * width + w) * 3 + 0] == 255) {
				buf[(hdec * width + w   ) * 3 + 0] = value;
				buf[(h    * width + wdec) * 3 + 0] = value;
				buf[(h    * width + w   ) * 3 + 0] = value;
				buf[(h    * width + winc) * 3 + 0] = value;
				buf[(hinc * width + w   ) * 3 + 0] = value;
			}
		}
	}
	delete data;
	data = buf;
}

