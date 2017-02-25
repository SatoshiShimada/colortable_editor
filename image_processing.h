
#ifndef __IMAGEPROCESSING_H__
#define __IMAGEPROCESSING_H__

enum {
	FILTER_COLOR = 1,
	FILTER_COLOR_RED = 2,
	FILTER_COLOR_GREEN = 4,
	FILTER_COLOR_BLUE = 8,
};

class ImageProcessing
{
public:
	ImageProcessing(int, int);
	~ImageProcessing();
	void erosion(unsigned char *);
	void dilation(unsigned char *);
	void labeling(unsigned char *);
	void labelingWithSize(unsigned char *);
	void labelingWithSize(unsigned char *, unsigned int);
	void eliminateIsolatedPixel(unsigned char *);
	void expand(unsigned char *);
	void sobelDrivative(unsigned char *, unsigned char);
protected:
	int width;
	int height;
	const unsigned int lookup_table_size;
	unsigned int size_threshold;
	void labelingProcess(unsigned int *);
	void filter(unsigned char *, unsigned char *);
};

#endif //__IMAGEPROCESSING_H__

