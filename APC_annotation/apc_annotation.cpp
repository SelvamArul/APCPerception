#include "apc_annotation.h"
APC_annotation::APC_annotation(){
	this->dirPath = QString();
	imageLabel = new QlabelClickable(this);
	imageLabel->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
	imageLabel->Qpiximage = QPixmap("ais.png");
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setPixmap(imageLabel->Qpiximage);
	imageLabel->imageMaskBackup =cv::imread(this->imagePath.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);

}
APC_annotation::~APC_annotation(){ }
void APC_annotation::start()
    {
	  std::unique_ptr<QPushButton> button(new QPushButton);
	  std::unique_ptr<QPushButton> nextButton(new QPushButton);
      button->setText("Select new Directory");
      nextButton->setText("Next Image >>");
      button->setMinimumSize(100,50);
      nextButton->setMaximumSize(500,50);

      QObject::connect(button.get(), SIGNAL(clicked()),this, SLOT(clickedSlot()));
      QObject::connect(nextButton.get(),SIGNAL( clicked() ) ,this,SLOT(returnfromChild()) );
      button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
      nextButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

      std::unique_ptr<QShortcut> shortcutOpen(new QShortcut(QKeySequence("Ctrl+O"), this));
      std::unique_ptr<QShortcut> shortcutNext(new QShortcut(QKeySequence("Ctrl+N"), this));



      QObject::connect(shortcutOpen.get(), SIGNAL(activated()), this, SLOT(clickedSlot()));
      QObject::connect(shortcutNext.get(), SIGNAL(activated()), this, SLOT(returnfromChild()));


      this->resize(800,800);
      QPalette Pal(palette());
      Pal.setColor(QPalette::Background, Qt::black);

      std::unique_ptr<QHBoxLayout> buttonLayout(new QHBoxLayout);
      buttonLayout.get()->addWidget(button.get());
      buttonLayout.get()->addWidget(nextButton.get());

      this->layout = new QVBoxLayout (this);
      this->layout->addLayout(buttonLayout.get());
      this->layout->addWidget(this->imageLabel);

      setWindowTitle("Ais Image annotation tool");
      show();
    }
void APC_annotation::addNextImage()
{
	slotPickNextImage();
}

void APC_annotation::slotPickNextImage()
{
	QMessageBox *msgBox  = new QMessageBox();
	if (this->workingDirIterator->hasNext())
	{
		msgBox->setText("Loading next Image");
		QString temp = this->workingDirIterator->next();
		cvImagesavepath = temp +"/" ;
		if (!QDir(cvImagesavepath).exists())
			{
				QDir().mkdir(cvImagesavepath);
			}
		this->imagePath = temp + "/rgb.jpg";
		this->setImageInitial();
	}
		else {
			msgBox->setText("No more images");
			msgBox->show();
		}


}
void APC_annotation::clickedSlot()
     {

		/*
		 * Iterate through the sub directories and look for image named "rgb.jpg"
		 * create new images of objectmasks with name of the object
		 */
        QMessageBox msgBox;
        msgBox.setWindowTitle("Hello");
        QString fileName ;
        if (this->dirPath.isNull()	 == true) {
        	fileName =
        		QFileDialog::getExistingDirectory(this, "Select a directory to open", QDir::homePath()+"/arul/APCImages/",
        				QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
        }
        else
        {
        	fileName =
        			QFileDialog::getExistingDirectory(this, "Select a directory to open", this->dirPath,
        					QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
        }
        std::cout<<"The directory is : "<<fileName.toUtf8().constData()<<std::endl;
        if (!fileName.isEmpty())
        {
        	msgBox.setText(fileName);
        				msgBox.show();
			this->dirPath = QFileInfo(fileName).path();
			std::cout<<"The dirPath is : "<<dirPath.toUtf8().constData()<<std::endl;
			this->workingDirIterator =new QDirIterator(fileName, QDir::NoDotAndDotDot| QDir::Dirs ,QDirIterator::Subdirectories);

			// the directory iterator has been initialized
			// From now on, I should work only with this iterator
			QString temp = this->workingDirIterator->next();
			std::cout<<"Returned from temp "<<temp.toUtf8().constData()<<std::endl;

			cvImagesavepath = temp +"/" ;
			std::cout<<"The cvImagesavepath is : "<<cvImagesavepath.toUtf8().constData()<<std::endl;
			if (!QDir(cvImagesavepath).exists())
			{
				QDir().mkdir(cvImagesavepath);
			}
			this->imagePath = temp + "/rgb.jpg";
			std::cout<<"The imageread path  is : "<<this->imagePath.toUtf8().constData()<<std::endl;
			setImageInitial();
        }

     }
void APC_annotation::setImageInitial()
{
	this->imageLabel->flag_isConvex =false;
	this->imageLabel->noOfVertivces =0;
	this->imageLabel->convexVertices.clear();
	// initialize opencv image
	QMessageBox msgBox;
	msgBox.setText("setImageInitial");
	imageLabel->Qpiximage = QPixmap (this->imagePath);
	imageLabel->setPixmap(imageLabel->Qpiximage /*.scaled(480,270,Qt::KeepAspectRatio)*/); //.scaled(1000,1000,Qt::KeepAspectRatio)
	imageLabel->setScaledContents(true);
	imageLabel->imageMaskBackup =cv::imread(this->imagePath.toStdString(),CV_LOAD_IMAGE_GRAYSCALE);
	imageLabel->imageMaskBackup = cv::Scalar(0);
	imageLabel->dirPath =this->dirPath;
	imageLabel->imagePath=this->imagePath;
	imageLabel->cvImagesavepath=this->cvImagesavepath;
	this->layout->update();
	this->isNextButtonadded = true;
	show();
}


QString APC_annotation::getImagePath()
{
	return this->imagePath;
}

void APC_annotation::returnfromChild()
{
	if (this->isNextButtonadded)
		this->slotPickNextImage();
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
	QImage tmp(this->pixmap()->toImage());
	QPainter painter(&tmp);
	QPen paintpen(Qt::red);
	paintpen.setWidth(5);
	QPoint p1;

	QRect rect = pixmap()->rect();
	float scale = std::min((float)width()/rect.width(), (float)height()/rect.height());

	p1 = (1.0/scale) * QPoint(clickedPixel.x, clickedPixel.y);
	if (this->noOfVertivces ==0){
			firstPixel = cv::Point(p1.x(),p1.y());
		}
	ss <<p1.x()<<"  "<<p1.y();
	Msgbox.setText(QString::fromStdString(ss.str()));
	Msgbox.show();
	painter.setPen(paintpen);
	painter.drawPoint(p1);


	if (this->noOfVertivces >0)
	{
		//check if current pixel is close to first Pixel
		// I'm Considering euclidean distance and distance of 10 pixels
		if (pow (this->firstPixel.x - p1.x(),2)+ pow (this->firstPixel.y - p1.y(),2) <=100)
		{
			p1 = QPoint(firstPixel.x, firstPixel.y);
			this->flag_isConvex=true;
		}
		this->convexVertices.push_back(cv::Point(p1.x(),p1.y()));
		this->noOfVertivces++;
		painter.drawLine(this->convexVertices[this->convexVertices.size() -2].x,
				this->convexVertices[this->convexVertices.size() -2].y,
				this->convexVertices[this->convexVertices.size()-1].x,
				this->convexVertices[this->convexVertices.size()-1].y);
	}
	else
	{
		this->convexVertices.push_back(cv::Point(p1.x(),p1.y()));
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
	/* QMessageBox::StandardButton reply;
	  reply = QMessageBox::question(this, "Test", "Loop closed, Save current image and select next?",
	                                QMessageBox::Yes|QMessageBox::No);
	  if (reply == QMessageBox::Yes) {
		  this->saveAndContinue();
		  emit callbackParent();
	  } else {
		  saveAndContinue();
	  }*/
	saveAndContinue();
}

void QlabelClickable::saveCVoperations()
{
		cv::Mat objectMask = imageMaskBackup.clone();
		cv::Point* tempPtr = &(this->convexVertices[0]);
		fillConvexPoly(objectMask,tempPtr,convexVertices.size(),cv::Scalar(255));
		QWidget * newWidget= new QWidget();
		QString objectSelected = QInputDialog::getItem(newWidget,"Object list","Select the object name ",
				this->objectslist);
		if (!objectSelected.trimmed().isEmpty()) {
			QString imgname =   cvImagesavepath +"/"+objectSelected+".png";
			cv::imwrite(imgname.toStdString(),objectMask );
			QMessageBox *Msgbox = new QMessageBox();
			Msgbox->setText("Image written to " + imgname + " # "+ QString::number(convexVertices.size()));
		}
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
	this->show();
}
void QlabelClickable::mousePressEvent ( QMouseEvent *event )
{
	this->clickedPixel= cv::Point(event->x(), event->y());
	if (!this->flag_isConvex){
		emit clicked();
	}
}

void QlabelClickable::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	if(!pixmap())
		return;

	QRect rect = pixmap()->rect();

	float scale = std::min((float)width()/rect.width(), (float)height()/rect.height());

	rect.setWidth(rect.width() * scale);
	rect.setHeight(rect.height() * scale);

	painter.drawPixmap(rect, *pixmap());
}
















