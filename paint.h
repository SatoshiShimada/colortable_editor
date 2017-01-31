
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

class PaintArea : public QLabel
{
Q_OBJECT
public:
	PaintArea();
	QPixmap map;
	void setCatcherSize(int);
	bool clearTable(void);
	bool saveTable(const char *);
	bool loadTable(const char *);
	bool applyTable(void);
	void setCategoly(int);
protected:
	QPixmap *mainPixmap;
	QPixmap *originalPixmap;
	ColorTable color_table;
	int catcherSize;
	int currentIndex;
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void setColorToTable(int x, int y);
	bool isCategoly(QRgb);
	void categolize(void);
	QPixmap createLabeledImage(void);
private:
public slots:
	void resetPixmapArea(void);
	void savePixmapImage(const char *);
	void loadPixmapImage(const char *);
signals:
	void imageChanged(void);
};

#endif //__PAINT_H__

