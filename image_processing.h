
#ifndef __IMAGEPROCESSING_H__
#define __IMAGEPROCESSING_H__

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
protected:
	int width;
	int height;
	const unsigned int lookup_table_size;
	unsigned int size_threshold;
	void labelingProcess(unsigned int *);
};

#endif //__IMAGEPROCESSING_H__

