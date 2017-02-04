
#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <iostream>
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

#include "paint.h"
#include "labeling_image.h"

class Interface : public QMainWindow
{
	Q_OBJECT

protected:
	PaintArea *paintarea;
	LabelingImage *labelingimage;
	QString filenameDrag;
	QWidget *window;
	QGroupBox *changeClickModeGroupBox;
	QGroupBox *colortableGroupBox;
	QGroupBox *imageGroupBox;
	QGroupBox *imageProcessingGroupBox;
	QLabel *image;
	QLabel *filenameLabel;
	QLabel *marginSizeLabel;
	QLabel *deleteSizeLabel;
	QComboBox *selectCategoriesComboBox;
	QRadioButton *setClickModeRadioButton;
	QRadioButton *clearClickModeRadioButton;
	QRadioButton *deletePixModeRadioButton;
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
	QLineEdit *filenameLine;
	QSlider *marginSizeSlider;
	QSlider *deleteSizeSlider;
	QHBoxLayout *mainLayout;
	QGridLayout *labelLayout;
	QVBoxLayout *buttonLayout;
	QVBoxLayout *colortableLayout;
	QVBoxLayout *imageProcessingLayout;
	QVBoxLayout *imageLayout;
	void connection(void);
	bool isSetColorTable;
	bool isClickPixMode;
	bool isClickColorTableMode;
	bool isDeletePixMode;
public:
	Interface();
	~Interface();
	void createWindow(void);
	void loadImage(const char *);
	void saveImage(const char *);
	void dragEnterEvent(QDragEnterEvent *e);
	void dropEvent(QDropEvent *e);
private slots:
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
};

#endif //__INTERFACE_H__

