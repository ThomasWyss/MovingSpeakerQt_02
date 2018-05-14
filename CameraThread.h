#pragma once
#include <QObject>
#include <QThread>
#include <QString>

#include "opencv2/videoio/videoio.hpp"

#include "aruco/dictionary.hpp"

using namespace cv;
//using namespace aruco;


class CameraThread : public QThread
{
	Q_OBJECT

public: 
	CameraThread(QObject *parent = nullptr);
	~CameraThread();
	void stop();
	int	iVid;
	//void setMessage(const QString &message);

protected:
	void process_line(const QByteArray& cs, int ilidx);
	void run(void) override;
	void exit(void);
	double camMatrix[3][3];



private:
	QString messageStr;
	volatile bool Stopped_;
	VideoCapture Vid_;
	Mat Frame_;
};
