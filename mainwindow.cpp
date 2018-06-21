#include "mainwindow.h"
#include <QLabel>
#include <QWidget>
#include <QStatusbar>

#include <QVBoxLayout>
#include <QPushButton>
#include <QVideoWidget>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio/videoio.hpp"
#include <QTextStream>

#define cam 0
CameraThread CamThread_[2];

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

	// Create central widget
	m_centralWidget = new QWidget(this);
	this->setCentralWidget(m_centralWidget);

	// Create layout
	m_verticalLayout = new QVBoxLayout(m_centralWidget);

	// Define size policy
	//QSizePolicy sizePolicyMainWindow(QSizePolicy::Fixed, QSizePolicy::Fixed);
	//this->setSizePolicy(sizePolicyMainWindow);

	// Create main bar
	QPushButton *button1 = new QPushButton("One");
	QPushButton *button2 = new QPushButton("Two");
	QPushButton *button3 = new QPushButton("Three");
	QPushButton *button4 = new QPushButton("Four");
	QPushButton *button5 = new QPushButton("Five");

	m_verticalLayout->addWidget(button1);
	m_verticalLayout->addWidget(button2);
	m_verticalLayout->addWidget(button3);
	m_verticalLayout->addWidget(button4);
	m_verticalLayout->addWidget(button5);

	m_verticalLayout->setDirection(QBoxLayout::LeftToRight);

	m_centralWidget->setLayout(m_verticalLayout);



	//m_mainBar = new QtMainBar(this);
	//m_verticalLayout->addWidget(m_mainBar);
	//connect(m_mainBar, SIGNAL(moduleSelectedSIG(QToolButton*, int&)), this, SLOT(moduleSelectedSlot(QToolButton*, int&)));
	//connect(m_mainBar, SIGNAL(exitClickedSIG()), this, SLOT(exitSlot()));

	// Create module widget place
	m_moduleWidget = new QWidget(m_centralWidget);
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(1);
	sizePolicy.setVerticalStretch(1);
	sizePolicy.setHeightForWidth(m_moduleWidget->sizePolicy().hasHeightForWidth());
	m_moduleWidget->setSizePolicy(sizePolicy);
	m_verticalLayout->addWidget(m_moduleWidget);
	m_moduleVerticalLayout = new QVBoxLayout(m_moduleWidget);
	m_moduleVerticalLayout->setMargin(0);
	m_moduleVerticalLayout->setSpacing(0);


	// Connect signals and slots for status bar
	//connect(m_statusBar, SIGNAL(startProgressEventSig()), m_statusBar, SLOT(progressBarActive()));
	//connect(m_statusBar, SIGNAL(endProgressEventSig()), m_statusBar, SLOT(progressBarInactive()));
	this->setWindowState(Qt::WindowMaximized | Qt::WindowActive);

}

void MainWindow::startThreads()
{
	CamThread_[0].iVid = cam;
	CamThread_[0].start();
	CamThread_[1].iVid = 1;
	CamThread_[1].start();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	CamThread_[0].iVid = cam;
	CamThread_[0].stop();
	CamThread_[1].iVid = 1;
	CamThread_[1].stop();
}
