
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
	PaintArea(int, int);
protected:
	QPixmap *mainPixmap;
	QPixmap *originalPixmap;
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
    int width;
    int height;
public slots:
	void resetPixmapArea(void);
	void savePixmapImage(const char *);
	void loadPixmapImage(const char *);
	//void exportPixmapImage(const char *);
 signals:
    void mousePressSignal(int, int);
    void mouseReleaseSignal(int, int);
    void mouseMoveSignal(int, int);
};

#endif //__PAINT_H__

