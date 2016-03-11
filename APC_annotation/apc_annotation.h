#ifndef APC_ANNOTATION_H
#define APC_ANNOTATION_H

#include <QtGui/QWidget>
#include "ui_apc_annotation.h"
#include <QDirIterator>
#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFileDialog>
#include <QDir>
#include <QDesktopServices>
#include <QLabel>
#include <QPainter>
#include <QPalette>
#include <QDebug>
#include <QFileInfo>
#include <QTimer>
#include <QStringList>
#include <QListWidget>
#include <QInputDialog>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <QMouseEvent>
#include <string>
#include <vector>

class QlabelClickable: public QLabel
{

	std::vector<cv::Point2f> convexVertices;
	std::vector<cv::Point> convexPoints;
	int noOfVertivces;
	cv::Point2f firstPixel;
	cv::Point2f clickedPixel;
	bool flag_isConvex;
	Q_OBJECT
	public:
	cv::Mat imageMaskBackup;
	QString dirPath;
	QString imagePath;
	QString cvImagesavepath;
	QStringList objectslist;
	QPixmap Qpiximage;
	QlabelClickable(  QWidget * parent = 0 );
	void saveAndContinue();
	void saveCVoperations();
		~QlabelClickable(){}

	signals:
		void clicked();
		void convexDone();
		void callbackParent();

	public slots:
		void slotClicked();
		void slotConvexDone();

	protected:
		void mousePressEvent ( QMouseEvent * event ) ;
};

class APC_annotation :  public QMainWindow
{
    Q_OBJECT

public:
    APC_annotation();
    ~APC_annotation();
    void start();
    void setImageInitial();
    QString getImagePath();
    void addNextImage();

private:
    Ui::APC_annotationClass ui;
    QString imagePath;
    QString dirPath;
    QWidget* centralWidget;
    QVBoxLayout* layout;
    QDirIterator* workingDirIterator;
    QString cvImagesavepath;
    bool isNextButtonadded = false;
    bool promptfile = true;
    QlabelClickable *imageLabel;
    QPushButton *button;


public slots:
         void clickedSlot();
         void returnfromChild();
         void slotPickNextImage();
};



#endif // APC_ANNOTATION_H