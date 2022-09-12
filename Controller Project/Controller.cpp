#include "controller.h"

Controller::Controller()
{
	controller_buttons.resize(24);
	button_states.resize(24);
	button_codes.resize(24);

	stick_dead_zone.resize(2);
	stick_speed.resize(2);
	
	trigger_dead_zone = 50.0;
	stick_dead_zone[0] = 2500.0;
	stick_dead_zone[1] = 2500.0;
	stick_scalar = 0.0000305185;
	stick_speed[0] = 10.0;
	stick_speed[1] = 100.0;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	//combo keybinds
	multi_button_codes.resize(2);
	multi_button_codes[0].key_code_list.resize(2);
	multi_button_codes[0].key_code_list[0] = FACE_A;
	multi_button_codes[0].key_code_list[1] = FACE_B;
	multi_button_codes[0].output_key_list.resize(2);
	multi_button_codes[0].output_key_list[0] = 0x41;
	multi_button_codes[0].output_key_list[1] = 0x42;

	//single keybinds
	button_codes[LEFT_STICK_X_P] = { 3,0x44 };
	button_codes[LEFT_STICK_X_N] = { 3,0x41 };
	button_codes[LEFT_STICK_Y_P] = { 3,0x57 };
	button_codes[LEFT_STICK_Y_N] = { 3,0x53 };
	button_codes[RIGHT_STICK_X_P] = { 0,0 };
	button_codes[RIGHT_STICK_X_N] = { 0,1 };
	button_codes[RIGHT_STICK_Y_P] = { 0,2 };
	button_codes[RIGHT_STICK_Y_N] = { 0,3 };
	button_codes[LEFT_TRIGGER] = { 1,1 };
	button_codes[RIGHT_TRIGGER] = { 1,0 };
	button_codes[DPAD_UP] = { 2, 0x42 };
	button_codes[DPAD_DOWN] = { 2,0x47 };
	button_codes[DPAD_LEFT] = { 2,0x54 };
	button_codes[DPAD_RIGHT] = { -1,-1 };
	button_codes[START] = { 2,0x09 };
	button_codes[BACK] = { 2,0x48 };
	button_codes[LEFT_THUMB_DOWN] = { 3,0xA0 };
	button_codes[RIGHT_THUMB_DOWN] = { 2,0x56 };
	button_codes[LEFT_SHOULDER] = { 1,2 };
	button_codes[RIGHT_SHOULDER] = { 1,3 };
	button_codes[FACE_A] = { 2,0x20 };
	button_codes[FACE_B] = { 2,0x43 };
	button_codes[FACE_X] = { 2,0x52 };
	button_codes[FACE_Y] = { 2,0x46 };

}

int Controller::update()
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
		return(1);
	}

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
		controller_buttons[0] = temp_stick_input;
		controller_buttons[1] = 0.0;
	}
	else if (temp_stick_input <= 0.0)
	{
		controller_buttons[0] = 0.0;
		controller_buttons[1] = temp_stick_input;
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
		controller_buttons[2] = temp_stick_input;
		controller_buttons[3] = 0.0;
	}
	else if (temp_stick_input <= 0.0)
	{
		controller_buttons[2] = 0.0;
		controller_buttons[3] = temp_stick_input;
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
		controller_buttons[4] = temp_stick_input;
		controller_buttons[5] = 0.0;
	}
	else if (temp_stick_input <= 0.0)
	{
		controller_buttons[4] = 0.0;
		controller_buttons[5] = temp_stick_input;
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
		controller_buttons[6] = temp_stick_input;
		controller_buttons[7] = 0.0;
	}
	else if (temp_stick_input <= 0.0)
	{
		controller_buttons[6] = 0.0;
		controller_buttons[7] = temp_stick_input;
	}

	//read left trigger input
	controller_buttons[8] = state.Gamepad.bLeftTrigger;
	if (controller_buttons[8] < trigger_dead_zone)
	{
		controller_buttons[8] = 0.0;
	}

	//read right trigger input
	controller_buttons[9] = state.Gamepad.bRightTrigger;
	if (controller_buttons[9] < trigger_dead_zone)
	{
		controller_buttons[9] = 0.0;
	}

	//read button inputs
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) { controller_buttons[10] = 1.0; } else { controller_buttons[10] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) { controller_buttons[11] = 1.0; } else { controller_buttons[11] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) { controller_buttons[12] = 1.0; } else { controller_buttons[12] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) { controller_buttons[13] = 1.0; } else { controller_buttons[13] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START) { controller_buttons[14] = 1.0; } else { controller_buttons[14] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) { controller_buttons[15] = 1.0; } else { controller_buttons[15] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) { controller_buttons[16] = 1.0; } else { controller_buttons[16] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) { controller_buttons[17] = 1.0; } else { controller_buttons[17] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) { controller_buttons[18] = 1.0; } else { controller_buttons[18] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) { controller_buttons[19] = 1.0; } else { controller_buttons[19] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) { controller_buttons[20] = 1.0; } else { controller_buttons[20] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) { controller_buttons[21] = 1.0; } else { controller_buttons[21] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X) { controller_buttons[22] = 1.0; } else { controller_buttons[22] = 0.0; }
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y) { controller_buttons[23] = 1.0; } else { controller_buttons[23] = 0.0; }

	//check for multi button inputs
	int button_count;
	int current_count = 0;
	for (int i = 0; i < multi_button_codes.size(); i++)
	{
		button_count = multi_button_codes[i].key_code_list.size();
		current_count = 0;
		for (int h = 0; h < multi_button_codes[i].key_code_list.size(); h++)
		{
			if (controller_buttons[multi_button_codes[i].key_code_list[h]] != 0.0)
			{
				current_count++;
			}
			else
			{
				multi_button_codes[i].press_state = 0;
				break;
			}
		}
		if (button_count == current_count)
		{
			//all buttons are hit
			//zero out those buttons so they arent used for other inputs
			for (int h = 0; h < multi_button_codes[i].key_code_list.size(); h++)
			{
				controller_buttons[multi_button_codes[i].key_code_list[h]] = 0;
			}
			//do the mapped input
			//do all key press downs
			if (multi_button_codes[i].press_state == 0)
			{
				multi_button_codes[i].press_state = 1;
				for (int h = 0; h < multi_button_codes[i].output_key_list.size(); h++)
				{
					sent_inputs[h].type = INPUT_KEYBOARD;
					sent_inputs[h].ki.wVk = multi_button_codes[i].output_key_list[h];
					sent_inputs[h].ki.dwFlags = 0;
				}
				SendInput(multi_button_codes[i].output_key_list.size(), sent_inputs, sizeof(INPUT));
			}
			else if (multi_button_codes[i].press_state == 1)//do all key press ups
			{
				for (int h = 0; h < multi_button_codes[i].output_key_list.size(); h++)
				{
					sent_inputs[h].type = INPUT_KEYBOARD;
					sent_inputs[h].ki.wVk = multi_button_codes[i].output_key_list[h];
					sent_inputs[h].ki.dwFlags = KEYEVENTF_KEYUP;
				}
				SendInput(multi_button_codes[i].output_key_list.size(), sent_inputs, sizeof(INPUT));
			}
		}
	}

	//check for single button inputs
	for (int i = 0; i < 24; i++)
	{
		if (button_codes[i].key_type == 0)//mouse movement
		{
				
			if (button_codes[i].key_code == 0 || button_codes[i].key_code == 1)//x 
			{
				cursor_x += controller_buttons[i] * stick_speed[0];
				mouse_event(0x0001, controller_buttons[i] * stick_speed[1], 0, 0, 0);
			}
			else if (button_codes[i].key_code == 2 || button_codes[i].key_code == 3)//y 
			{
				cursor_y -= controller_buttons[i] * stick_speed[0];
				mouse_event(0x0001, 0, controller_buttons[i] * stick_speed[1] * -1, 0, 0);
			}
			SetCursorPos(cursor_x, cursor_y);

		}
		else if (button_codes[i].key_type == 1)
		{
			if (button_codes[i].key_code == 0)
			{
				if (controller_buttons[i] != 0.0)
				{
					sent_inputs[0].type = INPUT_MOUSE;
					sent_inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
					SendInput(1, sent_inputs, sizeof(INPUT));
				}
				else
				{
					sent_inputs[0].type = INPUT_MOUSE;
					sent_inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
					SendInput(1, sent_inputs, sizeof(INPUT));
				}
			}
			else if (button_codes[i].key_code == 1)
			{
				if (controller_buttons[i] != 0.0)
				{
					button_states[i] = 1;
					sent_inputs[0].type = INPUT_MOUSE;
					sent_inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
					SendInput(1, sent_inputs, sizeof(INPUT));
				}
				else if (controller_buttons[i] == 0.0 && button_states[i] == 1)
				{
					button_states[i] = 0;
					sent_inputs[0].type = INPUT_MOUSE;
					sent_inputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
					SendInput(1, sent_inputs, sizeof(INPUT));
				}
			}
			else if (button_codes[i].key_code == 2)
			{
				if (controller_buttons[i] != 0.0)
				{
					sent_inputs[0].type = INPUT_MOUSE;
					sent_inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
					sent_inputs[0].mi.mouseData = MK_XBUTTON1;
					SendInput(1, sent_inputs, sizeof(INPUT));
				}
				else
				{
					sent_inputs[0].type = INPUT_MOUSE;
					sent_inputs[0].mi.dwFlags = MOUSEEVENTF_XUP;
					sent_inputs[0].mi.mouseData = MK_XBUTTON1;
					SendInput(1, sent_inputs, sizeof(INPUT));
				}
			}
			else if (button_codes[i].key_code == 3)
			{
				if (controller_buttons[i] != 0.0)
				{
					sent_inputs[0].type = INPUT_MOUSE;
					sent_inputs[0].mi.dwFlags = MOUSEEVENTF_XDOWN;
					sent_inputs[0].mi.mouseData = MK_XBUTTON2;
					SendInput(1, sent_inputs, sizeof(INPUT));
				}
				else
				{
					sent_inputs[0].type = INPUT_MOUSE;
					sent_inputs[0].mi.dwFlags = MOUSEEVENTF_XUP;
					sent_inputs[0].mi.mouseData = MK_XBUTTON2;
					SendInput(1, sent_inputs, sizeof(INPUT));
				}
			}
		}
		else if (button_codes[i].key_type == 2)
		{
			if (controller_buttons[i] != 0.0 && button_states[i] == 0)
			{
				button_states[i] = 1;
				sent_inputs[0].type = INPUT_KEYBOARD;
				sent_inputs[0].ki.wVk = button_codes[i].key_code;
				sent_inputs[0].ki.dwFlags = 0;
				sent_inputs[1].type = INPUT_KEYBOARD;
				sent_inputs[1].ki.wVk = button_codes[i].key_code;
				sent_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(2, sent_inputs, sizeof(INPUT));
			}
			else if (controller_buttons[i] == 0.0 && button_states[i] == 1)
			{
				button_states[i] = 0;
			}
		}
		else if (button_codes[i].key_type == 3)
		{
			if (controller_buttons[i] != 0.0)
			{
				button_states[i] = 1;
				sent_inputs[0].type = INPUT_KEYBOARD;
				sent_inputs[0].ki.wVk = button_codes[i].key_code;
				sent_inputs[0].ki.dwFlags = 0;
				SendInput(1, sent_inputs, sizeof(INPUT));
			}
			else if (controller_buttons[i] == 0.0 && button_states[i] == 1)
			{
				button_states[i] = 0;
				sent_inputs[0].type = INPUT_KEYBOARD;
				sent_inputs[0].ki.wVk = button_codes[i].key_code;
				sent_inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, sent_inputs, sizeof(INPUT));
			}
		}
	}
	SetCursorPos(cursor_x, cursor_y);
	return(0);
}
