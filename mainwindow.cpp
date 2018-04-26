#include "mainwindow.h"
#include <QLabel>
#include <QVideoWidget>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio/videoio.hpp"

#define cam 0

MainWindow::MainWindow(QWidget *parent) 
	: QMainWindow(parent)
{
	initializeGui();
	startThreads();
}
MainWindow::~MainWindow()
= default;

void MainWindow::initializeGui()
{
	//VideoCapture Vid_;
	//Vid_.open(0);
	//cv::Mat videoFrame;
	//Vid_.read(videoFrame);
	//Vid_.release();
	//
	//QVideoWidget *VidWidget = new QVideoWidget;
	//QPixmap pictureFrame = videoFrame;
	
	//VidWidget->show();

	auto *label = new QLabel(this);
	label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	//cv::imshow("label", videoFrame);
	//label->setPixmap(videoFrame);
	this->setFixedHeight(600);
	this->setFixedWidth(900);
}

void MainWindow::startThreads()
{
	CamThread_[0].iVid = cam;
	CamThread_[0].start();
	//CamThread_[1].iVid = 1;
	//CamThread_[1].start();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	CamThread_[0].iVid = cam;
	CamThread_[0].stop();
	//CamThread_[0].iVid = 1;
	//CamThread_[1].stop();
}
