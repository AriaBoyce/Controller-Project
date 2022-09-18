#include "controller.h"
/*
Aria Boyce
Controller Project
last Updated: 9/16/2022
Used to emulate keyboard mouse input in Escape From Tarkov using an Xbox Controller
Is fully functioning in this state for my needs. Not even command prompt ready quite yet.
Will maybe eventually add a GUI to this for easier use for myself and perhaps others
V 0.1.1
Increased Tick Rate
Fixed bug where it would constantly spam up the part of some mouse buttons.
Fixed bug where multi key functions would not trigger consistently.
*/
int main()
{
	Controller Controller;
	while (1)
	{
		Controller.update();
		Sleep(10);
	}
}