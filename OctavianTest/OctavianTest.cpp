#include "Application.h"

int main(int argc, char* args[])
{
	Application application;

	if (application.init())
		application.run();

	return 0;
}