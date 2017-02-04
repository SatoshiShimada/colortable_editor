
#include <QtGui>

#include <cstring>

#include "interface.h"
#include "paint.h"
#include "labeling_image.h"

Interface::Interface() : QMainWindow(), isSetColorTable(true), isClickPixMode(false), isClickColorTableMode(true), isDeletePixMode(true)
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
	marginSizeLabel           = new QLabel("margin size: ");
	deleteSizeLabel           = new QLabel("Delete size: ");
	selectCategoliesComboBox  = new QComboBox();
	setClickModeRadioButton   = new QRadioButton("Set");
	clearClickModeRadioButton = new QRadioButton("Clear");
	deletePixModeRadioButton  = new QRadioButton("Delete");
	changeClickModeGroupBox   = new QGroupBox("Click mode");
	colortableGroupBox        = new QGroupBox("color table");
	imageGroupBox             = new QGroupBox("image");
	imageProcessingGroupBox   = new QGroupBox("Image Processing");
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
	paintarea                 = new PaintArea(320, 240);
	labelingimage             = new LabelingImage(320, 240, 6);
	marginSizeSlider          = new QSlider;
	deleteSizeSlider          = new QSlider;
	mainLayout                = new QHBoxLayout;
	labelLayout               = new QGridLayout;
	buttonLayout              = new QVBoxLayout;
	colortableLayout          = new QVBoxLayout;
	imageProcessingLayout     = new QVBoxLayout;
	imageLayout               = new QVBoxLayout;

	setClickModeRadioButton->setChecked(true);

	marginSizeSlider->setTickPosition(QSlider::TicksBelow);
	marginSizeSlider->setOrientation(Qt::Horizontal);
	marginSizeSlider->setRange(0, 10);
	marginSizeLabel->setText("margin size: 1");

	deleteSizeSlider->setTickPosition(QSlider::TicksBelow);
	deleteSizeSlider->setOrientation(Qt::Horizontal);
	deleteSizeSlider->setRange(1, 10);
	deleteSizeLabel->setText("Delete size: 1");

	selectCategoliesComboBox->addItem(QString("Ball"));
	selectCategoliesComboBox->addItem(QString("Goal"));
	selectCategoliesComboBox->addItem(QString("White Line"));
	selectCategoliesComboBox->addItem(QString("Field"));
	selectCategoliesComboBox->addItem(QString("Robot"));
	selectCategoliesComboBox->addItem(QString("Back Ground"));

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

	imageLayout->addWidget(clearImageButton);
	imageLayout->addWidget(saveImageButton);
	imageLayout->addWidget(loadImageButton);
	imageLayout->addWidget(exportImageButton);
	imageGroupBox->setLayout(imageLayout);

	imageProcessingLayout->addWidget(imageErosionButton);
	imageProcessingLayout->addWidget(imageDilationButton);
	imageProcessingGroupBox->setLayout(imageProcessingLayout);

	labelLayout->addWidget(imageGroupBox, 1, 1);
	labelLayout->addWidget(colortableGroupBox, 1, 2);
	labelLayout->addWidget(selectCategoliesComboBox, 2, 1);
	labelLayout->addWidget(imageProcessingGroupBox, 3, 1);
	labelLayout->addWidget(changeClickModeGroupBox, 3, 2);
	labelLayout->addWidget(marginSizeLabel, 4, 1);
	labelLayout->addWidget(marginSizeSlider, 4, 2);
	labelLayout->addWidget(deleteSizeLabel, 5, 1);
	labelLayout->addWidget(deleteSizeSlider, 5, 2);

	mainLayout->addLayout(labelLayout);
	mainLayout->addWidget(labelingimage);
	mainLayout->addWidget(paintarea);

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
	QObject::connect(selectCategoliesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setObjectType()));
	QObject::connect(selectCategoliesComboBox, SIGNAL(highlighted(int)), this, SLOT(setObjectType()));
	QObject::connect(setClickModeRadioButton, SIGNAL(clicked(bool)), this, SLOT(setClickModeSlot()));
	QObject::connect(clearClickModeRadioButton, SIGNAL(clicked(bool)), this, SLOT(clearClickModeSlot()));
	QObject::connect(deletePixModeRadioButton, SIGNAL(clicked(bool)), this, SLOT(deletePixModeSlot()));
	QObject::connect(paintarea, SIGNAL(mousePressSignal(int, int)), this, SLOT(mousePressSlot(int, int)));
	QObject::connect(paintarea, SIGNAL(mouseMoveSignal(int, int)), this, SLOT(mousePressSlot(int, int)));
	QObject::connect(paintarea, SIGNAL(mouseReleaseSignal(int, int)), this, SLOT(mouseReleaseSlot(int, int)));
	QObject::connect(labelingimage, SIGNAL(updatedImage()), this, SLOT(drawImage()));
	QObject::connect(imageErosionButton, SIGNAL(clicked(bool)), this, SLOT(imageErosionSlot()));
	QObject::connect(imageDilationButton, SIGNAL(clicked(bool)), this, SLOT(imageDilationSlot()));
}

void Interface::clearImageSlot(void)
{
	paintarea->resetPixmapArea();
}

void Interface::saveImageSlot(void)
{
	const char *filename = "out.png";
	paintarea->savePixmapImage(filename);
}

void Interface::loadImageSlot(void)
{
	const char *filename = "out.png";
	loadImage(filename);
}

void Interface::exportImageSlot(void)
{
	const char *filename = "export.png";
	labelingimage->exportImage(filename);
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
	const char *filename = "table";
	labelingimage->saveColorTable(filename);
}

void Interface::loadTableSlot(void)
{
	const char *filename = "table";
	labelingimage->loadColorTable(filename);
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
	sprintf(buf, "margin size: %d", marginSizeSlider->value());
	marginSizeLabel->setText(buf);
	labelingimage->setMargin(marginSizeSlider->value());
}

void Interface::deleteSizeChanged(void)
{
	char buf[1024];
	sprintf(buf, "Delete size: %d", deleteSizeSlider->value());
	deleteSizeLabel->setText(buf);
	//labelingimage->setMargin(marginSizeSlider->value());
}

void Interface::drawImage(void)
{
	labelingimage->update();
}

void Interface::setObjectType(void)
{
	labelingimage->setIndex(selectCategoliesComboBox->currentIndex());
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

