
#include "Application.h"

int main(int argc, char* argv[])
{
	Application app{};

	if (app.Init(1080, 720, "Backrooms"))
	{
		app.Run();
		app.Quit();
	}

	return 0;
}