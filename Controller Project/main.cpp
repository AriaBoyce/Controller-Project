#include "controller.h"

int main()
{
	Controller Controller;
	while (1)
	{
		Controller.update();
		Sleep(25);
	}
}