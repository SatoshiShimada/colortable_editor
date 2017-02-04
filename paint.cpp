
#include "paint.h"

PaintArea::PaintArea(int width, int height) : QLabel(), width(width), height(height)
{
	mainPixmap = new QPixmap(width, height);
	mainPixmap->fill(qRgb(0, 0, 0));
	this->resize(width, height);
	this->setPixmap(*mainPixmap);
	this->update();
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();
	if(event->button() == Qt::LeftButton) {
		x -= (this->size().width() - width) / 2;
		y -= (this->size().height() - height) / 2;
		if(x < 0 || x > width) return;
		if(y < 0 || y > height) return;
		emit mousePressSignal(x, y);
	}
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();
	if((event->button() & Qt::LeftButton)) {
		x -= (this->size().width() - width) / 2;
		y -= (this->size().height() - height) / 2;
		if(x < 0 || x > width) return;
		if(y < 0 || y > height) return;
		emit mouseReleaseSignal(x, y);
	}
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();
	if(event->button() == Qt::NoButton) {
		x -= (this->size().width() - width) / 2;
		y -= (this->size().height() - height) / 2;
		if(x < 0 || x > width) return;
		if(y < 0 || y > height) return;
		emit mouseMoveSignal(x, y);
	}
}

void PaintArea::resetPixmapArea(void)
{
	mainPixmap->fill(Qt::black);
	this->setPixmap(*mainPixmap);
	this->update();
}

void PaintArea::savePixmapImage(const char *filename)
{
	QString qfilename = QString(filename);
	mainPixmap->save(qfilename);
}

void PaintArea::loadPixmapImage(const char *filename)
{
	QString qfilename = QString(filename);
	mainPixmap->load(qfilename);
	*mainPixmap = mainPixmap->scaled(width, height);
	originalPixmap = new QPixmap(*mainPixmap);
	this->setPixmap(*mainPixmap);
	this->update();
}

/*
void PaintArea::exportPixmapImage(const char *filename)
{
	int color_lists[ColorTable::max_categolies][3] = {
		//{ 255, 255, 255 },
		{ 255, 255,   0 },
		{ 255,   0, 255 },
		{ 255,   0,   0 },
		{   0, 255, 255 },
		{   0, 255,   0 },
		{   0,   0, 255 },
	};
	int r, g, b;
	QImage image = map.toImage();
	QImage outputImage(image.width(), image.height(), QImage::Format_RGB32);
	outputImage.fill(qRgb(0, 0, 0));
	for(int y = 0; y < image.height(); y++) {
		for(int x = 0; x < image.width(); x++) {
			QRgb value = image.pixel(x, y);
			for(int i = 0; i < ColorTable::max_categolies; i++) {
				if(value & (1 << i)) {
					r = color_lists[i][0];
					g = color_lists[i][1];
					b = color_lists[i][2];
					outputImage.setPixel(x, y, qRgb(r, g, b));
					break;
				}
			}
		}
	}
	outputImage.save(QString(filename));
}
*/

