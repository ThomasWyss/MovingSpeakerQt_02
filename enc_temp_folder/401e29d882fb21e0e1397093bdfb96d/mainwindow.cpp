#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	initializeGui();
}
MainWindow::~MainWindow()
{

}

void MainWindow::initializeGui()
{

	this->setFixedHeight(600);
	this->setFixedWidth(900);
	auto ab = this->x();

}
