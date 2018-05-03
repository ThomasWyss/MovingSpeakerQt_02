#include <cstdio>
#include <CameraThread.h>

#include <opencv2/aruco.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio/videoio.hpp"

#include "aruco/dictionary.hpp"
#include <qcoreapplication.h>
#include <chrono>




#define M_PI  3.14159265358979323846
#define FontSize 14
#define Left 180

using namespace std;
using namespace cv;
using namespace aruco;


cv::Mat InImage, OutImage, InDst;
cv::Mat inputImage;
vector< int > markerIds;
vector< vector<Point2f>> markerCorners, rejectedCandidates;
vector< vector<Point2f> >::iterator itMarker;



CameraThread::CameraThread(QObject* parent) : Stopped_(false)
{
	//vid.open("http://<Thomas:9878a6545>@<192.168.178.24:88>"); 	

		 //if (~Vid_.isOpened()) Vid_.open(0);
}

CameraThread::~CameraThread()
{
	Stopped_ = true;
	if (Vid_.isOpened()) Vid_.release();
}

void CameraThread::stop()
{
	if (Vid_.isOpened()) Vid_.release();
}

void CameraThread::run(void)
{
	Vid_.open(iVid);
	Vid_.set(CAP_PROP_FRAME_WIDTH, 1280.0);
	Vid_.set(CAP_PROP_FRAME_HEIGHT, 720.0);

	if (!Vid_.isOpened()) return;
	Stopped_ = false;
	Point pAb = Point(Left, 200);
	Point pCenter = Point(640, 370);
	char cpWindowName[50], cpPhyData[50], cpWinData[128], cpWinData_2[50];
	sprintf(cpWindowName, "Camera_%d", iVid);

	const cv::Ptr<cv::aruco::Dictionary> dictionary = getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME::DICT_ARUCO_ORIGINAL);
	cv::aruco::drawMarker(dictionary, 25, 200, OutImage, 1);
	auto& parameters = DetectorParameters::create();
	String cerr;
	const cv::QtFont fontA = cv::fontQt("Times",FontSize);

	const int iHeight= Vid_.get(CAP_PROP_FRAME_HEIGHT);
	const int iWidth = Vid_.get(CAP_PROP_FRAME_WIDTH);
	
	Vid_.read(Frame_);
	cv::imshow(cpWindowName, Frame_);

	auto chronoNow = std::chrono::high_resolution_clock::now();
	auto chronoNowLoop = std::chrono::high_resolution_clock::now();
	auto chronoOld = chronoNow;
	chrono::duration<double> chronotimeDiff, chronoImviewDiff;
	auto chronoImshow = std::chrono::high_resolution_clock::now();

	double dSumX = 0;
	double dSumY = 0;	
	Point pXy,  pPhy, pXySum;
	double dPhy, dDiag, dFps, dTime;
	int iCounter = 0;
	std::chrono::duration<double, std::milli> fp_ms, fp_ms_1;

	while (Vid_.read(Frame_)) {		
		chronoOld = chronoNow;
		chronoNow = std::chrono::high_resolution_clock::now();
		chronotimeDiff = chronoNow - chronoOld;
		dFps = dFps + chronotimeDiff.count();
		//double fp_ms10 = fp_ms10 + double(fp_ms);
		if (iCounter == 10)
		{
			dTime = dFps / 10;
			dFps = 0;
			
			//fp_ms10 = 0;
			iCounter = 0;
		}
		iCounter++;
		sprintf_s(cpWinData, "%d %d     fps: %05.1f", iHeight, iWidth, 1.0 / dTime);

		detectMarkers(Frame_, dictionary, markerCorners, markerIds, parameters, rejectedCandidates);
		//drawDetectedMarkers(Frame_, markerCorners, markerIds, Scalar(0, 255, 0));
		
		if (!markerCorners.empty())
		{
			dSumX = 0;
			dSumY = 0;
			itMarker = markerCorners.begin();
			auto itAa = *itMarker;
				for (auto ii = 0; ii < 4; ii++)
				{
					dSumX += itAa[ii].x;
					dSumY += itAa[ii].y;
				}
			pXy = Point(dSumX / 4, dSumY / 4);
			pPhy = Point(pXy.x - pCenter.x, pXy.y - pCenter.y);
			dPhy = 180*atan2f(pPhy.x,pPhy.y)/ M_PI;
			dDiag=sqrt((itAa[0].x - itAa[2].x)*(itAa[0].x - itAa[2].x) + (itAa[0].y - itAa[2].y)*(itAa[0].y - itAa[2].y));
			//dDiag = sqrt(pPhy.x*pPhy.x + pPhy.y*pPhy.y);
		}

		sprintf_s(cpPhyData,"X   phy: %3.1f  diag:%3.1f", dPhy, dDiag);
		cv::addText(Frame_, cpPhyData, pXy, fontA);
		cv::addText(Frame_, cpPhyData, Point(Left,220), fontA);
		cv::addText(Frame_, cpWinData, pAb, fontA);
		//cv::addText(Frame_, cpWinData_2, pAb, fontA);
		cv::addText(Frame_, "+", pCenter, fontA);
		
		if (Stopped_)  break;
		chronoNowLoop = std::chrono::high_resolution_clock::now();
		fp_ms = chronoNowLoop - chronoNow;
		std::chrono::duration<double, std::milli> fp_ms_1 = chronoNow - chronoOld;
		sprintf_s(cpWinData, "intern: %05.1f  full: %05.1f  diff: %05.1f  ISdiff: %05.1f", 
						      fp_ms, fp_ms_1, fp_ms_1-fp_ms, 1000*chronoImviewDiff.count());
		cv::addText(Frame_, cpWinData, Point(180, 240), fontA);

		QCoreApplication::processEvents();
		cv::imshow(cpWindowName, Frame_);
		chronoImshow = std::chrono::high_resolution_clock::now();
		chronoImviewDiff = chronoImshow - chronoNowLoop;
	}

	if (Vid_.isOpened()) Vid_.release();
	cv::destroyWindow(cpWindowName);
}

void CameraThread::exit()
{
	if (Vid_.isOpened()) Vid_.release();
}
