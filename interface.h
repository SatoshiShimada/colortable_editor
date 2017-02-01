
#ifndef _INTERFACE_H_
#define _INTERFACE_H_

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

class Interface : public QMainWindow
{
	Q_OBJECT

protected:
	PaintArea *paintarea;
	QString filenameDrag;
	QWidget *window;
	QGroupBox *changeClickModeGroupBox;
	QGroupBox *colortableGroupBox;
	QGroupBox *imageGroupBox;
	QLabel *image;
	QLabel *filenameLabel;
	QLabel *catcherSizeLabel;
	QComboBox *selectCategoliesComboBox;
	QRadioButton *setClickModeRatioButton;
	QRadioButton *clearClickModeRatioButton;
	QPushButton *clearImageButton;
	QPushButton *saveImageButton;
	QPushButton *loadImageButton;
	QPushButton *clearAllTableButton;
	QPushButton *clearTableButton;
	QPushButton *saveTableButton;
	QPushButton *loadTableButton;
	QPushButton *applyTableButton;
	QLineEdit *filenameLine;
	QSlider *catcherSizeSlider;
	QVBoxLayout *mainLayout;
	QGridLayout *labelLayout;
	QHBoxLayout *winLayout;
	QVBoxLayout *buttonLayout;
	QVBoxLayout *colortableLayout;
	QVBoxLayout *imageLayout;
	void connection(void);

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
	void clearAllTableSlot(void);
	void clearTableSlot(void);
	void saveTableSlot(void);
	void loadTableSlot(void);
	void applyTableSlot(void);
	void catcherSizeChanged(void);
	void drawImage(void);
	void setObjectType(void);
	void setClickModeSlot(void);
	void clearClickModeSlot(void);
};

#endif // _INTERFACE_H_

