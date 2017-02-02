
#include <QtGui>

#include <cstring>

#include "interface.h"
#include "paint.h"

Interface::Interface()
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
	image                     = new QLabel;
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
	paintarea                 = new PaintArea;
	catcherSizeSlider         = new QSlider;
	mainLayout                = new QVBoxLayout;
	winLayout                 = new QHBoxLayout;
	labelLayout               = new QGridLayout;
	buttonLayout              = new QVBoxLayout;
	colortableLayout          = new QVBoxLayout;
	imageProcessingLayout     = new QVBoxLayout;
	imageLayout               = new QVBoxLayout;

	image->setMinimumSize(320, 240);
	image->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
	image->setPixmap(paintarea->map);

	setClickModeRatioButton->setChecked(true);

	catcherSizeSlider->setTickPosition(QSlider::TicksBelow);
	catcherSizeSlider->setOrientation(Qt::Horizontal);
	catcherSizeSlider->setRange(1, 10);
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

	winLayout->addLayout(labelLayout);
	winLayout->addWidget(image);
	winLayout->addWidget(paintarea);
	mainLayout->addLayout(winLayout);

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
	QObject::connect(paintarea, SIGNAL(imageChanged()), this, SLOT(drawImage()));
	QObject::connect(selectCategoliesComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setObjectType()));
	QObject::connect(selectCategoliesComboBox, SIGNAL(highlighted(int)), this, SLOT(setObjectType()));
	QObject::connect(setClickModeRatioButton, SIGNAL(clicked(bool)), this, SLOT(setClickModeSlot()));
	QObject::connect(clearClickModeRatioButton, SIGNAL(clicked(bool)), this, SLOT(clearClickModeSlot()));
	QObject::connect(imageErosionButton, SIGNAL(clicked(bool)), paintarea, SLOT(imageErosion()));
	QObject::connect(imageDilationButton, SIGNAL(clicked(bool)), paintarea, SLOT(imageDilation()));
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
	paintarea->loadPixmapImage(filename);
}

void Interface::exportImageSlot(void)
{
	const char *filename = "export.png";
	paintarea->exportPixmapImage(filename);
}

void Interface::clearAllTableSlot(void)
{
	paintarea->clearTable();
	paintarea->applyTable();
}

void Interface::clearTableSlot(void)
{
	paintarea->clearCategolyTable();
	paintarea->applyTable();
}

void Interface::saveTableSlot(void)
{
	const char *filename = "table";
	paintarea->saveTable(filename);
	paintarea->applyTable();
}

void Interface::loadTableSlot(void)
{
	const char *filename = "table";
	paintarea->loadTable(filename);
	paintarea->applyTable();
}

void Interface::applyTableSlot(void)
{
	paintarea->applyTable();
}

void Interface::saveImage(const char *filename)
{
	paintarea->savePixmapImage(filename);
}

void Interface::loadImage(const char *filename)
{
	paintarea->loadPixmapImage(filename);
}

void Interface::catcherSizeChanged(void)
{
	char buf[1024];
	sprintf(buf, "Catcher size: %d", catcherSizeSlider->value());
	catcherSizeLabel->setText(buf);
	paintarea->setCatcherSize(catcherSizeSlider->value());
}

void Interface::drawImage(void)
{
	image->setPixmap(paintarea->map);
}

void Interface::setObjectType(void)
{
	paintarea->setCategoly(selectCategoliesComboBox->currentIndex());
	paintarea->applyTable();
}

void Interface::setClickModeSlot(void)
{
	paintarea->setMode(true);
}

void Interface::clearClickModeSlot(void)
{
	paintarea->setMode(false);
}

