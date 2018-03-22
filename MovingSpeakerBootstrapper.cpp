#include "MovingSpeakerBootstrapper.h"
#include "MainWindow.h"


MovingSpeakerBootstrapper::MovingSpeakerBootstrapper(int& argc, char** argv)
	: QApplication(argc, argv)
{
}

int MovingSpeakerBootstrapper::run()
{
	//

	MainWindow mainWindow;

	mainWindow.show();

	//

	return exec();
}
