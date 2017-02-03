
#include <QtGui>

#include <cstring>

#include "interface.h"
#include "paint.h"
#include "labeling_image.h"

Interface::Interface() : QMainWindow(), isSetColorTable(true)
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
	catcherSizeLabel          = new QLabel("Catcher size: ");
	selectCategoliesComboBox  = new QComboBox();
	setClickModeRatioButton   = new QRadioButton("Set");
	clearClickModeRatioButton = new QRadioButton("Clear");
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
	catcherSizeSlider         = new QSlider;
	mainLayout                = new QHBoxLayout;
	labelLayout               = new QGridLayout;
	buttonLayout              = new QVBoxLayout;
	colortableLayout          = new QVBoxLayout;
	imageProcessingLayout     = new QVBoxLayout;
	imageLayout               = new QVBoxLayout;

	setClickModeRatioButton->setChecked(true);

	catcherSizeSlider->setTickPosition(QSlider::TicksBelow);
	catcherSizeSlider->setOrientation(Qt::Horizontal);
	catcherSizeSlider->setRange(0, 10);
	catcherSizeLabel->setText("Catcher size: 1");

	selectCategoliesComboBox->addItem(QString("Ball"));
	selectCategoliesComboBox->addItem(QString("Goal"));
	selectCategoliesComboBox->addItem(QString("White Line"));
	selectCategoliesComboBox->addItem(QString("Field"));
	selectCategoliesComboBox->addItem(QString("Robot"));
	selectCategoliesComboBox->addItem(QString("Back Ground"));

	buttonLayout->addWidget(setClickModeRatioButton);
	buttonLayout->addWidget(clearClickModeRatioButton);
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
	labelLayout->addWidget(changeClickModeGroupBox, 2, 2);
	labelLayout->addWidget(imageProcessingGroupBox, 3, 1);
	labelLayout->addWidget(catcherSizeLabel, 4, 1);
	labelLayout->addWidget(catcherSizeSlider, 4, 2);

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
	QObject::connect(catcherSizeSlider, SIGNAL(sliderReleased()), this, SLOT(catcherSizeChanged()));
	QObject::connect(selectCategoliesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setObjectType()));
	QObject::connect(selectCategoliesComboBox, SIGNAL(highlighted(int)), this, SLOT(setObjectType()));
	QObject::connect(setClickModeRatioButton, SIGNAL(clicked(bool)), this, SLOT(setClickModeSlot()));
	QObject::connect(clearClickModeRatioButton, SIGNAL(clicked(bool)), this, SLOT(clearClickModeSlot()));
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

void Interface::catcherSizeChanged(void)
{
	char buf[1024];
	sprintf(buf, "Catcher size: %d", catcherSizeSlider->value());
	catcherSizeLabel->setText(buf);
	labelingimage->setMargin(catcherSizeSlider->value());
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
}

void Interface::clearClickModeSlot(void)
{
	isSetColorTable = false;
}

void Interface::mousePressSlot(int x, int y)
{
	if(isSetColorTable)
		labelingimage->setBitColorTable(x, y);
	else
		labelingimage->clearBitColorTable(x, y);
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

