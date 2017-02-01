
#include "interface.h"
#include "paint.h"
#include "color_table.h"

PaintArea::PaintArea() : QLabel(), map(320, 240), catcherSize(1), currentIndex(1), isSetMode(true)
{
	mainPixmap = new QPixmap(320, 240);
	mainPixmap->fill(qRgb(0, 0, 0));
	map.fill(qRgb(0, 0, 0));
	this->resize(320, 240);
	this->setPixmap(*mainPixmap);
	this->update();
}

void PaintArea::clearColorToTable(int x, int y)
{
	int margin = catcherSize;
	int x_diff = (this->size().width() - 320) / 2;
	int y_diff = (this->size().height() - 240) / 2;
	x = x - x_diff;
	y = y - y_diff;
	if(x < 0 || x >= mainPixmap->width()) return;
	if(y < 0 || y >= mainPixmap->height()) return;
	unsigned int rgb = originalPixmap->toImage().pixel(x, y);
	int r = (rgb >> 16) & 0xff;
	int g = (rgb >>  8) & 0xff;
	int b = (rgb >>  0) & 0xff;
	for(int rr = std::max<int>(r - margin, 0); rr < std::min<int>(r + margin, 255); rr++) {
		for(int gg = std::max<int>(g - margin, 0); gg < std::min<int>(g + margin, 255); gg++) {
			for(int bb = std::max<int>(b - margin, 0); bb < std::min<int>(b + margin, 255); bb++) {
				unsigned int index = qRgb(rr, gg, bb) & 0x00FFFFFF;
				color_table.clearColorTable(index, 1 << currentIndex);
			}
		}
	}
}

void PaintArea::setColorToTable(int x, int y)
{
	int margin = catcherSize;
	int x_diff = (this->size().width() - 320) / 2;
	int y_diff = (this->size().height() - 240) / 2;
	x = x - x_diff;
	y = y - y_diff;
	if(x < 0 || x >= mainPixmap->width()) return;
	if(y < 0 || y >= mainPixmap->height()) return;
	unsigned long rgb = originalPixmap->toImage().pixel(x, y);
	unsigned long r = (rgb >> 16) & 0xff;
	unsigned long g = (rgb >>  8) & 0xff;
	unsigned long b = (rgb >>  0) & 0xff;
	for(unsigned long rr = std::max<unsigned long>(r - margin, 0); rr < std::min<unsigned long>(r + margin, 255); rr++) {
		for(unsigned long gg = std::max<unsigned long>(g - margin, 0); gg < std::min<unsigned long>(g + margin, 255); gg++) {
			for(unsigned long bb = std::max<unsigned long>(b - margin, 0); bb < std::min<unsigned long>(b + margin, 255); bb++) {
				unsigned long index = qRgb(rr, gg, bb) & 0x00FFFFFF;
				color_table.setColorTable(index, 1 << currentIndex);
			}
		}
	}
}

void PaintArea::setLabeledImageData(unsigned char *imageData)
{
	QImage label = map.toImage();
	for(int y = 0; y < label.height(); y++) {
		for(int x = 0; x < label.width(); x++) {
			unsigned char r = imageData[(y * label.width() + x) * 3 + 0];
			unsigned char g = imageData[(y * label.width() + x) * 3 + 1];
			unsigned char b = imageData[(y * label.width() + x) * 3 + 2];
			label.setPixel(x, y, qRgb((int)r, (int)g, (int)b));
		}
	}
	map = QPixmap::fromImage(label);
	emit imageChanged();
}

void PaintArea::getLabeledImageData(unsigned char *returnImage)
{
	QImage label = map.toImage();
	for(int y = 0; y < label.height(); y++) {
		for(int x = 0; x < label.width(); x++) {
			QRgb rgb = label.pixel(x, y);
			unsigned char r = (rgb >> 16) & 0xff;
			unsigned char g = (rgb >>  8) & 0xff;
			unsigned char b = (rgb >>  0) & 0xff;
			returnImage[(y * label.width() + x) * 3 + 0] = r;
			returnImage[(y * label.width() + x) * 3 + 1] = g;
			returnImage[(y * label.width() + x) * 3 + 2] = b;
		}
	}
}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		if(isSetMode)
			setColorToTable(event->x(), event->y());
		else
			clearColorToTable(event->x(), event->y());
	}
}

void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
	if((event->button() & Qt::LeftButton)) {
		applyTable();
	}
}

void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
	if(event->button() == Qt::NoButton) {
		if(isSetMode)
			setColorToTable(event->x(), event->y());
		else
			clearColorToTable(event->x(), event->y());
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
	*mainPixmap = mainPixmap->scaled(320, 240);
	originalPixmap = new QPixmap(*mainPixmap);
	this->setPixmap(*mainPixmap);
	this->update();
}

bool PaintArea::isCategoly(QRgb color)
{
	unsigned int index = color & 0x00FFFFFF;
	if(color_table.getColorTable(index) & (1 << currentIndex))
		return true;
	return false;
}

void PaintArea::categolize(void)
{
	QImage image = originalPixmap->toImage();
	for(int y = 0; y < image.height(); y++) {
		for(int x = 0; x < image.width(); x++) {
			QRgb value = image.pixel(x, y);
			if(isCategoly(value)) {
				value = qRgb(255, 0, 0);
				image.setPixel(x, y, value);
			}
		}
	}
	*mainPixmap = QPixmap::fromImage(image);
	this->setPixmap(*mainPixmap);
	this->update();
}

QPixmap PaintArea::createLabeledImage(void)
{
	QImage image = originalPixmap->toImage();
	QImage label(image.width(), image.height(), QImage::Format_RGB32);
	label.fill(qRgb(0, 0, 0));
	for(int y = 0; y < image.height(); y++) {
		for(int x = 0; x < image.width(); x++) {
			QRgb value = image.pixel(x, y);
			if(isCategoly(value)) {
				label.setPixel(x, y, qRgb(255, 0, 0));
			} else {
			}
		}
	}
	map = QPixmap::fromImage(label);
	return map;
}

void PaintArea::setCatcherSize(int size)
{
	catcherSize = size;
}

void PaintArea::setCategoly(int index)
{
	if(index < 0 || index > ColorTable::max_categolies)
		index = 0;
	currentIndex = index;
}

bool PaintArea::clearTable(void)
{
	return color_table.clear();
}

bool PaintArea::clearCategolyTable(void)
{
	return color_table.clearCategoly(1 << currentIndex);
}

bool PaintArea::saveTable(const char *filename)
{
	return color_table.save(filename);
}

bool PaintArea::loadTable(const char *filename)
{
	return color_table.load(filename);
}

bool PaintArea::applyTable(void)
{
	categolize();
	createLabeledImage();
	emit imageChanged();
	return true;
}

void PaintArea::setMode(bool mode)
{
	isSetMode = mode;
}

void PaintArea::setImageFromData(void)
{
	unsigned char *data = new unsigned char[map.width() * map.height() * 3];
	if(data) {
		image_processing.getImageData(data);
		setLabeledImageData(data);
		delete[] data;
	}
}

void PaintArea::imageErosion(void)
{
	QImage image = originalPixmap->toImage();
	unsigned char *data = new unsigned char[image.width() * image.height() * 3];
	if(data) {
		getLabeledImageData(data);
		image_processing.setImageData(image.width(), image.height(), data);
		delete[] data;
	}
	image_processing.erosion();
	setImageFromData();
}

void PaintArea::imageDilation(void)
{
	QImage image = originalPixmap->toImage();
	unsigned char *data = new unsigned char[image.width() * image.height() * 3];
	if(data) {
		getLabeledImageData(data);
		image_processing.setImageData(image.width(), image.height(), data);
		delete[] data;
	}
	image_processing.dilation();
	setImageFromData();
}

