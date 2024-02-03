#include "Controller.h"

Controller::Controller()
{
	controller_state_current.resize(24);
	controller_state_pressed.resize(24);
	controller_state_previous.resize(24);
	controller_state_released.resize(24);

	stick_dead_zone.resize(2);
	stick_speed.resize(2);

	trigger_dead_zone = 50.0;
	stick_dead_zone[0] = 5000.0;
	stick_dead_zone[1] = 5000.0;
	stick_scalar = 0.0000305185;
	stick_speed[0] = 15.0;
	stick_speed[1] = 50.0;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	english_codes.resize(11);
	english_codes[0] = "LEFT_STICK_X_P = D";
	english_codes[1] = "LEFT_STICK_X_N = A";
	english_codes[2] = "LEFT_STICK_Y_P = W";
	english_codes[3] = "LEFT_STICK_Y_N = S";

	english_codes[4] = "RIGHT_STICK_X_P = MOUSE_X_P";
	english_codes[5] = "RIGHT_STICK_X_N = MOUSE_X_N";
	english_codes[6] = "RIGHT_STICK_Y_P = MOUSE_Y_P";
	english_codes[7] = "RIGHT_STICK_Y_N = MOUSE_Y_N";

	english_codes[8] = "LEFT_TRIGGER = RIGHT_CLICK";
	english_codes[9] = "RIGHT_TRIGGER = LEFT_CLICK";

	english_codes[10] = "FACE_X = R";
	button_states.resize(11);
	Convert_Key_Codes();
}

void Controller::Convert_Key_Codes()
{
	vector<string> temp_list;
	for (int i = 0; i < english_codes.size(); i++)
	{
		temp_list.resize(0);
		while (true)
		{
			temp_list.push_back(english_codes[i].substr(0, english_codes[i].find(" ")));
			english_codes[i].erase(0,english_codes[i].find(" ")+1);
			if (temp_list[temp_list.size() - 1] == "=")
			{
				temp_list.pop_back();
				temp_list.push_back(english_codes[i].substr(0, english_codes[i].find(" ")));
				break;
			}
		}

		vector<int> temp_code;
		//get input codes
		for (int i = 0; i < temp_list.size() - 1; i++)
		{
			if (temp_list[i] == "LEFT_STICK_X_P")
			{
				temp_code.push_back(0);
			}
			else if (temp_list[i] == "LEFT_STICK_X_N")
			{
				temp_code.push_back(1);
			}
			else if (temp_list[i] == "LEFT_STICK_Y_P")
			{
				temp_code.push_back(2);
			}
			else if (temp_list[i] == "LEFT_STICK_Y_N")
			{
				temp_code.push_back(3);
			}
			else if (temp_list[i] == "RIGHT_STICK_X_P")
			{
				temp_code.push_back(4);
			}
			else if (temp_list[i] == "RIGHT_STICK_X_N")
			{
				temp_code.push_back(5);
			}
			else if (temp_list[i] == "RIGHT_STICK_Y_P")
			{
				temp_code.push_back(6);
			}
			else if (temp_list[i] == "RIGHT_STICK_Y_N")
			{
				temp_code.push_back(7);
			}
			else if (temp_list[i] == "LEFT_TRIGGER")
			{
				temp_code.push_back(8);
			}
			else if (temp_list[i] == "RIGHT_TRIGGER")
			{
				temp_code.push_back(9);
			}
			else if (temp_list[i] == "DPAD_UP")
			{
				temp_code.push_back(10);
			}
			else if (temp_list[i] == "DPAD_DOWN")
			{
				temp_code.push_back(11);
			}
			else if (temp_list[i] == "DPAD_LEFT")
			{
				temp_code.push_back(12);
			}
			else if (temp_list[i] == "DPAD_RIGHT")
			{
				temp_code.push_back(13);
			}
			else if (temp_list[i] == "START")
			{
				temp_code.push_back(14);
			}
			else if (temp_list[i] == "BACK")
			{
				temp_code.push_back(15);
			}
			else if (temp_list[i] == "LEFT_THUMB_DOWN")
			{
				temp_code.push_back(16);
			}
			else if (temp_list[i] == "RIGHT_THUMB_DOWN")
			{
				temp_code.push_back(17);
			}
			else if (temp_list[i] == "LEFT_SHOULDER")
			{
				temp_code.push_back(18);
			}
			else if (temp_list[i] == "RIGHT_SHOULDER")
			{
				temp_code.push_back(19);
			}
			else if (temp_list[i] == "FACE_A")
			{
				temp_code.push_back(20);
			}
			else if (temp_list[i] == "FACE_B")
			{
				temp_code.push_back(21);
			}
			else if (temp_list[i] == "FACE_X")
			{
				temp_code.push_back(22);
			}
			else if (temp_list[i] == "FACE_Y")
			{
				temp_code.push_back(23);
			}
		}

		//get output code
		if (temp_list[temp_list.size() - 1] == "LEFT_CLICK")
		{
			temp_code.push_back(0x01);
		}
		else if (temp_list[temp_list.size() - 1] == "RIGHT_CLICK")
		{
			temp_code.push_back(0x02);
		}
		else if (temp_list[temp_list.size() - 1] == "BACKSPACE")
		{
			temp_code.push_back(0x08);
		}
		else if (temp_list[temp_list.size() - 1] == "TAB")
		{
			temp_code.push_back(0x09);
		}
		else if (temp_list[temp_list.size() - 1] == "ENTER")
		{
			temp_code.push_back(0x0D);
		}
		else if (temp_list[temp_list.size() - 1] == "SHIFT")
		{
			temp_code.push_back(0x10);
		}
		else if (temp_list[temp_list.size() - 1] == "CTRL")
		{
			temp_code.push_back(0x11);
		}
		else if (temp_list[temp_list.size() - 1] == "ALT")
		{
			temp_code.push_back(0x12);
		}
		else if (temp_list[temp_list.size() - 1] == "CAPS LOCK")
		{
			temp_code.push_back(0x14);
		}
		else if (temp_list[temp_list.size() - 1] == "ESC")
		{
			temp_code.push_back(0x1B);
		}
		else if (temp_list[temp_list.size() - 1] == "SPACE")
		{
			temp_code.push_back(0x20);
		}
		else if (temp_list[temp_list.size() - 1] == "A")
		{
			temp_code.push_back(0x41);
		}
		else if (temp_list[temp_list.size() - 1] == "B")
		{
			temp_code.push_back(0x42);
		}
		else if (temp_list[temp_list.size() - 1] == "C")
		{
			temp_code.push_back(0x43);
		}
		else if (temp_list[temp_list.size() - 1] == "D")
		{
			temp_code.push_back(0x44);
		}
		else if (temp_list[temp_list.size() - 1] == "E")
		{
			temp_code.push_back(0x45);
		}
		else if (temp_list[temp_list.size() - 1] == "F")
		{
			temp_code.push_back(0x46);
		}
		else if (temp_list[temp_list.size() - 1] == "G")
		{
			temp_code.push_back(0x47);
		}
		else if (temp_list[temp_list.size() - 1] == "H")
		{
			temp_code.push_back(0x48);
		}
		else if (temp_list[temp_list.size() - 1] == "I")
		{
			temp_code.push_back(0x49);
		}
		else if (temp_list[temp_list.size() - 1] == "J")
		{
			temp_code.push_back(0x4A);
		}
		else if (temp_list[temp_list.size() - 1] == "K")
		{
			temp_code.push_back(0x4B);
		}
		else if (temp_list[temp_list.size() - 1] == "L")
		{
			temp_code.push_back(0x4C);
		}
		else if (temp_list[temp_list.size() - 1] == "M")
		{
			temp_code.push_back(0x4D);
		}
		else if (temp_list[temp_list.size() - 1] == "N")
		{
			temp_code.push_back(0x4E);
		}
		else if (temp_list[temp_list.size() - 1] == "O")
		{
			temp_code.push_back(0x4F);
		}
		else if (temp_list[temp_list.size() - 1] == "P")
		{
			temp_code.push_back(0x50);
		}
		else if (temp_list[temp_list.size() - 1] == "Q")
		{
			temp_code.push_back(0x51);
		}
		else if (temp_list[temp_list.size() - 1] == "R")
		{
			temp_code.push_back(0x52);
		}
		else if (temp_list[temp_list.size() - 1] == "S")
		{
			temp_code.push_back(0x53);
		}
		else if (temp_list[temp_list.size() - 1] == "T")
		{
			temp_code.push_back(0x54);
		}
		else if (temp_list[temp_list.size() - 1] == "U")
		{
			temp_code.push_back(0x55);
		}
		else if (temp_list[temp_list.size() - 1] == "V")
		{
			temp_code.push_back(0x56);
		}
		else if (temp_list[temp_list.size() - 1] == "W")
		{
			temp_code.push_back(0x57);
		}
		else if (temp_list[temp_list.size() - 1] == "X")
		{
			temp_code.push_back(0x58);
		}
		else if (temp_list[temp_list.size() - 1] == "Y")
		{
			temp_code.push_back(0x59);
		}
		else if (temp_list[temp_list.size() - 1] == "Z")
		{
			temp_code.push_back(0x5A);
		}
		else if (temp_list[temp_list.size() - 1] == "MOUSE_X_P")
		{
			temp_code.push_back(9000);
		}
		else if (temp_list[temp_list.size() - 1] == "MOUSE_X_N")
		{
			temp_code.push_back(9001);
		}
		else if (temp_list[temp_list.size() - 1] == "MOUSE_Y_P")
		{
			temp_code.push_back(9002);
		}
		else if (temp_list[temp_list.size() - 1] == "MOUSE_Y_N")
		{
			temp_code.push_back(9003);
		}

		input_code.push_back(temp_code);
	}


}	

void Controller::Update()
{

	POINT p;
	GetCursorPos(&p);
	cursor_x = p.x;
	cursor_y = p.y;

	ZeroMemory(&state, sizeof(XINPUT_STATE));
	dwResult = XInputGetState(0, &state);
	if (dwResult != ERROR_SUCCESS)
	{
		//update controller
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		dwResult = XInputGetState(0, &state);
		return;
	}

	//get previous controller state
	for (int i = 0; i < controller_state_current.size(); i++)
	{
		controller_state_previous[i] = controller_state_current[i];
	}

	//update controller state
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) { controller_state_current[10] = 1.0; } else { controller_state_current[10] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) { controller_state_current[11] = 1.0; } else { controller_state_current[11] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) { controller_state_current[12] = 1.0; } else { controller_state_current[12] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) { controller_state_current[13] = 1.0; } else { controller_state_current[13] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) { controller_state_current[14] = 1.0; } else { controller_state_current[14] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) { controller_state_current[15] = 1.0; } else { controller_state_current[15] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) { controller_state_current[16] = 1.0; } else { controller_state_current[16] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) { controller_state_current[17] = 1.0; } else { controller_state_current[17] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) { controller_state_current[18] = 1.0; } else { controller_state_current[18] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) { controller_state_current[19] = 1.0; } else { controller_state_current[19] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) { controller_state_current[20] = 1.0; } else { controller_state_current[20] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) { controller_state_current[21] = 1.0; } else { controller_state_current[21] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) { controller_state_current[22] = 1.0; } else { controller_state_current[22] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) { controller_state_current[23] = 1.0; } else { controller_state_current[23] = 0.0; }

	//use previous and current to check for pressed and released
	for (int i = 10; i < controller_state_current.size(); i++)
	{
		if (controller_state_previous[i] == 0.0 && controller_state_current[i] == 1.0)
		{
			controller_state_pressed[i] = 1.0;
		}
		else
		{
			controller_state_pressed[i] = 0.0;
		}
		if (controller_state_previous[i] == 1.0 && controller_state_current[i] == 0.0)
		{
			controller_state_released[i] = 1.0;
		}
		else
		{
			controller_state_released[i] = 0.0;
		}
	}

	//get stick info
	//get controller info
	float temp_stick_input = 0.0;

	//get left stick info

	temp_stick_input = state.Gamepad.sThumbLX;
	//use dead zone
	if (abs(temp_stick_input) < stick_dead_zone[0])
	{
		temp_stick_input = 0.0;
	}
	temp_stick_input *= stick_scalar;
	if (temp_stick_input > 0.0)
	{
		controller_state_current[0] = temp_stick_input;
		controller_state_current[1] = 0.0;
	}
	else if (temp_stick_input <= 0.0)
	{
		controller_state_current[0] = 0.0;
		controller_state_current[1] = temp_stick_input;
	}


	//get left stick y info
	temp_stick_input = state.Gamepad.sThumbLY;
	if (abs(temp_stick_input) < stick_dead_zone[0])
	{
		temp_stick_input = 0.0;
	}
	temp_stick_input *= stick_scalar;

	if (temp_stick_input > 0.0)
	{
		controller_state_current[2] = temp_stick_input;
		controller_state_current[3] = 0.0;
	}
	else if (temp_stick_input <= 0.0)
	{
		controller_state_current[2] = 0.0;
		controller_state_current[3] = temp_stick_input;
	}

	//read right stick X info
	temp_stick_input = 0.0;
	temp_stick_input = state.Gamepad.sThumbRX;
	if (abs(temp_stick_input) < stick_dead_zone[1])
	{
		temp_stick_input = 0.0;
	}
	temp_stick_input *= stick_scalar;
	if (temp_stick_input > 0.0)
	{
		controller_state_current[4] = temp_stick_input;
		controller_state_current[5] = 0.0;
	}
	else if (temp_stick_input <= 0.0)
	{
		controller_state_current[4] = 0.0;
		controller_state_current[5] = temp_stick_input;
	}

	//get right stick y info
	temp_stick_input = state.Gamepad.sThumbRY;
	if (abs(temp_stick_input) < stick_dead_zone[1])
	{
		temp_stick_input = 0.0;
	}
	temp_stick_input *= stick_scalar;

	if (temp_stick_input > 0.0)
	{
		controller_state_current[6] = temp_stick_input;
		controller_state_current[7] = 0.0;
	}
	else if (temp_stick_input <= 0.0)
	{
		controller_state_current[6] = 0.0;
		controller_state_current[7] = temp_stick_input;
	}

	//read left trigger input
	controller_state_current[8] = state.Gamepad.bLeftTrigger;
	if (controller_state_current[8] < trigger_dead_zone)
	{
		controller_state_current[8] = 0.0;
	}

	//read right trigger input
	controller_state_current[9] = state.Gamepad.bRightTrigger;
	if (controller_state_current[9] < trigger_dead_zone)
	{
		controller_state_current[9] = 0.0;
	}

	int key_check = 0;
	//check for full keycode list
	for (int i = 0; i < input_code.size(); i++)
	{
		int count = 0;
		for (int h = 0; h < input_code[i].size() - 1; h++)
		{
			if (controller_state_current[input_code[i][h]] != 0.0)
			{
				count++;
			}
		}
		if (count == input_code[i].size() - 1 && button_states[i] == false)//press down
		{
			//keycode is met
			//do output
			if (input_code[i][input_code[i].size() - 1] == 0x01)
			{
				button_states[i] = true;
				sent_inputs[key_check].type = INPUT_MOUSE;
				sent_inputs[key_check].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
				key_check++;
			}
			else if (input_code[i][input_code[i].size() - 1] == 0x02)
			{
				button_states[i] = true;
				sent_inputs[key_check].type = INPUT_MOUSE;
				sent_inputs[key_check].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
				key_check++;
			}
			else if (input_code[i][input_code[i].size() - 1] == 9000)
			{
				cursor_x += controller_state_current[4] * stick_speed[0];
				mouse_event(0x0001, controller_state_current[4] * stick_speed[1], 0, 0, 0);
			}
			else if (input_code[i][input_code[i].size() - 1] == 9001)
			{
				cursor_x += controller_state_current[5] * stick_speed[0];
				mouse_event(0x0001, controller_state_current[5] * stick_speed[1], 0, 0, 0);
			}
			else if (input_code[i][input_code[i].size() - 1] == 9002)
			{
				cursor_y -= controller_state_current[6] * stick_speed[0];
				mouse_event(0x0001, 0, controller_state_current[6] * stick_speed[1] * -1, 0, 0);
			}
			else if (input_code[i][input_code[i].size() - 1] == 9003)
			{
				cursor_y -= controller_state_current[7] * stick_speed[0];
				mouse_event(0x0001, 0, controller_state_current[7] * stick_speed[1] * -1, 0, 0);
			}
			else
			{
				button_states[i] = true;
				sent_inputs[key_check].type = INPUT_KEYBOARD;
				sent_inputs[key_check].ki.wVk = input_code[i][input_code[i].size() - 1];
				sent_inputs[key_check].ki.dwFlags = 0;
				key_check++;
			}
		}
		else if(count != input_code[i].size() - 1 && button_states[i] == true)//press up
		{
			if (input_code[i][input_code[i].size() - 1] == 0x01)
			{
				button_states[i] = false;
				sent_inputs[key_check].type = INPUT_MOUSE;
				sent_inputs[key_check].mi.dwFlags = MOUSEEVENTF_LEFTUP;
				key_check++;
			}
			else if (input_code[i][input_code[i].size() - 1] == 0x02)
			{
				button_states[i] = false;
				sent_inputs[key_check].type = INPUT_MOUSE;
				sent_inputs[key_check].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
				key_check++;
			}
			else if (input_code[i][input_code[i].size() - 1] == 9000)
			{

			}
			else if (input_code[i][input_code[i].size() - 1] == 9001)
			{

			}
			else if (input_code[i][input_code[i].size() - 1] == 9002)
			{

			}
			else if (input_code[i][input_code[i].size() - 1] == 9003)
			{

			}
			else
			{
				button_states[i] = false;
				sent_inputs[key_check].type = INPUT_KEYBOARD;
				sent_inputs[key_check].ki.wVk = input_code[i][input_code[i].size() - 1];
				sent_inputs[key_check].ki.dwFlags = KEYEVENTF_KEYUP;
				key_check++;
			}
		}
	}
	SendInput(key_check, sent_inputs, sizeof(INPUT));
	SetCursorPos(cursor_x, cursor_y);
}

Controller::~Controller()
{

}