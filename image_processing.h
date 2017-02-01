
#ifndef _IMAGEPROCESSING_H_
#define _IMAGEPROCESSING_H_

class ImageProcessing
{
public:
	ImageProcessing();
	~ImageProcessing();
	void setImageData(int, int, unsigned char *);
	void getImageData(unsigned char *);
	void erosion(void);
	void dilation(void);
protected:
	bool isAllocatedDataMemory;
	unsigned char *data;
	int width;
	int height;
};

#endif // _IMAGEPROCESSING_H_

