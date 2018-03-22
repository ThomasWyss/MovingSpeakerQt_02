#pragma once
#include <QApplication>

class MovingSpeakerBootstrapper : public QApplication
{

	public:
	MovingSpeakerBootstrapper(int& argc, char** argv);

	int run();

};
