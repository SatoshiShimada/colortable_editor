
#ifndef __LABELINGIMAGE_H__
#define __LABELINGIMAGE_H__

#include <QtGui>
#include <QLabel>

#include "labeling_image_data.h"

class LabelingImage : public QLabel
{
	Q_OBJECT

public:
	LabelingImage(int, int, int);
	void clearAllColorTable(void);
	void clearColorTable(void);
	void loadColorTable(const char *);
	void saveColorTable(const char *);
	void exportImage(const char *);
	void loadImage(const char *);
	void erosion(void);
	void dilation(void);
	void labeling(void);
	void eliminateIsolatedPixel(void);
	void expand(void);
	void extractSelectedRegion(void);
	void setImage(const unsigned char *);
	void setImageColor(const unsigned char *);
	void getSmallImage(unsigned char *, int);
	unsigned char *getCheckImageData(void);
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	QPixmap map;
	QPixmap originalMap;
	LabelingImageData labelData;
	int width;
	int height;
	int currentIndex;
	int editPixSize;
	int categoryNum;
public slots:
	void setIndex(int);
	void setMargin(int);
	void setEditPixSize(int);
	void deletePix(int, int);
	void writePix(int, int);
	void selectRegion(int, int);
	void setBitColorTable(int, int);
	void clearBitColorTable(int, int);
	void applyColorTable(void);
	void clearCurrentBitmap(void);
	void imageAndOperation(void);
	void sobel(unsigned char);
signals:
	void updatedImage(void);
	void mousePressSignal(int, int);
	void mouseReleaseSignal(int, int);
	void mouseMoveSignal(int, int);
};

#endif //__LABELINGIMAGE_H__

