
#ifndef __IMAGEPROCESSING_H__
#define __IMAGEPROCESSING_H__

class ImageProcessing
{
public:
  ImageProcessing(int, int);
	~ImageProcessing();
	void erosion(unsigned char *);
	void dilation(unsigned char *);
protected:
	int width;
	int height;
};

#endif // __IMAGEPROCESSING_H__

