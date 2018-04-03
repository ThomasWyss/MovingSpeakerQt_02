#pragma once
#include <QObject>
#include <QThread>
#include <QString>

#include "opencv2/videoio/videoio.hpp"

#include "aruco/dictionary.hpp"

using namespace cv;
using namespace aruco;


class CameraThread : public QThread
{
	Q_OBJECT

public: 
	CameraThread(QObject *parent = nullptr);
	~CameraThread();
	void stop();
	//void setMessage(const QString &message);

protected:
	void run(void) override;
	void exit(void);


private:
	QString messageStr;
	volatile bool stopped;
	VideoCapture vid;
	Mat frame;
};
