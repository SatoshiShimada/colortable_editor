
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
	void setImage(const unsigned char *);
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	QPixmap map;
	QPixmap originalMap;
	LabelingImageData labelData;
	int currentIndex;
	int width;
	int height;
	int deleteSize;
public slots:
	void setIndex(int);
	void setMargin(int);
	void setDeleteSize(int);
	void deletePix(int, int);
	void setBitColorTable(int, int);
	void clearBitColorTable(int, int);
	void applyColorTable(void);
signals:
	void updatedImage(void);
};

#endif //__LABELINGIMAGE_H__

