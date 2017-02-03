
#include <cstdio>
#include <iostream>

#include "image_processing.h"

ImageProcessing::ImageProcessing(int width, int height) : width(width), height(height)
{
}

ImageProcessing::~ImageProcessing()
{
}

void ImageProcessing::erosion(unsigned char *data)
{
	unsigned char *buf = new unsigned char[width * height];
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			int wdec = std::max<int>(w - 1, 0);
			int winc = std::min<int>(w + 1, width - 1);
			int hdec = std::max<int>(h - 1, 0);
			int hinc = std::min<int>(h + 1, height - 1);
			unsigned char p1 = data[hdec * width + w   ];
			unsigned char p2 = data[h    * width + wdec];
			unsigned char p3 = data[h    * width + w   ];
			unsigned char p4 = data[h    * width + winc];
			unsigned char p5 = data[hinc * width + w   ];
			if(p1 && p2 && p3 && p4 && p5) {
				buf[h * width + w] = 255;
			} else {
				buf[h * width + w] = 0;
			}
		}
	}
	for(int i = 0; i < width * height; i++)
		data[i] = buf[i];
	delete[] buf;
}

void ImageProcessing::dilation(unsigned char *data)
{
	unsigned char *buf = new unsigned char[width * height];
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			int wdec = std::max<int>(w - 1, 0);
			int winc = std::min<int>(w + 1, width - 1);
			int hdec = std::max<int>(h - 1, 0);
			int hinc = std::min<int>(h + 1, height - 1);
			unsigned char value = 255;
			if(data[h * width + w] == 255) {
				buf[hdec * width + w   ] = value;
				buf[h    * width + wdec] = value;
				buf[h    * width + w   ] = value;
				buf[h    * width + winc] = value;
				buf[hinc * width + w   ] = value;
			}
		}
	}
	for(int i = 0; i < width * height; i++)
		data[i] = buf[i];
	delete[] buf;
}

