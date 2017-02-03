
#include "labeling_image_data.h"

LabelingImageData::LabelingImageData(int width, int height, int category_num) : width(width), height(height), category_num(category_num), currentIndex(0), margin(0), imageprocessing(width, height)
{
	original_data = new unsigned char [width * height * 3];
	for(int i = 0; i < category_num; i++) {
		bitmap_data.push_back(new unsigned char [width * height]);
	}
}

LabelingImageData::~LabelingImageData()
{
	delete[] original_data;
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

void LabelingImageData::loadColorTable(const char *filename)
{
	colortable.load(filename);
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

void LabelingImageData::exportImage(const char *filename)
{
}

void LabelingImageData::setImage(unsigned char *data)
{
	for(int i = 0; i < width * height * 3; i++) {
		original_data[i] = data[i];
	}
}

unsigned char *LabelingImageData::getCurrentData(void)
{
	return bitmap_data[currentIndex];

}

