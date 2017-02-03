
#include "labeling_image.h"

LabelingImage::LabelingImage(int width, int height, int category_num) : QLabel(), map(width, height), originalMap(width, height), labelData(width, height, category_num), currentIndex(0), width(width), height(height)
{
	this->setMinimumSize(width, height);
	this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	map.fill(qRgb(0, 0, 0));
	this->setPixmap(map);
}

void LabelingImage::setIndex(int index)
{
	labelData.setIndex(index);
}

void LabelingImage::setMargin(int margin)
{
	labelData.setMargin(margin);
}

void LabelingImage::setBitColorTable(int x, int y)
{
	x -= (this->size().width() - width) / 2;
	y -= (this->size().height() - height) / 2;
	if(x < 0 || x > width) return;
	if(y < 0 || y > height) return;
	labelData.setBitColorTable(x, y);
	labelData.applyColorTable();
	setImage(labelData.getCurrentData());
}

void LabelingImage::clearBitColorTable(int x, int y)
{
	x -= (this->size().width() - width) / 2;
	y -= (this->size().height() - height) / 2;
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
}

void LabelingImage::saveColorTable(const char *filename)
{
	labelData.saveColorTable(filename);
}

void LabelingImage::exportImage(const char *filename)
{
	labelData.exportImage(filename);
}

void LabelingImage::loadImage(const char *filename)
{
	originalMap.load(filename);
	originalMap.scaled(width, height);
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

void LabelingImage::applyColorTable(void)
{
	labelData.applyColorTable();
	setImage(labelData.getCurrentData());
}

void LabelingImage::setImage(const unsigned char *data)
{
	QImage image = map.toImage();
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			if(data[h * width + w] != 0)
				image.setPixel(w, h, qRgb(255, 0, 0));
			else
				image.setPixel(w, h, qRgb(0, 0, 0));
		}
	}
	map = QPixmap::fromImage(image);
	this->setPixmap(map);
	emit updatedImage();
}

