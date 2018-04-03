#include "mainwindow.h"


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
	this->setFixedHeight(600);
	this->setFixedWidth(900);
}

void MainWindow::startThreads()
{
	CamThread.start();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	CamThread.stop();
}
