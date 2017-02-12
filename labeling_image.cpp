
#include "labeling_image.h"

LabelingImage::LabelingImage(int width, int height, int category_num) : QLabel(), map(width, height), originalMap(width, height), labelData(width, height, category_num), width(width), height(height), currentIndex(0), deleteSize(1), categoryNum(category_num)
{
	this->setMinimumSize(width, height);
	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	map.fill(qRgb(0, 0, 0));
	this->setPixmap(map);
}

void LabelingImage::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton) {
		int x = event->x();
		int y = event->y();
		deletePix(x, y);
	}
}

void LabelingImage::mouseReleaseEvent(QMouseEvent *event)
{
	if((event->button() & Qt::LeftButton)) {
		int x = event->x();
		int y = event->y();
		deletePix(x, y);
	}
}

void LabelingImage::mouseMoveEvent(QMouseEvent *event)
{
	if(event->button() == Qt::NoButton) {
		int x = event->x();
		int y = event->y();
		deletePix(x, y);
	}
}
void LabelingImage::setIndex(int index)
{
	labelData.setIndex(index);
	setImage(labelData.getCurrentData());
}

void LabelingImage::setMargin(int margin)
{
	labelData.setMargin(margin);
}

void LabelingImage::deletePix(int x, int y)
{
	if(x < 0 || x > width) return;
	if(y < 0 || y > height) return;
	labelData.deletePix(x, y, deleteSize);
	setImage(labelData.getCurrentData());
}

void LabelingImage::setBitColorTable(int x, int y)
{
	if(x < 0 || x > width) return;
	if(y < 0 || y > height) return;
	labelData.setBitColorTable(x, y);
	labelData.applyColorTable();
	setImage(labelData.getCurrentData());
}

void LabelingImage::clearBitColorTable(int x, int y)
{
	if(x < 0 || x > width) return;
	if(y < 0 || y > height) return;
	labelData.clearBitColorTable(x, y);
	labelData.applyColorTable();
	setImage(labelData.getCurrentData());
}

void LabelingImage::clearAllColorTable(void)
{
	labelData.clearAllColorTable();
}

void LabelingImage::clearColorTable(void)
{
	labelData.clearColorTable();
}

void LabelingImage::loadColorTable(const char *filename)
{
	labelData.loadColorTable(filename);
	setImage(labelData.getCurrentData());
}

void LabelingImage::saveColorTable(const char *filename)
{
	labelData.saveColorTable(filename);
}

void LabelingImage::exportImage(const char *filename)
{
	QImage outputImage(width, height, QImage::Format_RGB32);
	unsigned char *data = new unsigned char [width * height * 3];
	labelData.exportImage(data);
	for(int y = 0; y < height; y++) {
		for(int x = 0; x < width; x++) {
			outputImage.setPixel(x, y, qRgb(
				(int)data[(y * width + x) * 3 + 0],
				(int)data[(y * width + x) * 3 + 1],
				(int)data[(y * width + x) * 3 + 2]));
		}
	}
	outputImage.save(QString(filename));
}

void LabelingImage::loadImage(const char *filename)
{
	originalMap.load(filename);
	originalMap = originalMap.scaled(width, height);
	QImage image = originalMap.toImage();
	unsigned char *data = new unsigned char [width * height * 3];
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			QRgb rgb = image.pixel(w, h);
			data[(h * width + w) * 3 + 0] = (rgb >> 16) & 0xff;
			data[(h * width + w) * 3 + 1] = (rgb >>  8) & 0xff;
			data[(h * width + w) * 3 + 2] = (rgb >>  0) & 0xff;
		}
	}
	labelData.setImage(data);
	delete[] data;
}

void LabelingImage::erosion(void)
{
	labelData.erosion();
	setImage(labelData.getCurrentData());
}

void LabelingImage::dilation(void)
{
	labelData.dilation();
	setImage(labelData.getCurrentData());
}

void LabelingImage::labeling(void)
{
	labelData.labeling();
	setImage(labelData.getCurrentData());
}

void LabelingImage::eliminateIsolatedPixel(void)
{
	labelData.eliminateIsolatedPixel();
	setImage(labelData.getCurrentData());
}

void LabelingImage::applyColorTable(void)
{
	labelData.applyColorTable();
	setImage(labelData.getCurrentData());
}

void LabelingImage::setImage(const unsigned char *data)
{
	const int color_num = 14;
	int color_lists[color_num][3] = {
		{ 127,   0,   0 },
		{ 255,   0,   0 },
		{ 255, 127,   0 },
		{   0, 255,   0 },
		{ 127, 255,   0 },
		{ 255, 255,   0 },
		{   0,   0, 127 },
		{   0,   0, 255 },
		{ 127,   0, 255 },
		{ 255,   0, 255 },
		{   0, 127, 255 },
		{   0, 255, 255 },
		{ 127, 255, 255 },
		{ 255, 255, 255 },
	};
	QImage image = map.toImage();
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			if(data[h * width + w] != 0) {
				int *color = color_lists[data[h * width + w] % color_num];
				image.setPixel(w, h, qRgb(color[0], color[1], color[2]));
			} else {
				image.setPixel(w, h, qRgb(0, 0, 0));
			}
		}
	}
	map = QPixmap::fromImage(image);
	this->setPixmap(map);
	emit updatedImage();
}

void LabelingImage::setDeleteSize(int value)
{
	deleteSize = value;
}

void LabelingImage::getSmallImage(unsigned char *data, int index)
{
	unsigned char *image = labelData.getData(index);
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			data[h * width + w] = image[h * width + w];
		}
	}
}

