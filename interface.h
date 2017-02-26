
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <iostream>
#include <vector>
#include <QtGui>
#include <QtCore>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QDropEvent>
#include <QDrag>
#include <QUrl>
#include <QMimeData>
#include <QString>
#include <QFileDialog>

#include "paint.h"
#include "labeling_image.h"

class Interface : public QMainWindow
{
	Q_OBJECT

private:
	unsigned char filterColorFlag;
protected:
	void connection(void);
	void createWindow(void);
	void createMenus(void);
	void createActions(void);
#ifndef QT_NO_CONTEXTMENU
	void contextMenuEvent(QContextMenuEvent *event);
#endif //QT_NO_CONTEXTMENU
	void loadImage(const char *);
	void saveImage(const char *);
	void dragEnterEvent(QDragEnterEvent *e);
	void dropEvent(QDropEvent *e);
	void getSmallImages(void);
	PaintArea *paintarea;
	LabelingImage *labelingimage;
	QString filenameDrag;
	QString listFileName;
	QWidget *window;
	QMenu *imageMenu;
	QMenu *colortableMenu;
	QMenu *imageprocessingMenu;
	QAction *loadListFileAction;
	QAction *nextImageAction;
	QAction *clearImageAction;
	QAction *clearBitmapImageAction;
	QAction *loadImageAction;
	QAction *saveImageAction;
	QAction *exportImageAction;
	QAction *loadColortableAction;
	QAction *saveColortableAction;
	QAction *clearAllColortableAction;
	QAction *clearColortableAction;
	QAction *applyColortableAction;
	QAction *erosionAction;
	QAction *dilationAction;
	QAction *labelingAction;
	QAction *eliminateIsolatedPixelAction;
	QAction *expandIsolatedPointAction;
	QAction *extractRegionAction;
	QGroupBox *changeClickModeGroupBox;
	QGroupBox *colortableGroupBox;
	QGroupBox *imageGroupBox;
	QGroupBox *imageProcessingGroupBox;
	QGroupBox *filterColorGroupBox;
	QLabel *image;
	QLabel *filenameLabel;
	QLabel *marginSizeLabel;
	QLabel *editPixSizeLabel;
	QLabel *ballSmallImageLabel;
	QLabel *fieldSmallImageLabel;
	QLabel *whitelineSmallImageLabel;
	QLabel *goalpoleSmallImageLabel;
	QLabel *robotSmallImageLabel;
	QLineEdit *currentFileNameLineEdit;
	QPixmap *ballSmallImagePixmap;
	QPixmap *fieldSmallImagePixmap;
	QPixmap *whitelineSmallImagePixmap;
	QPixmap *goalpoleSmallImagePixmap;
	QPixmap *robotSmallImagePixmap;
	QComboBox *selectCategoriesComboBox;
	QRadioButton *setClickModeRadioButton;
	QRadioButton *clearClickModeRadioButton;
	QRadioButton *deletePixModeRadioButton;
	QRadioButton *writePixModeRadioButton;
	QRadioButton *selectRegionRadioButton;
	QCheckBox *filterRedCheckBox;
	QCheckBox *filterGreenCheckBox;
	QCheckBox *filterBlueCheckBox;
	QPushButton *loadListFileButton;
	QPushButton *nextImageButton;
	QPushButton *clearImageButton;
	QPushButton *clearBitmapImageButton;
	QPushButton *saveImageButton;
	QPushButton *loadImageButton;
	QPushButton *exportImageButton;
	QPushButton *clearAllTableButton;
	QPushButton *clearTableButton;
	QPushButton *saveTableButton;
	QPushButton *loadTableButton;
	QPushButton *applyTableButton;
	QPushButton *imageErosionButton;
	QPushButton *imageDilationButton;
	QPushButton *imageLabelingButton;
	QPushButton *imageEliminateIsolatedPixelButton;
	QPushButton *imageExpandButton;
	QPushButton *imageExtractSelectedRegionsButton;
	QPushButton *imageSobelButton;
	QPushButton *imageFillRegionButton;
	QPushButton *ballSmallImageButton;
	QPushButton *fieldSmallImageButton;
	QPushButton *whitelineSmallImageButton;
	QPushButton *goalpoleSmallImageButton;
	QPushButton *robotSmallImageButton;
	QPushButton *superimposeLeftButton;
	QPushButton *superimposeRightButton;
	QLineEdit *filenameLine;
	QSlider *marginSizeSlider;
	QSlider *editPixSizeSlider;
	QGridLayout *mainLayout;
	QGridLayout *labelLayout;
	QVBoxLayout *superimposeButtonsLayout;
	QVBoxLayout *buttonLayout;
	QVBoxLayout *colortableLayout;
	QVBoxLayout *imageProcessingLayout;
	QVBoxLayout *filterColorLayout;
	QVBoxLayout *imageLayout;
	QVBoxLayout *ballSmallImageLayout;
	QVBoxLayout *fieldSmallImageLayout;
	QVBoxLayout *whitelineSmallImageLayout;
	QVBoxLayout *goalpoleSmallImageLayout;
	QVBoxLayout *robotSmallImageLayout;
	QHBoxLayout *smallImageLayout;
	bool isSetColorTable;
	bool isClickPixMode;
	bool isClickColorTableMode;
	bool isDeletePixMode;
	bool isSelectRegionMode;
	bool isClickSelectPoint;
	int width;
	int height;
	int smallImageWidth;
	int smallImageHeight;
	int listFileIndex;
	const int categories;
	std::vector<std::string> listFile;
	std::vector<int> clickPointList;
public:
	Interface();
	~Interface();
private slots:
	void loadListFileSlot(void);
	void nextImageSlot(void);
	void clearImageSlot(void);
	void clearBitmapImageSlot(void);
	void saveImageSlot(void);
	void loadImageSlot(void);
	void exportImageSlot(void);
	void clearAllTableSlot(void);
	void clearTableSlot(void);
	void saveTableSlot(void);
	void loadTableSlot(void);
	void applyTableSlot(void);
	void marginSizeChanged(void);
	void editPixSizeChanged(void);
	void drawImage(void);
	void setObjectType(void);
	void setClickModeSlot(void);
	void clearClickModeSlot(void);
	void deletePixModeSlot(void);
	void writePixModeSlot(void);
	void selectRegionModeSlot(void);
	void mousePressSlot(int, int);
	void mouseReleaseSlot(int, int);
	void imageErosionSlot(void);
	void imageDilationSlot(void);
	void imageLabelingSlot(void);
	void imageEliminatedIsolatedPixelSlot(void);
	void imageExpandSlot(void);
	void imageExtractSelectedRegionsSlot(void);
	void imageSobelSlot(void);
	void imageFillRegionSlot(void);
	void ballCategorySelectedSlot(void);
	void fieldCategorySelectedSlot(void);
	void whitelineCategorySelectedSlot(void);
	void goalpoleCategorySelectedSlot(void);
	void robotCategorySelectedSlot(void);
	void superimposeLeftSlot(void);
	void superimposeRightSlot(void);
	void filterColorRedSlot(void);
	void filterColorGreenSlot(void);
	void filterColorBlueSlot(void);
};

#endif //__INTERFACE_H__

