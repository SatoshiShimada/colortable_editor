
#ifndef __LABELINGIMAGEDATA_H__
#define __LABELINGIMAGEDATA_H__

#include <vector>

#include "color_table.h"
#include "image_processing.h"

class LabelingImageData
{
public:
	LabelingImageData(int, int, int);
	~LabelingImageData();
	void setData(int, unsigned char *);
	unsigned char *getData(int);
	unsigned char *getCurrentData(void);
	unsigned char *getCurrentColorData(void);
	void loadColorTable(const char *);
	void saveColorTable(const char *);
	void clearAllColorTable(void);
	void clearColorTable(void);
	void applyColorTable();
	void clearBitColorTable(int, int);
	void setBitColorTable(int, int);
	void erosion(void);
	void dilation(void);
	void labeling(void);
	void eliminateIsolatedPixel(void);
	void fill(void);
	void setIndex(int);
	void setMargin(int);
	void exportImage(unsigned char *);
	void setImage(unsigned char *);
	void setImageColor(unsigned char *);
	void clearCurrentBitmap(void);
	void deletePix(int, int, int);
	void writePix(int, int, int);
	void selectRegion(int, int);
	void extractSelectedRegions(void);
	void imageAndOperation(void);
	void sobel(unsigned char);
	unsigned char *getCheckImageData(void);
	unsigned char *original_data;
	unsigned char *color_data;
	std::vector<unsigned char *> bitmap_data;
protected:
	const int width;
	const int height;
	const int category_num;
	int currentIndex;
	int margin;
	std::vector<unsigned char> selected_regions;
	ColorTable colortable;
	ImageProcessing imageprocessing;
	table tableValue(int);
};

#endif //__LABELINGIMAGEDATA_H__

