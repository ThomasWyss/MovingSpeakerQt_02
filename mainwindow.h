#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "CameraThread.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private:
	Ui::MainWindowClass ui;
	void initializeGui();
	void startThreads();
	void closeEvent(QCloseEvent* event) override;
	CameraThread CamThread;
};

#endif // MAINWINDOW_H
