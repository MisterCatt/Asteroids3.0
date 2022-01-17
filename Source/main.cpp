#include "Screen.h"
#include "Game.h"

int screenWidth = 1000;
int screenHeight = 1000;

int main(int argc, char** argv)
{
	srand(0);

	Screen screen(screenWidth, screenHeight, "Galba");

	Game* Asteroids = new Game(screen);

 	while (screen.IsOpen())
	{
		screen.Clear();

		Asteroids->run();

		screen.Display();
	}
	return 0;
}