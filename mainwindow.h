#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QtWidgets/QMainWindow>
#include "QtMainBar.h"
#include "QtStatusBar.h"
#include "QtModule.h"
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
	CameraThread CamThread_[2];


	QWidget *					m_centralWidget;
	QVBoxLayout *				m_verticalLayout;
	QWidget *					m_moduleWidget;
	QVBoxLayout *				m_moduleVerticalLayout;
	QtMainBar *					m_mainBar;
	QtStatusBar *				m_statusBar;
	QtModule * 					m_currentModule;
	std::vector<QtModule*> 		m_moduleList;



};

#endif // MAINWINDOW_H
