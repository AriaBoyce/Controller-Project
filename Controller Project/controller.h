#pragma once
#include <Windows.h>
#include <iostream>
#include <xinput.h>
#include <cmath>
#include <winuser.h>
#include <vector>
#pragma comment(lib, "XInput.lib") 
using namespace std;
#define LEFT_STICK_X_P		0
#define LEFT_STICK_X_N		1
#define LEFT_STICK_Y_P		2
#define LEFT_STICK_Y_N		3

#define RIGHT_STICK_X_P		4
#define RIGHT_STICK_X_N		5
#define RIGHT_STICK_Y_P		6
#define RIGHT_STICK_Y_N		7

#define LEFT_TRIGGER		8
#define RIGHT_TRIGGER		9

#define DPAD_UP				10
#define DPAD_DOWN			11
#define DPAD_LEFT			12
#define DPAD_RIGHT			13
#define START				14
#define BACK				15
#define LEFT_THUMB_DOWN		16
#define RIGHT_THUMB_DOWN	17
#define LEFT_SHOULDER		18
#define RIGHT_SHOULDER		19
#define FACE_A				20
#define	FACE_B				21
#define FACE_X				22
#define	FACE_Y				23


class Controller
{
public:
	Controller();
	void Update();
	void Convert_Key_Codes();
	~Controller();
private:
	vector<float> controller_state_current;
	vector<float> controller_state_pressed;
	vector<float> controller_state_released;
	vector<float> controller_state_previous;
	float trigger_dead_zone;
	vector<float> stick_speed;
	float stick_scalar;
	vector<float> stick_dead_zone;
	int cursor_x;
	int cursor_y;
	DWORD dwResult;
	XINPUT_STATE state;
	vector<string> english_codes;

	vector<vector<int>> input_code;
	INPUT sent_inputs[15];
	vector<bool> button_states;
};