
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

protected:
	void connection(void);
	void createWindow(void);
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
	QGroupBox *changeClickModeGroupBox;
	QGroupBox *colortableGroupBox;
	QGroupBox *imageGroupBox;
	QGroupBox *imageProcessingGroupBox;
	QLabel *image;
	QLabel *filenameLabel;
	QLabel *marginSizeLabel;
	QLabel *deleteSizeLabel;
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
	QPushButton *loadListFileButton;
	QPushButton *nextImageButton;
	QPushButton *clearImageButton;
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
	QPushButton *ballSmallImageButton;
	QPushButton *fieldSmallImageButton;
	QPushButton *whitelineSmallImageButton;
	QPushButton *goalpoleSmallImageButton;
	QPushButton *robotSmallImageButton;
	QLineEdit *filenameLine;
	QSlider *marginSizeSlider;
	QSlider *deleteSizeSlider;
	QGridLayout *mainLayout;
	QGridLayout *labelLayout;
	QVBoxLayout *buttonLayout;
	QVBoxLayout *colortableLayout;
	QVBoxLayout *imageProcessingLayout;
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
	int width;
	int height;
	int smallImageWidth;
	int smallImageHeight;
	int listFileIndex;
	const int categories;
	std::vector<std::string> listFile;
public:
	Interface();
	~Interface();
private slots:
	void loadListFileSlot(void);
	void nextImageSlot(void);
	void clearImageSlot(void);
	void saveImageSlot(void);
	void loadImageSlot(void);
	void exportImageSlot(void);
	void clearAllTableSlot(void);
	void clearTableSlot(void);
	void saveTableSlot(void);
	void loadTableSlot(void);
	void applyTableSlot(void);
	void marginSizeChanged(void);
	void deleteSizeChanged(void);
	void drawImage(void);
	void setObjectType(void);
	void setClickModeSlot(void);
	void clearClickModeSlot(void);
	void deletePixModeSlot(void);
	void mousePressSlot(int, int);
	void mouseReleaseSlot(int, int);
	void imageErosionSlot(void);
	void imageDilationSlot(void);
	void imageLabelingSlot(void);
	void imageEliminatedIsolatedPixelSlot(void);
	void ballCategorySelectedSlot(void);
	void fieldCategorySelectedSlot(void);
	void whitelineCategorySelectedSlot(void);
	void goalpoleCategorySelectedSlot(void);
	void robotCategorySelectedSlot(void);
};

#endif //__INTERFACE_H__

