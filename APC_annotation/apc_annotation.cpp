#include "apc_annotation.h"
APC_annotation::APC_annotation(){
	this->dirPath = QString();
	imageLabel = new QlabelClickable(this);
	imageLabel->Qpiximage = QPixmap("ais.png");
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setPixmap(imageLabel->Qpiximage);
	imageLabel->imageMaskBackup =cv::imread(this->imagePath.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);
}
APC_annotation::~APC_annotation(){ }
void APC_annotation::start()
    {
	  //this->move(100,100);
      QPushButton *button = new QPushButton(this);

      button->setText("Select new Image");

      QObject::connect(button, SIGNAL(clicked()),this, SLOT(clickedSlot()));
      button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

      this->centralWidget = new QWidget(this);
      this->centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
      this->centralWidget->setGeometry(0,0,300,100);
      QPalette Pal(palette());
      Pal.setColor(QPalette::Background, Qt::black);
      this->centralWidget->setAutoFillBackground(true);
      this->centralWidget->setPalette(Pal);
      this->layout = new QVBoxLayout (centralWidget);
      this->layout->addWidget(button);
      this->layout->addWidget(imageLabel);

      setCentralWidget(centralWidget);
      setWindowTitle("Ais APC");

      show();
    }
void APC_annotation::addNextImage()
{
	slotPickNextImage();
}

void APC_annotation::slotPickNextImage()
{
	//this->show();
	QMessageBox *msgBox  = new QMessageBox();
	if (this->workingDirIterator->hasNext())
	{
		msgBox->setText("Loading next Image");
		//msgBox->show();

		this->imagePath = this->workingDirIterator->next();
		this->dirPath = QFileInfo(imagePath).path();
		QDir parentDir =QFileInfo(this->dirPath).dir()  ;
		cvImagesavepath = parentDir.path()+"/" +QFileInfo(imagePath).fileName().split(".",QString::SkipEmptyParts).at(0);
		if (!QDir(cvImagesavepath).exists() )
		{
			QDir().mkdir(cvImagesavepath);
		}
		this->setImageInitial();
	}
		else {
			msgBox->setText("No more images");
			msgBox->show();
		}

}
void APC_annotation::clickedSlot()
     {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Hello");
        QStringList fileName ;
        if (this->dirPath.isNull()	 == true) {
        	fileName =
        		QFileDialog::getOpenFileNames(this, "Select a file to open...", QDir::homePath()+"/Desktop/ImageAnnotaion/",
				tr("Images (*.png *.xpm *.jpg)"));
        }
        else
        {
        	fileName =
        			QFileDialog::getOpenFileNames(this, "Select a file to open...", this->dirPath,
					tr("Images (*.png *.xpm *.jpg)"));
        }
        QString strListItems = fileName.join("\n");
        this->imagePath = strListItems;
        this->dirPath = QFileInfo(imagePath).path();
        this->workingDirIterator =new QDirIterator(this->dirPath,QStringList() << "*.jpg", QDir::Files);
        //this->workingDirIterator->next();
    	QDir parentDir =QFileInfo(this->dirPath).dir()  ;
    	cvImagesavepath = parentDir.path() +"/"+ QFileInfo(imagePath).fileName().split(".",QString::SkipEmptyParts).at(0);
		if (!QDir(cvImagesavepath).exists())
		{
			QDir().mkdir(cvImagesavepath);
		}
        setImageInitial();

     }
void APC_annotation::setImageInitial()
{
	// initialize opencv image
	QMessageBox msgBox;
	msgBox.setText("setImageInitial");
	//msgBox.show();
	imageLabel->Qpiximage = QPixmap (this->imagePath);
	imageLabel->setFixedSize(imageLabel->Qpiximage.size());
	imageLabel->setPixmap(imageLabel->Qpiximage);
	imageLabel->imageMaskBackup =cv::imread(this->imagePath.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);
	imageLabel->imageMaskBackup = cv::Scalar(0);
	imageLabel->dirPath =this->dirPath;
	imageLabel->imagePath=this->imagePath;
	imageLabel->cvImagesavepath=this->cvImagesavepath;
	this->layout->update();
	show();
}


QString APC_annotation::getImagePath()
{
	return this->imagePath;
}

void APC_annotation::returnfromChild()
{

	this->addNextImage();
}


// QlabelClickable members definition

QlabelClickable::QlabelClickable(  QWidget * parent )
:QLabel(parent)
{
	this->noOfVertivces =0;
	this->flag_isConvex = false;
	connect( this, SIGNAL( clicked() ), this, SLOT( slotClicked() ) );
	connect(this,SIGNAL( convexDone() ),this,SLOT(slotConvexDone() ));
	connect(this,SIGNAL( callbackParent() ) ,this->parent(),SLOT(returnfromChild()) );

	for (int i =0 ; i< 50;i++)
	{
		objectslist.append("Object"+QString::number(i));
	}
}

void QlabelClickable::slotClicked()
{
	QMessageBox Msgbox;
	std::ostringstream ss;
	ss <<clickedPixel.x<<"  "<<clickedPixel.y;
	if (this->noOfVertivces ==0){
		firstPixel = clickedPixel;
	}
	Msgbox.setText(QString::fromStdString(ss.str()));
	//Msgbox.show();
	QImage tmp(this->pixmap()->toImage());
	QPainter painter(&tmp);
	QPen paintpen(Qt::red);
	paintpen.setWidth(2);
	QPoint p1;
	p1.setX(clickedPixel.x);
	p1.setY(clickedPixel.y);
	painter.setPen(paintpen);
	painter.drawPoint(p1);

	if (this->noOfVertivces >0)
	{
		//check if current pixel is close to first Pixel
		// I'm Considering euclidean distance and distance of 100 pixels
		if (pow (this->firstPixel.x - clickedPixel.x,2)+ pow (this->firstPixel.y - clickedPixel.y,2) <=100)
		{
			clickedPixel.x = this->firstPixel.x;
			clickedPixel.y = this->firstPixel.y;
			this->flag_isConvex=true;
		}
		this->convexVertices.push_back(clickedPixel);
		this->noOfVertivces++;
		painter.drawLine(this->convexVertices[this->convexVertices.size() -2].x,
				this->convexVertices[this->convexVertices.size() -2].y,
				this->convexVertices[this->convexVertices.size()-1].x,
				this->convexVertices[this->convexVertices.size()-1].y);
	}
	else
	{
		this->convexVertices.push_back(clickedPixel);
		this->noOfVertivces++;
	}
	this->setPixmap(QPixmap::fromImage(tmp));
	this->show();
	if (this->flag_isConvex == true){
				emit convexDone();
			}
}

void QlabelClickable::slotConvexDone()
{
	 QMessageBox::StandardButton reply;
	  reply = QMessageBox::question(this, "Test", "Loop closed, Save current image and select next?",
	                                QMessageBox::Yes|QMessageBox::No);
	  if (reply == QMessageBox::Yes) {
		  this->saveAndContinue();
		  emit callbackParent();
	  } else {
		  saveAndContinue();
	  }
}

void QlabelClickable::saveCVoperations()
{
		//convert Point2f to Point2i
		for (int i=0;i<this->convexVertices.size();i++) {
			this->convexPoints.push_back(cv::Point((int) this->convexVertices[i].x,
					(int) this->convexVertices[i].y));
		}
		cv::Mat objectMask = imageMaskBackup.clone();
		cv::Point* tempPtr = &(this->convexPoints[0]);
		fillConvexPoly(objectMask,tempPtr,convexPoints.size(),cv::Scalar(255));
		QWidget * newWidget= new QWidget();
		QString objectSelected = QInputDialog::getItem(newWidget,"Object list","Select the object name ",
				this->objectslist);
		QString imgname =   cvImagesavepath +"/"+objectSelected+".png";
		cv::imwrite(imgname.toStdString(),objectMask );
		QMessageBox *Msgbox = new QMessageBox();
		Msgbox->setText("Image written to " + imgname + " # "+ QString::number(convexPoints.size()));
		//Msgbox->show();

}
void QlabelClickable::saveAndContinue()
{
//CV code to save *** moved to a new function ***
// should prompt image name
// for now just continue by resetting the noOfVertivces, flag_isConvex, and convexVertices

	this->saveCVoperations();

	this->flag_isConvex =false;
	this->noOfVertivces =0;
	this->convexVertices.clear();
	this->convexPoints.clear();
	this->show();
}
void QlabelClickable::mousePressEvent ( QMouseEvent *event )
{
	this->clickedPixel= cv::Point2f((float)event->x(), (float)event->y());
	if (!this->flag_isConvex){
		emit clicked();
	}
}



















