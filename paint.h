
#ifndef __PAINT_H__
#define __PAINT_H__

#include <QtGui>
#include <QWidget>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

#include "color_table.h"
#include "image_processing.h"

class PaintArea : public QLabel
{
	Q_OBJECT

public:
	PaintArea();
	QPixmap map;
	void setCatcherSize(int);
	bool clearTable(void);
	bool clearCategolyTable(void);
	bool saveTable(const char *);
	bool loadTable(const char *);
	bool applyTable(void);
	void setCategoly(int);
	void setMode(bool);
protected:
	QPixmap *mainPixmap;
	QPixmap *originalPixmap;
	ColorTable color_table;
	ImageProcessing image_processing;
	int catcherSize;
	int currentIndex;
	bool isSetMode;
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void clearColorToTable(int x, int y);
	void setColorToTable(int x, int y);
	bool isCategoly(QRgb);
	void categolize(void);
	QPixmap createLabeledImage(void);
	void setImageFromData(void);
	void setLabeledImageData(unsigned char *);
	void getLabeledImageData(unsigned char *);
public slots:
	void resetPixmapArea(void);
	void savePixmapImage(const char *);
	void loadPixmapImage(const char *);
	void imageErosion(void);
	void imageDilation(void);
signals:
	void imageChanged(void);
};

#endif //__PAINT_H__

