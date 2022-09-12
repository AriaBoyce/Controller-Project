#include <Windows.h>
#include <iostream>
#include <xinput.h>
#include <cmath>
#include <winuser.h>
#include <vector>
#pragma comment(lib, "XInput.lib") 
#include "defines.h"

using namespace std;

class Controller
{
public:
	Controller();
	int update();
private:
	vector<float> controller_buttons;
	vector<float> stick_dead_zone;
	float trigger_dead_zone;
	vector<float> stick_speed;
	float stick_scalar;
	vector<bool> button_states;
	struct key_code
	{
		int key_type;
		int key_code;
	};
	vector<key_code> button_codes;
	
	struct multi_button
	{
		vector<int> key_code_list;
		vector<int> output_key_list;
		bool press_state = 0;
	};
	vector<multi_button> multi_button_codes;

	int cursor_x;
	int cursor_y;

	INPUT sent_inputs[10];

	DWORD dwResult;
	XINPUT_STATE state;
};