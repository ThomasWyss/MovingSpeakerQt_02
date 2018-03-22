#pragma once
#include <QObject>
#include <QMainWindow>
#include <QThread>
#include <QString>


class CameraThread : public QThread
{
	Q_OBJECT

public: 
	CameraThread(QObject *parent = nullptr);
	~CameraThread();

	//void setMessage(const QString &message);
	void stop(void);

protected:
	void run(void);

private:
	QString messageStr;
	volatile bool stopped;
};
