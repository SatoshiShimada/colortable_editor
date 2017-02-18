
#include <QtGui>

#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

#include "interface.h"
#include "paint.h"
#include "labeling_image.h"

Interface::Interface() : QMainWindow(), isSetColorTable(true), isClickPixMode(false), isClickColorTableMode(true), isDeletePixMode(true), isSelectRegionMode(false), width(320), height(240), smallImageWidth(width / 2), smallImageHeight(height / 2), listFileIndex(0), categories(5)
{
	setAcceptDrops(true);
	createWindow();
	createActions();
	createMenus();
	connection();
}

Interface::~Interface()
{
}

void Interface::createWindow(void)
{
	window                    = new QWidget;
	marginSizeLabel           = new QLabel("Margin size: ");
	editPixSizeLabel          = new QLabel("Edit Pixel size: ");
	ballSmallImageLabel       = new QLabel;
	fieldSmallImageLabel      = new QLabel;
	whitelineSmallImageLabel  = new QLabel;
	goalpoleSmallImageLabel   = new QLabel;
	robotSmallImageLabel      = new QLabel;
	currentFileNameLineEdit   = new QLineEdit;
	ballSmallImagePixmap      = new QPixmap(smallImageWidth, smallImageHeight);
	fieldSmallImagePixmap     = new QPixmap(smallImageWidth, smallImageHeight);
	whitelineSmallImagePixmap = new QPixmap(smallImageWidth, smallImageHeight);
	goalpoleSmallImagePixmap  = new QPixmap(smallImageWidth, smallImageHeight);
	robotSmallImagePixmap     = new QPixmap(smallImageWidth, smallImageHeight);
	selectCategoriesComboBox  = new QComboBox();
	setClickModeRadioButton   = new QRadioButton("Set");
	clearClickModeRadioButton = new QRadioButton("Clear");
	deletePixModeRadioButton  = new QRadioButton("Delete");
	writePixModeRadioButton   = new QRadioButton("Write");
	selectRegionRadioButton   = new QRadioButton("Select");
	changeClickModeGroupBox   = new QGroupBox("Click mode");
	colortableGroupBox        = new QGroupBox("color table");
	imageGroupBox             = new QGroupBox("image");
	imageProcessingGroupBox   = new QGroupBox("Image Processing");
	loadListFileButton        = new QPushButton("Load List File");
	nextImageButton           = new QPushButton("Next Image");
	clearImageButton          = new QPushButton("Clear");
	clearBitmapImageButton    = new QPushButton("Clear bitmap");
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
	imageEliminateIsolatedPixelButton = new QPushButton("Isolated Pixel");
	imageFillButton           = new QPushButton("Fill");
	imageExtractSelectedRegionsButton = new QPushButton("Extract Region");
	imageSobelButton          = new QPushButton("Sobel");
	ballSmallImageButton      = new QPushButton("Ball");
	fieldSmallImageButton     = new QPushButton("Field");
	whitelineSmallImageButton = new QPushButton("White line");
	goalpoleSmallImageButton  = new QPushButton("Goal pole");
	robotSmallImageButton     = new QPushButton("Robot");
	superimposeLeftButton     = new QPushButton("<");
	superimposeRightButton    = new QPushButton(">");
	paintarea                 = new PaintArea(width, height);
	labelingimage             = new LabelingImage(width, height, categories);
	marginSizeSlider          = new QSlider;
	editPixSizeSlider         = new QSlider;
	mainLayout                = new QGridLayout;
	labelLayout               = new QGridLayout;
	superimposeButtonsLayout  = new QVBoxLayout;
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

	paintarea->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	labelingimage->setAlignment(Qt::AlignTop | Qt::AlignLeft);

	setClickModeRadioButton->setChecked(true);

	marginSizeSlider->setTickPosition(QSlider::TicksBelow);
	marginSizeSlider->setOrientation(Qt::Horizontal);
	marginSizeSlider->setRange(0, 10);
	marginSizeLabel->setText("Margin size: 1");

	editPixSizeSlider->setTickPosition(QSlider::TicksBelow);
	editPixSizeSlider->setOrientation(Qt::Horizontal);
	editPixSizeSlider->setRange(1, 10);
	editPixSizeLabel->setText("Edit Pixel size: 1");

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
	buttonLayout->addWidget(writePixModeRadioButton);
	buttonLayout->addWidget(deletePixModeRadioButton);
	buttonLayout->addWidget(selectRegionRadioButton);
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
	imageLayout->addWidget(clearBitmapImageButton);
	imageLayout->addWidget(saveImageButton);
	imageLayout->addWidget(loadImageButton);
	imageLayout->addWidget(exportImageButton);
	imageGroupBox->setLayout(imageLayout);

	imageProcessingLayout->addWidget(imageErosionButton);
	imageProcessingLayout->addWidget(imageDilationButton);
	imageProcessingLayout->addWidget(imageLabelingButton);
	imageProcessingLayout->addWidget(imageEliminateIsolatedPixelButton);
	imageProcessingLayout->addWidget(imageFillButton);
	imageProcessingLayout->addWidget(imageExtractSelectedRegionsButton);
	imageProcessingLayout->addWidget(imageSobelButton);
	imageProcessingGroupBox->setLayout(imageProcessingLayout);

	//labelLayout->addWidget(imageGroupBox, 1, 1);
	//labelLayout->addWidget(colortableGroupBox, 1, 2);
	//labelLayout->addWidget(selectCategoriesComboBox, 2, 1);
	labelLayout->addWidget(imageProcessingGroupBox, 1, 1);
	labelLayout->addWidget(changeClickModeGroupBox, 1, 2);
	labelLayout->addWidget(marginSizeLabel, 2, 1);
	labelLayout->addWidget(marginSizeSlider, 2, 2);
	labelLayout->addWidget(editPixSizeLabel, 3, 1);
	labelLayout->addWidget(editPixSizeSlider, 3, 2);

	superimposeButtonsLayout->addWidget(superimposeLeftButton);
	superimposeButtonsLayout->addWidget(superimposeRightButton);

	mainLayout->addLayout(labelLayout, 1, 1, 3, 1);
	mainLayout->addWidget(currentFileNameLineEdit, 1, 2, 1, 3);
	mainLayout->addWidget(labelingimage, 2, 2);
	mainLayout->addLayout(superimposeButtonsLayout, 2, 3);
	mainLayout->addWidget(paintarea, 2, 4);
	mainLayout->addLayout(smallImageLayout, 3, 2, 1, 3);

	window->setLayout(mainLayout);
	setCentralWidget(window);
}

void Interface::createMenus(void)
{
	imageMenu = menuBar()->addMenu("Image");
	imageMenu->addAction(loadListFileAction);
	imageMenu->addAction(nextImageAction);
	imageMenu->addAction(clearImageAction);
	imageMenu->addAction(clearBitmapImageAction);
	imageMenu->addAction(loadImageAction);
	imageMenu->addAction(saveImageAction);
	imageMenu->addAction(exportImageAction);

	colortableMenu = menuBar()->addMenu("Colortable");
	colortableMenu->addAction(loadColortableAction);
	colortableMenu->addAction(saveColortableAction);
	colortableMenu->addAction(clearAllColortableAction);
	colortableMenu->addAction(clearColortableAction);
	colortableMenu->addAction(applyColortableAction);

	imageprocessingMenu = menuBar()->addMenu("Image Processing");
	imageprocessingMenu->addAction(erosionAction);
	imageprocessingMenu->addAction(dilationAction);
	imageprocessingMenu->addAction(labelingAction);
	imageprocessingMenu->addAction(eliminateIsolatedPixelAction);
	imageprocessingMenu->addAction(fillIsolatedPointAction);
	imageprocessingMenu->addAction(extractRegionAction);
}

void Interface::createActions(void)
{
	loadListFileAction = new QAction("Load List File", this);
	connect(loadListFileAction, SIGNAL(triggered()), this, SLOT(loadListFileSlot()));
	nextImageAction = new QAction("Next image", this);
	connect(nextImageAction, SIGNAL(triggered()), this, SLOT(nextImageSlot()));
	clearImageAction = new QAction("Clear", this);
	connect(clearImageAction, SIGNAL(triggered()), this, SLOT(clearImageSlot()));
	clearBitmapImageAction = new QAction("Clear bitmap", this);
	connect(clearBitmapImageAction, SIGNAL(triggered()), this, SLOT(clearBitmapImageSlot()));
	loadImageAction = new QAction("Load", this);
	connect(loadImageAction, SIGNAL(triggered()), this, SLOT(loadImageSlot()));
	saveImageAction = new QAction("Save", this);
	connect(saveImageAction, SIGNAL(triggered()), this, SLOT(saveImageSlot()));
	exportImageAction = new QAction("Export", this);
	connect(exportImageAction, SIGNAL(triggered()), this, SLOT(exportImageSlot()));

	loadColortableAction = new QAction("Load", this);
	connect(loadColortableAction, SIGNAL(triggered()), this, SLOT(loadTableSlot()));
	saveColortableAction = new QAction("Save", this);
	connect(saveColortableAction, SIGNAL(triggered()), this, SLOT(saveTableSlot()));
	clearAllColortableAction = new QAction("Clear all", this);
	connect(clearAllColortableAction, SIGNAL(triggered()), this, SLOT(clearAllTableSlot()));
	clearColortableAction = new QAction("Clear", this);
	connect(clearColortableAction, SIGNAL(triggered()), this, SLOT(clearTableSlot()));
	applyColortableAction = new QAction("Apply", this);
	connect(applyColortableAction, SIGNAL(triggered()), this, SLOT(applyTableSlot()));

	erosionAction = new QAction("Erosion", this);
	connect(erosionAction, SIGNAL(triggered()), this, SLOT(imageErosionSlot()));
	dilationAction = new QAction("Dilation", this);
	connect(dilationAction, SIGNAL(triggered()), this, SLOT(imageDilationSlot()));
	labelingAction = new QAction("Labeling", this);
	connect(labelingAction, SIGNAL(triggered()), this, SLOT(imageLabelingSlot()));
	eliminateIsolatedPixelAction = new QAction("Eliminate isolated pixel", this);
	connect(eliminateIsolatedPixelAction, SIGNAL(triggered()), this, SLOT(imageEliminatedIsolatedPixelSlot()));
	fillIsolatedPointAction = new QAction("Fill isolated point", this);
	connect(fillIsolatedPointAction, SIGNAL(triggered()), this, SLOT(imageFillSlot()));
	extractRegionAction = new QAction("Extract regions", this);
	connect(extractRegionAction, SIGNAL(triggered()), this, SLOT(imageExtractSelectedRegionsSlot()));
}

#ifndef QT_NO_CONTEXTMENU
void Interface::contextMenuEvent(QContextMenuEvent *event)
{
	//QMenu menu(this);
	//menu.addAction(cutAct);
}
#endif //QT_NO_CONTEXTMENU

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
	QObject::connect(clearBitmapImageButton, SIGNAL(clicked()), this, SLOT(clearBitmapImageSlot()));
	QObject::connect(saveImageButton, SIGNAL(clicked()), this, SLOT(saveImageSlot()));
	QObject::connect(loadImageButton, SIGNAL(clicked()), this, SLOT(loadImageSlot()));
	QObject::connect(exportImageButton, SIGNAL(clicked()), this, SLOT(exportImageSlot()));
	QObject::connect(clearAllTableButton, SIGNAL(clicked()), this, SLOT(clearAllTableSlot()));
	QObject::connect(clearTableButton, SIGNAL(clicked()), this, SLOT(clearTableSlot()));
	QObject::connect(saveTableButton, SIGNAL(clicked()), this, SLOT(saveTableSlot()));
	QObject::connect(loadTableButton, SIGNAL(clicked()), this, SLOT(loadTableSlot()));
	QObject::connect(applyTableButton, SIGNAL(clicked()), this, SLOT(applyTableSlot()));
	QObject::connect(marginSizeSlider, SIGNAL(sliderReleased()), this, SLOT(marginSizeChanged()));
	QObject::connect(editPixSizeSlider, SIGNAL(sliderReleased()), this, SLOT(editPixSizeChanged()));
	QObject::connect(selectCategoriesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setObjectType()));
	QObject::connect(selectCategoriesComboBox, SIGNAL(highlighted(int)), this, SLOT(setObjectType()));
	QObject::connect(setClickModeRadioButton, SIGNAL(clicked(bool)), this, SLOT(setClickModeSlot()));
	QObject::connect(clearClickModeRadioButton, SIGNAL(clicked(bool)), this, SLOT(clearClickModeSlot()));
	QObject::connect(deletePixModeRadioButton, SIGNAL(clicked(bool)), this, SLOT(deletePixModeSlot()));
	QObject::connect(writePixModeRadioButton, SIGNAL(clicked(bool)), this, SLOT(writePixModeSlot()));
	QObject::connect(selectRegionRadioButton, SIGNAL(clicked(bool)), this, SLOT(selectRegionModeSlot()));
	QObject::connect(paintarea, SIGNAL(mousePressSignal(int, int)), this, SLOT(mousePressSlot(int, int)));
	QObject::connect(paintarea, SIGNAL(mouseMoveSignal(int, int)), this, SLOT(mousePressSlot(int, int)));
	QObject::connect(paintarea, SIGNAL(mouseReleaseSignal(int, int)), this, SLOT(mouseReleaseSlot(int, int)));
	QObject::connect(labelingimage, SIGNAL(updatedImage()), this, SLOT(drawImage()));
	QObject::connect(labelingimage, SIGNAL(mousePressSignal(int, int)), this, SLOT(mousePressSlot(int, int)));
	QObject::connect(labelingimage, SIGNAL(mouseMoveSignal(int, int)), this, SLOT(mousePressSlot(int, int)));
	QObject::connect(labelingimage, SIGNAL(mousePressSignal(int, int)), this, SLOT(mouseReleaseSlot(int, int)));
	QObject::connect(imageErosionButton, SIGNAL(clicked(bool)), this, SLOT(imageErosionSlot()));
	QObject::connect(imageDilationButton, SIGNAL(clicked(bool)), this, SLOT(imageDilationSlot()));
	QObject::connect(imageLabelingButton, SIGNAL(clicked(bool)), this, SLOT(imageLabelingSlot()));
	QObject::connect(imageEliminateIsolatedPixelButton, SIGNAL(clicked(bool)), this, SLOT(imageEliminatedIsolatedPixelSlot()));
	QObject::connect(imageFillButton, SIGNAL(clicked(bool)), this, SLOT(imageFillSlot()));
	QObject::connect(imageExtractSelectedRegionsButton, SIGNAL(clicked(bool)), this, SLOT(imageExtractSelectedRegionsSlot()));
	QObject::connect(imageSobelButton, SIGNAL(clicked(bool)), this, SLOT(imageSobelSlot()));
	QObject::connect(ballSmallImageButton, SIGNAL(clicked(bool)), this, SLOT(ballCategorySelectedSlot()));
	QObject::connect(fieldSmallImageButton, SIGNAL(clicked(bool)), this, SLOT(fieldCategorySelectedSlot()));
	QObject::connect(whitelineSmallImageButton, SIGNAL(clicked(bool)), this, SLOT(whitelineCategorySelectedSlot()));
	QObject::connect(goalpoleSmallImageButton, SIGNAL(clicked(bool)), this, SLOT(goalpoleCategorySelectedSlot()));
	QObject::connect(robotSmallImageButton, SIGNAL(clicked(bool)), this, SLOT(robotCategorySelectedSlot()));
	QObject::connect(superimposeLeftButton, SIGNAL(clicked(bool)), this, SLOT(superimposeLeftSlot()));
	QObject::connect(superimposeRightButton, SIGNAL(clicked(bool)), this, SLOT(superimposeRightSlot()));
}

void Interface::loadListFileSlot(void)
{
	listFileName = QFileDialog::getOpenFileName(this, "Open Image", "./");
	std::ifstream listFileStream(listFileName.toStdString().c_str());
	std::string line;
	listFile.clear();
	while(std::getline(listFileStream, line)) {
		listFile.push_back(line);
	}
	if(listFile.size() != 0) {
		loadImage(listFile[0].c_str());
		currentFileNameLineEdit->setText(QString(listFile[0].c_str()));
		labelingimage->applyColorTable();
	}
	listFileIndex = 0;
}

void Interface::nextImageSlot(void)
{
	listFileIndex++;
	if(listFileIndex >= listFile.size())
		listFileIndex = std::max<int>(listFile.size() - 1, 0);
	loadImage(listFile[listFileIndex].c_str());
	currentFileNameLineEdit->setText(QString(listFile[listFileIndex].c_str()));
	labelingimage->applyColorTable();
}

void Interface::clearImageSlot(void)
{
	paintarea->resetPixmapArea();
}

void Interface::clearBitmapImageSlot(void)
{
	labelingimage->clearCurrentBitmap();
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

void Interface::editPixSizeChanged(void)
{
	char buf[1024];
	sprintf(buf, "Edit Pixel size: %d", editPixSizeSlider->value());
	editPixSizeLabel->setText(buf);
	labelingimage->setEditPixSize(editPixSizeSlider->value());
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
	isSelectRegionMode = false;
}

void Interface::clearClickModeSlot(void)
{
	isSetColorTable = false;
	isClickColorTableMode = true;
	isClickPixMode = false;
	isSelectRegionMode = false;
}

void Interface::deletePixModeSlot(void)
{
	isDeletePixMode = true;
	isClickColorTableMode = false;
	isClickPixMode = true;
	isSelectRegionMode = false;
}

void Interface::writePixModeSlot(void)
{
	isDeletePixMode = false;
	isClickColorTableMode = false;
	isClickPixMode = true;
	isSelectRegionMode = false;
}

void Interface::selectRegionModeSlot(void)
{
	isSetColorTable = false;
	isClickColorTableMode = false;
	isClickPixMode = false;
	isSelectRegionMode = true;
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
			labelingimage->writePix(x, y);
	} else if(isSelectRegionMode) {
		labelingimage->selectRegion(x, y);
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

void Interface::imageEliminatedIsolatedPixelSlot(void)
{
	labelingimage->eliminateIsolatedPixel();
}

void Interface::imageFillSlot(void)
{
	labelingimage->fill();
}

void Interface::imageExtractSelectedRegionsSlot(void)
{
	labelingimage->extractSelectedRegion();
}

void Interface::imageSobelSlot(void)
{
	labelingimage->sobel();
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

void Interface::superimposeLeftSlot(void)
{
	labelingimage->imageAndOperation();
}

void Interface::superimposeRightSlot(void)
{
}

