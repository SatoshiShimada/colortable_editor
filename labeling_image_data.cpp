
#include <iostream>

#include "labeling_image_data.h"

LabelingImageData::LabelingImageData(int width, int height, int category_num) : width(width), height(height), category_num(category_num), currentIndex(0), margin(0), imageprocessing(width, height)
{
	original_data = new unsigned char [width * height * 3];
	color_data    = new unsigned char [width * height * 3];
	for(int i = 0; i < width * height * 3; i++) {
		original_data[i] = 0;
		color_data[i]    = 0;
	}
	for(int c = 0; c < category_num; c++)
		bitmap_data.push_back(new unsigned char [width * height]);
	for(int c = 0; c < category_num; c++)
		for(int i = 0; i < width * height; i++)
			bitmap_data[c][i] = 0;
}

LabelingImageData::~LabelingImageData()
{
	delete[] original_data;
	delete[] color_data;
	for(int i = 0; i < category_num; i++) {
		delete[] bitmap_data[i];
	}
}

void LabelingImageData::setData(int index, unsigned char *data)
{
	for(int i = 0; i < width * height; i++) {
		bitmap_data[index][i] = data[i];
	}
}

unsigned char *LabelingImageData::getData(int index)
{
	return bitmap_data[index];
}

void LabelingImageData::erosion(void)
{
	imageprocessing.erosion(getCurrentData());
}

void LabelingImageData::dilation(void)
{
	imageprocessing.dilation(getCurrentData());
}

void LabelingImageData::labeling(void)
{
	imageprocessing.labelingWithSize(getCurrentData(), 20);
}

void LabelingImageData::eliminateIsolatedPixel(void)
{
	imageprocessing.eliminateIsolatedPixel(getCurrentData());
}

void LabelingImageData::fill(void)
{
	imageprocessing.fill(getCurrentData());
}

void LabelingImageData::loadColorTable(const char *filename)
{
	colortable.load(filename);
	for(int i = 0; i < category_num; i++) {
		colortable.apply(width, height, original_data, bitmap_data[i], tableValue(i));
	}
}

void LabelingImageData::saveColorTable(const char *filename)
{
	colortable.save(filename);
}

void LabelingImageData::clearAllColorTable(void)
{
	colortable.clear();
}

void LabelingImageData::clearColorTable(void)
{
	colortable.clearCategory(tableValue(currentIndex));
}

void LabelingImageData::applyColorTable()
{
	colortable.apply(width, height, original_data, bitmap_data[currentIndex], tableValue(currentIndex));
}

void LabelingImageData::clearBitColorTable(int x, int y)
{
	unsigned char r = original_data[(y * width + x) * 3 + 0];
	unsigned char g = original_data[(y * width + x) * 3 + 1];
	unsigned char b = original_data[(y * width + x) * 3 + 2];
	unsigned int index = (r << 16) | (g << 8) | (b << 0);
	colortable.clearColorTable(index, tableValue(currentIndex), margin);
}

void LabelingImageData::setBitColorTable(int x, int y)
{
	unsigned char r = original_data[(y * width + x) * 3 + 0];
	unsigned char g = original_data[(y * width + x) * 3 + 1];
	unsigned char b = original_data[(y * width + x) * 3 + 2];
	unsigned int index = (r << 16) | (g << 8) | (b << 0);
	colortable.setColorTable(index, tableValue(currentIndex), margin);
}

table LabelingImageData::tableValue(int index)
{
	return (table)(1 << index);
}

void LabelingImageData::setIndex(int index)
{
	if(index < 0 || index > category_num)
		return;
	currentIndex = index;
}

void LabelingImageData::setMargin(int margin)
{
	this->margin = margin;
}

void LabelingImageData::exportImage(unsigned char *output_image)
{
	int color_lists[][3] = {
		{   0,   0, 255 },
		{   0, 255,   0 },
		{   0, 255, 255 },
		{ 255,   0,   0 },
		{ 255,   0, 255 },
		{ 255, 255,   0 },
		{ 255, 255, 255 },
	};
	std::vector<int> index_list;
	index_list.push_back(index_field);
	index_list.push_back(index_white);
	index_list.push_back(index_goalpole);
	index_list.push_back(index_robot);
	index_list.push_back(index_ball);

	for(int i = 0; i < width * height * 3; i++)
		output_image[i] = 0;
	for(unsigned int num = 0; num < index_list.size(); num++) {
		for(int i = 0; i < width * height; i++) {
			if(bitmap_data[num][i] != 0) {
				output_image[i * 3 + 0] = color_lists[num][0];
				output_image[i * 3 + 1] = color_lists[num][1];
				output_image[i * 3 + 2] = color_lists[num][2];
			}
		}
	}
}

void LabelingImageData::setImage(unsigned char *data)
{
	for(int i = 0; i < width * height * 3; i++) {
		original_data[i] = data[i];
	}
	for(int i = 0; i < category_num; i++) {
		colortable.apply(width, height, original_data, bitmap_data[i], tableValue(i));
	}
}

unsigned char *LabelingImageData::getCurrentData(void)
{
	return bitmap_data[currentIndex];
}

unsigned char *LabelingImageData::getCurrentColorData(void)
{
	return color_data;
}

void LabelingImageData::clearCurrentBitmap(void)
{
	for(int i = 0; i < width * height; i++) {
		bitmap_data[currentIndex][i] = 0;
	}
}

void LabelingImageData::deletePix(int x, int y, int size)
{
	for(int yi = std::max<int>(y - size, 0); yi < std::min<int>(y + size + 1, height); yi++) {
		for(int xi = std::max<int>(x - size, 0); xi < std::min<int>(x + size + 1, width); xi++) {
			bitmap_data[currentIndex][yi * width + xi] = 0;
		}
	}
}

void LabelingImageData::writePix(int x, int y, int size)
{
	for(int yi = std::max<int>(y - size, 0); yi < std::min<int>(y + size + 1, height); yi++) {
		for(int xi = std::max<int>(x - size, 0); xi < std::min<int>(x + size + 1, width); xi++) {
			bitmap_data[currentIndex][yi * width + xi] = 1;
		}
	}
}

void LabelingImageData::selectRegion(int x, int y)
{
	selected_regions.push_back(bitmap_data[currentIndex][y * width + x]);
}

void LabelingImageData::extractSelectedRegions(void)
{
	unsigned char map[0xff];
	for(unsigned int i = 0; i < sizeof(map); i++)
		map[i] = 0;
	for(unsigned int i = 0; i < selected_regions.size(); i++)
		map[selected_regions[i]] = selected_regions[i];
	for(int i = 0; i < width * height; i++)
		bitmap_data[currentIndex][i] = map[bitmap_data[currentIndex][i]];
	selected_regions.clear();
}

void LabelingImageData::imageAndOperation(void)
{
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			if(bitmap_data[currentIndex][h * width + w] != 0) {
				for(int i = 0; i < 3; i++) {
					color_data[(h * width + w) * 3 + i] = original_data[(h * width + w) * 3 + i];
				}
			} else {
				color_data[(h * width + w) * 3 + 0] = 0;
				color_data[(h * width + w) * 3 + 1] = 0;
				color_data[(h * width + w) * 3 + 2] = 0;
			}
		}
	}
}

void LabelingImageData::sobel(unsigned char flag)
{
	for(int i = 0; i < width * height * 3; i++)
		color_data[i] = original_data[i];
	imageprocessing.sobelDrivative(color_data, flag);
}

unsigned char *LabelingImageData::getCheckImageData(void)
{
	unsigned char *data = getCurrentData();
	for(int i = 0; i < width * height; i++) {
		if(data[i] != 0) {
			color_data[i * 3 + 0] = 255;
			color_data[i * 3 + 1] = 0;
			color_data[i * 3 + 2] = 0;
		} else {
			color_data[i * 3 + 0] = original_data[i * 3 + 0];
			color_data[i * 3 + 1] = original_data[i * 3 + 1];
			color_data[i * 3 + 2] = original_data[i * 3 + 2];
		}
	}
	return color_data;
}

