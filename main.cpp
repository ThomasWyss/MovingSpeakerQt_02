#include "mainwindow.h"
#include <QtWidgets/QApplication>
#include <MovingSpeakerBootstrapper.h>

int main(int argc, char *argv[])
{
	MovingSpeakerBootstrapper movingSpeakerBootstrapper(argc, argv);
	return movingSpeakerBootstrapper.run();
}
