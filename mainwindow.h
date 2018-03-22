#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
private:
	Ui::MainWindowClass ui;
	void initializeGui();
	void closeEvent(QCloseEvent* event) override;
};

#endif // MAINWINDOW_H
