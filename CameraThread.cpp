#include <cstdio>
#include <ctime>
#include <CameraThread.h>

#include <opencv2/aruco.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio/videoio.hpp"

#include "aruco/dictionary.hpp"
#include <qcoreapplication.h>
#include <chrono>


using namespace std;
using namespace cv;
using namespace aruco;


cv::Mat InImage, OutImage, InDst;
cv::Mat inputImage;
vector< int > markerIds;
vector< vector<Point2f> > markerCorners, rejectedCandidates;



CameraThread::CameraThread(QObject* parent): stopped(false)
{
	vid.open(0);
}

CameraThread::~CameraThread()
{
	stopped = true;
	if (vid.isOpened()) vid.release();
}

void CameraThread::stop()
{
	if (vid.isOpened()) vid.release();
}

void CameraThread::run(void)
{
	if (!vid.isOpened()) return;
	stopped = false;
	Point pAb = Point(100, 100);

	const cv::Ptr<cv::aruco::Dictionary> dictionary = getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME::DICT_ARUCO_ORIGINAL);
	cv::aruco::drawMarker(dictionary, 25, 200, OutImage, 1);
	auto& parameters = DetectorParameters::create();
	String cerr;
	const cv::QtFont fontA = cv::fontQt("Times");

	const int iHeight= vid.get(CAP_PROP_FRAME_HEIGHT);
	const int iWidth = vid.get(CAP_PROP_FRAME_WIDTH);
	char cpWinData[50];
	
	vid.read(frame);
	imshow("WebCam", frame);

	auto chronoNow = std::chrono::high_resolution_clock::now();

	while (vid.read(frame)) {
		//vid.read(frame);
		auto chronoOld = chronoNow;
		chronoNow = std::chrono::high_resolution_clock::now();
		chrono::duration<double> chronotimeDiff = chronoNow - chronoOld;
		sprintf_s(cpWinData, "%d %d  fps:%3.1f", iHeight, iWidth, 1.0/chronotimeDiff.count());

		detectMarkers(frame, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
		drawDetectedMarkers(frame, markerCorners, markerIds, Scalar(0, 255, 0));
		addText(frame, cpWinData, pAb, fontA);
		if (stopped)  break;
		imshow("WebCam", frame);
		QCoreApplication::processEvents();
		//if (waitKey(20) >= 0)  break;
	}
	if (vid.isOpened()) vid.release();
	destroyWindow("WebCam");
}

void CameraThread::exit()
{
	if (vid.isOpened()) vid.release();
}
