
#include <QtGui>

#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "interface.h"
#include "paint.h"
#include "labeling_image.h"

Interface::Interface() : QMainWindow(), isSetColorTable(true), isClickPixMode(false), isClickColorTableMode(true), isDeletePixMode(true), width(320), height(240), smallImageWidth(width / 2), smallImageHeight(height / 2), listFileIndex(0), categories(5)
{
	setAcceptDrops(true);
	createWindow();
	connection();
}

Interface::~Interface()
{
}

void Interface::createWindow(void)
{
	window                    = new QWidget;
	marginSizeLabel           = new QLabel("Margin size: ");
	deleteSizeLabel           = new QLabel("Delete size: ");
	ballSmallImageLabel       = new QLabel;
	fieldSmallImageLabel      = new QLabel;
	whitelineSmallImageLabel  = new QLabel;
	goalpoleSmallImageLabel   = new QLabel;
	robotSmallImageLabel      = new QLabel;
	ballSmallImagePixmap      = new QPixmap(smallImageWidth, smallImageHeight);
	fieldSmallImagePixmap     = new QPixmap(smallImageWidth, smallImageHeight);
	whitelineSmallImagePixmap = new QPixmap(smallImageWidth, smallImageHeight);
	goalpoleSmallImagePixmap  = new QPixmap(smallImageWidth, smallImageHeight);
	robotSmallImagePixmap     = new QPixmap(smallImageWidth, smallImageHeight);
	selectCategoriesComboBox  = new QComboBox();
	setClickModeRadioButton   = new QRadioButton("Set");
	clearClickModeRadioButton = new QRadioButton("Clear");
	deletePixModeRadioButton  = new QRadioButton("Delete");
	changeClickModeGroupBox   = new QGroupBox("Click mode");
	colortableGroupBox        = new QGroupBox("color table");
	imageGroupBox             = new QGroupBox("image");
	imageProcessingGroupBox   = new QGroupBox("Image Processing");
	loadListFileButton        = new QPushButton("Load List File");
	nextImageButton           = new QPushButton("Next Image");
	clearImageButton          = new QPushButton("Clear");
	saveImageButton           = new QPushButton("Save");
	loadImageButton           = new QPushButton("Load");
	exportImageButton         = new QPushButton("Export");
	clearAllTableButton       = new QPushButton("Clear All");
	clearTableButton          = new QPushButton("Clear");
	saveTableButton           = new QPushButton("Save");
	loadTableButton           = new QPushButton("Load");
	applyTableButton          = new QPushButton("Apply");
	imageErosionButton        = new QPushButton("Erosion");
	imageDilationButton       = new QPushButton("Dilation");
	imageLabelingButton       = new QPushButton("Labeling");
	ballSmallImageButton      = new QPushButton("Ball");
	fieldSmallImageButton     = new QPushButton("Field");
	whitelineSmallImageButton = new QPushButton("White line");
	goalpoleSmallImageButton  = new QPushButton("Goal pole");
	robotSmallImageButton     = new QPushButton("Robot");
	paintarea                 = new PaintArea(width, height);
	labelingimage             = new LabelingImage(width, height, categories);
	marginSizeSlider          = new QSlider;
	deleteSizeSlider          = new QSlider;
	mainLayout                = new QGridLayout;
	labelLayout               = new QGridLayout;
	buttonLayout              = new QVBoxLayout;
	colortableLayout          = new QVBoxLayout;
	imageProcessingLayout     = new QVBoxLayout;
	imageLayout               = new QVBoxLayout;
	ballSmallImageLayout      = new QVBoxLayout;
	fieldSmallImageLayout     = new QVBoxLayout;
	whitelineSmallImageLayout = new QVBoxLayout;
	goalpoleSmallImageLayout  = new QVBoxLayout;
	robotSmallImageLayout     = new QVBoxLayout;
	smallImageLayout          = new QHBoxLayout;

	setClickModeRadioButton->setChecked(true);

	marginSizeSlider->setTickPosition(QSlider::TicksBelow);
	marginSizeSlider->setOrientation(Qt::Horizontal);
	marginSizeSlider->setRange(0, 10);
	marginSizeLabel->setText("Margin size: 1");

	deleteSizeSlider->setTickPosition(QSlider::TicksBelow);
	deleteSizeSlider->setOrientation(Qt::Horizontal);
	deleteSizeSlider->setRange(1, 10);
	deleteSizeLabel->setText("Delete size: 1");

	selectCategoriesComboBox->addItem(QString("Ball"));
	selectCategoriesComboBox->addItem(QString("Field"));
	selectCategoriesComboBox->addItem(QString("White Line"));
	selectCategoriesComboBox->addItem(QString("Goal"));
	selectCategoriesComboBox->addItem(QString("Robot"));
	//selectCategoriesComboBox->addItem(QString("Back Ground"));

	ballSmallImagePixmap->fill(qRgb(0, 0, 0));
	fieldSmallImagePixmap->fill(qRgb(0, 0, 0));
	whitelineSmallImagePixmap->fill(qRgb(0, 0, 0));
	goalpoleSmallImagePixmap->fill(qRgb(0, 0, 0));
	robotSmallImagePixmap->fill(qRgb(0, 0, 0));

	ballSmallImageLabel->setPixmap(*ballSmallImagePixmap);
	fieldSmallImageLabel->setPixmap(*fieldSmallImagePixmap);
	whitelineSmallImageLabel->setPixmap(*whitelineSmallImagePixmap);
	goalpoleSmallImageLabel->setPixmap(*goalpoleSmallImagePixmap);
	robotSmallImageLabel->setPixmap(*robotSmallImagePixmap);

	ballSmallImageLayout->addWidget(ballSmallImageButton);
	ballSmallImageLayout->addWidget(ballSmallImageLabel);

	fieldSmallImageLayout->addWidget(fieldSmallImageButton);
	fieldSmallImageLayout->addWidget(fieldSmallImageLabel);

	whitelineSmallImageLayout->addWidget(whitelineSmallImageButton);
	whitelineSmallImageLayout->addWidget(whitelineSmallImageLabel);

	goalpoleSmallImageLayout->addWidget(goalpoleSmallImageButton);
	goalpoleSmallImageLayout->addWidget(goalpoleSmallImageLabel);

	robotSmallImageLayout->addWidget(robotSmallImageButton);
	robotSmallImageLayout->addWidget(robotSmallImageLabel);

	smallImageLayout->addLayout(ballSmallImageLayout);
	smallImageLayout->addLayout(fieldSmallImageLayout);
	smallImageLayout->addLayout(whitelineSmallImageLayout);
	smallImageLayout->addLayout(goalpoleSmallImageLayout);
	smallImageLayout->addLayout(robotSmallImageLayout);

	buttonLayout->addWidget(setClickModeRadioButton);
	buttonLayout->addWidget(clearClickModeRadioButton);
	buttonLayout->addWidget(deletePixModeRadioButton);
	changeClickModeGroupBox->setLayout(buttonLayout);

	colortableLayout->addWidget(clearAllTableButton);
	colortableLayout->addWidget(clearTableButton);
	colortableLayout->addWidget(saveTableButton);
	colortableLayout->addWidget(loadTableButton);
	colortableLayout->addWidget(applyTableButton);
	colortableGroupBox->setLayout(colortableLayout);

	imageLayout->addWidget(loadListFileButton);
	imageLayout->addWidget(nextImageButton);
	imageLayout->addWidget(clearImageButton);
	imageLayout->addWidget(saveImageButton);
	imageLayout->addWidget(loadImageButton);
	imageLayout->addWidget(exportImageButton);
	imageGroupBox->setLayout(imageLayout);

	imageProcessingLayout->addWidget(imageErosionButton);
	imageProcessingLayout->addWidget(imageDilationButton);
	imageProcessingLayout->addWidget(imageLabelingButton);
	imageProcessingGroupBox->setLayout(imageProcessingLayout);

	labelLayout->addWidget(imageGroupBox, 1, 1);
	labelLayout->addWidget(colortableGroupBox, 1, 2);
	labelLayout->addWidget(selectCategoriesComboBox, 2, 1);
	labelLayout->addWidget(imageProcessingGroupBox, 3, 1);
	labelLayout->addWidget(changeClickModeGroupBox, 3, 2);
	labelLayout->addWidget(marginSizeLabel, 4, 1);
	labelLayout->addWidget(marginSizeSlider, 4, 2);
	labelLayout->addWidget(deleteSizeLabel, 5, 1);
	labelLayout->addWidget(deleteSizeSlider, 5, 2);

	mainLayout->addLayout(labelLayout, 1, 1, 2, 1);
	mainLayout->addWidget(labelingimage, 1, 2);
	mainLayout->addWidget(paintarea, 1, 3);
	mainLayout->addLayout(smallImageLayout, 2, 2, 1, 2);

	window->setLayout(mainLayout);
	setCentralWidget(window);
}

void Interface::dragEnterEvent(QDragEnterEvent *e)
{
	if(e->mimeData()->hasFormat("text/uri-list")) {
		e->acceptProposedAction();
	}
}

void Interface::dropEvent(QDropEvent *e)
{
	filenameDrag = e->mimeData()->urls().first().toLocalFile();
	loadImage(filenameDrag.toStdString().c_str());
}

void Interface::connection(void)
{
	QObject::connect(loadListFileButton, SIGNAL(clicked()), this, SLOT(loadListFileSlot()));
	QObject::connect(nextImageButton, SIGNAL(clicked()), this, SLOT(nextImageSlot()));
	QObject::connect(clearImageButton, SIGNAL(clicked()), this, SLOT(clearImageSlot()));
	QObject::connect(saveImageButton, SIGNAL(clicked()), this, SLOT(saveImageSlot()));
	QObject::connect(loadImageButton, SIGNAL(clicked()), this, SLOT(loadImageSlot()));
	QObject::connect(exportImageButton, SIGNAL(clicked()), this, SLOT(exportImageSlot()));
	QObject::connect(clearAllTableButton, SIGNAL(clicked()), this, SLOT(clearAllTableSlot()));
	QObject::connect(clearTableButton, SIGNAL(clicked()), this, SLOT(clearTableSlot()));
	QObject::connect(saveTableButton, SIGNAL(clicked()), this, SLOT(saveTableSlot()));
	QObject::connect(loadTableButton, SIGNAL(clicked()), this, SLOT(loadTableSlot()));
	QObject::connect(applyTableButton, SIGNAL(clicked()), this, SLOT(applyTableSlot()));
	QObject::connect(marginSizeSlider, SIGNAL(sliderReleased()), this, SLOT(marginSizeChanged()));
	QObject::connect(deleteSizeSlider, SIGNAL(sliderReleased()), this, SLOT(deleteSizeChanged()));
	QObject::connect(selectCategoriesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setObjectType()));
	QObject::connect(selectCategoriesComboBox, SIGNAL(highlighted(int)), this, SLOT(setObjectType()));
	QObject::connect(setClickModeRadioButton, SIGNAL(clicked(bool)), this, SLOT(setClickModeSlot()));
	QObject::connect(clearClickModeRadioButton, SIGNAL(clicked(bool)), this, SLOT(clearClickModeSlot()));
	QObject::connect(deletePixModeRadioButton, SIGNAL(clicked(bool)), this, SLOT(deletePixModeSlot()));
	QObject::connect(paintarea, SIGNAL(mousePressSignal(int, int)), this, SLOT(mousePressSlot(int, int)));
	QObject::connect(paintarea, SIGNAL(mouseMoveSignal(int, int)), this, SLOT(mousePressSlot(int, int)));
	QObject::connect(paintarea, SIGNAL(mouseReleaseSignal(int, int)), this, SLOT(mouseReleaseSlot(int, int)));
	QObject::connect(labelingimage, SIGNAL(updatedImage()), this, SLOT(drawImage()));
	QObject::connect(imageErosionButton, SIGNAL(clicked(bool)), this, SLOT(imageErosionSlot()));
	QObject::connect(imageDilationButton, SIGNAL(clicked(bool)), this, SLOT(imageDilationSlot()));
	QObject::connect(imageLabelingButton, SIGNAL(clicked(bool)), this, SLOT(imageLabelingSlot()));
	QObject::connect(ballSmallImageButton, SIGNAL(clicked(bool)), this, SLOT(ballCategorySelectedSlot()));
	QObject::connect(fieldSmallImageButton, SIGNAL(clicked(bool)), this, SLOT(fieldCategorySelectedSlot()));
	QObject::connect(whitelineSmallImageButton, SIGNAL(clicked(bool)), this, SLOT(whitelineCategorySelectedSlot()));
	QObject::connect(goalpoleSmallImageButton, SIGNAL(clicked(bool)), this, SLOT(goalpoleCategorySelectedSlot()));
	QObject::connect(robotSmallImageButton, SIGNAL(clicked(bool)), this, SLOT(robotCategorySelectedSlot()));
}

void Interface::loadListFileSlot(void)
{
	listFileName = QFileDialog::getOpenFileName(this, "Open Image", "./");
	std::ifstream listFileStream(listFileName.toStdString().c_str());
	std::string line;
	while(std::getline(listFileStream, line)) {
		listFile.push_back(line);
	}
}

void Interface::nextImageSlot(void)
{
	listFileIndex++;
	loadImage(listFile[listFileIndex].c_str());
}

void Interface::clearImageSlot(void)
{
	paintarea->resetPixmapArea();
}

void Interface::saveImageSlot(void)
{
	QString qfilename = QFileDialog::getSaveFileName(this, "Save Image", "./");
	paintarea->savePixmapImage(qfilename.toStdString().c_str());
}

void Interface::loadImageSlot(void)
{
	QString qfilename = QFileDialog::getOpenFileName(this, "Load Image", "./");
	loadImage(qfilename.toStdString().c_str());
}

void Interface::exportImageSlot(void)
{
	QString qfilename = QFileDialog::getSaveFileName(this, "Export Image", "./");
	labelingimage->exportImage(qfilename.toStdString().c_str());
}

void Interface::clearAllTableSlot(void)
{
	labelingimage->clearAllColorTable();
}

void Interface::clearTableSlot(void)
{
	labelingimage->clearColorTable();
}

void Interface::saveTableSlot(void)
{
	QString qfilename = QFileDialog::getSaveFileName(this, "Save Table", "./");
	labelingimage->saveColorTable(qfilename.toStdString().c_str());
}

void Interface::loadTableSlot(void)
{
	QString qfilename = QFileDialog::getOpenFileName(this, "Load Table", "./");
	labelingimage->loadColorTable(qfilename.toStdString().c_str());
}

void Interface::applyTableSlot(void)
{
	labelingimage->applyColorTable();
}

void Interface::saveImage(const char *filename)
{
	paintarea->savePixmapImage(filename);
}

void Interface::loadImage(const char *filename)
{
	paintarea->loadPixmapImage(filename);
	labelingimage->loadImage(filename);
}

void Interface::marginSizeChanged(void)
{
	char buf[1024];
	sprintf(buf, "Margin size: %d", marginSizeSlider->value());
	marginSizeLabel->setText(buf);
	labelingimage->setMargin(marginSizeSlider->value());
}

void Interface::deleteSizeChanged(void)
{
	char buf[1024];
	sprintf(buf, "Delete size: %d", deleteSizeSlider->value());
	deleteSizeLabel->setText(buf);
	labelingimage->setDeleteSize(deleteSizeSlider->value());
}

void Interface::drawImage(void)
{
	labelingimage->update();
	getSmallImages();
}

void Interface::setObjectType(void)
{
	labelingimage->setIndex(selectCategoriesComboBox->currentIndex());
}

void Interface::setClickModeSlot(void)
{
	isSetColorTable = true;
	isClickColorTableMode = true;
	isClickPixMode = false;
}

void Interface::clearClickModeSlot(void)
{
	isSetColorTable = false;
	isClickColorTableMode = true;
	isClickPixMode = false;
}

void Interface::deletePixModeSlot(void)
{
	isDeletePixMode = true;
	isClickColorTableMode = false;
	isClickPixMode = true;
}

void Interface::mousePressSlot(int x, int y)
{
	if(isClickColorTableMode) {
		if(isSetColorTable)
			labelingimage->setBitColorTable(x, y);
		else
			labelingimage->clearBitColorTable(x, y);
	} else if(isClickPixMode) {
		if(isDeletePixMode)
			labelingimage->deletePix(x, y);
		else
			;
	}
}

void Interface::mouseReleaseSlot(int x, int y)
{
}

void Interface::imageErosionSlot(void)
{
	labelingimage->erosion();
}

void Interface::imageDilationSlot(void)
{
	labelingimage->dilation();
}

void Interface::imageLabelingSlot(void)
{
	labelingimage->labeling();
}

void Interface::ballCategorySelectedSlot(void)
{
	labelingimage->setIndex(0);
}

void Interface::fieldCategorySelectedSlot(void)
{
	labelingimage->setIndex(1);
}

void Interface::whitelineCategorySelectedSlot(void)
{
	labelingimage->setIndex(2);
}

void Interface::goalpoleCategorySelectedSlot(void)
{
	labelingimage->setIndex(3);
}

void Interface::robotCategorySelectedSlot(void)
{
	labelingimage->setIndex(4);
}

void Interface::getSmallImages(void)
{
	unsigned char *data = new unsigned char [width * height];
	std::vector<QPixmap *> pixmaps;
	pixmaps.push_back(ballSmallImagePixmap);
	pixmaps.push_back(fieldSmallImagePixmap);
	pixmaps.push_back(whitelineSmallImagePixmap);
	pixmaps.push_back(goalpoleSmallImagePixmap);
	pixmaps.push_back(robotSmallImagePixmap);

	for(int i = 0; i < categories; i++) {
		labelingimage->getSmallImage(data, i);
		QImage image(width, height, QImage::Format_RGB32);
		image.fill(qRgb(0, 0, 0));
		for(int h = 0; h < height; h++) {
			for(int w = 0; w < width; w++) {
				if(data[h * width + w] != 0) {
					image.setPixel(w, h, qRgb(255, 0, 0));
				}
			}
		}
		image = image.scaled(smallImageWidth, smallImageHeight);
		pixmaps[i]->operator=(QPixmap::fromImage(image));
	}
	ballSmallImageLabel->setPixmap(*ballSmallImagePixmap);
	fieldSmallImageLabel->setPixmap(*fieldSmallImagePixmap);
	whitelineSmallImageLabel->setPixmap(*whitelineSmallImagePixmap);
	goalpoleSmallImageLabel->setPixmap(*goalpoleSmallImagePixmap);
	robotSmallImageLabel->setPixmap(*robotSmallImagePixmap);
	delete[] data;
}

