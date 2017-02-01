
#ifndef _IMAGEPROCESSING_H_
#define _IMAGEPROCESSING_H_

class ImageProcessing
{
public:
	ImageProcessing();
	~ImageProcessing();
	void setImageData(int, int, unsigned char *);
protected:
	bool isAllocatedDataMemory;
	unsigned char *data;
	int width;
	int height;
};

#endif // _IMAGEPROCESSING_H_

