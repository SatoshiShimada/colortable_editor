
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
				buf[h * width + w] = 1;
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
	for(int i = 0; i < width * height; i++)
		buf[i] = 0;
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			int wdec = std::max<int>(w - 1, 0);
			int winc = std::min<int>(w + 1, width - 1);
			int hdec = std::max<int>(h - 1, 0);
			int hinc = std::min<int>(h + 1, height - 1);
			unsigned char value = 1;
			if(data[h * width + w] != 0) {
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

void ImageProcessing::labeling(unsigned char *data)
{
	unsigned char *buf = new unsigned char[width * height];
	const int lookup_table_size = 256; /* 8bits */
	int lookup_table[lookup_table_size];
	int last_num = 0;
	for(int i = 0; i < width * height; i++)
		buf[i] = 0;
	for(int i = 0; i < lookup_table_size; i++)
		lookup_table[i] = i;
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			if(data[h * width + w] != 0) {
				int wdec = std::max<int>(w - 1, 0);
				int winc = std::min<int>(w + 1, width - 1);
				int hdec = std::max<int>(h - 1, 0);
				int hinc = std::min<int>(h + 1, height - 1);
				unsigned char value[4];
				value[0] = data[hdec * width + wdec];
				value[1] = data[hdec * width + w   ];
				value[2] = data[hdec * width + winc];
				value[3] = data[h    * width + wdec];
				if(value[1] == 0 && value[2] == 0 && value[3] == 0 && value[4] == 0) {
					buf[h * width + w] = last_num + 1;
					last_num++;
					if(last_num > 255) {
						return;
					}
				} else {
					unsigned char min_value = 255;
					for(int i = 0; i < 4; i++) {
						if(value[i] == 0) continue;
						if(value[i] < min_value)
							min_value = value[i];
					}
					for(int i = 0; i < 4; i++) {
						buf[h * width + w] = min_value;
						if(value[i] != 0 && value[i] != min_value)
							lookup_table[i] = min_value;
					}
				}
			}
		}
	}
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			unsigned char value = buf[h * width + w];
			if(value != 0) {
				buf[h * width + w] = lookup_table[(int)value];
			}
		}
	}
	for(int i = 0; i < width * height; i++)
		data[i] = buf[i];
	delete[] buf;
}

