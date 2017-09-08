#ifndef COMMONCONTROL_H
#define COMMONCONTROL_H

#include<dinput.h>
#include <XInput.h>

enum KEYSTATE {
	KEY_PUSH,
	KEY_RELEASE,
	KEY_ON,
	KEY_OFF
};

enum KEYKIND
{
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_SPACE,
	KEY_ESC,
	KEYMAX
};

enum PADSTATE
{
	PAD_OFF,			//!< �����ꑱ���Ă���.
	PAD_ON,			//!< �����ꑱ���Ă���.
	PAD_RELEASE,	//!< �����ꂽ��.
	PAD_PUSH		//!< �����ꂽ��.
	
};

enum XINPUT_ID
{
	GAMEPAD_DANALOG_UP,			//!< �A�i���O�\���L�[��.
	GAMEPAD_DANALOG_DOWN,		//!< �A�i���O�\���L�[��.
	GAMEPAD_DANALOG_LEFT,		//!< �A�i���O�\���L�[��.
	GAMEPAD_DANALOG_RIGHT,		//!< �A�i���O�\���L�[�E.
	GAMEPAD_START,				//!< �X�^�[�g�{�^��.
	GAMEPAD_BACK,				//!< �o�b�N�{�^��.
	GAMEANALOG_LEFT_THUMB,		//!< ���X�e�B�b�N��������.
	GAMEANALOG_RIGHT_THUMB,		//!< �E�X�e�B�b�N��������.
	GAMEANALOG_LEFT_SHOULDER,	//!< LB�L�[.
	GAMEANALOG_RIGHT_SHOULDER,	//!< RB�L�[.
	GAMEPAD_A,					//!< A�{�^��.
	GAMEPAD_B,					//!< B�{�^��.
	GAMEPAD_X,					//!< X�{�^��.
	GAMEPAD_Y,					//!< Y�{�^��.
	XINPUT_ID_MAX				//!< �{�^���̑���.
};

enum KEYSTATE* GetKey();

void KeyCheck(KEYSTATE* Key, int DIK);

void OutputDebug_Number(float outputNum, HWND hWnd);

PADSTATE GetButtonState(XINPUT_ID _buttonId);

void GamePadCheckButton(XINPUT_ID _buttonId, WORD _xinputButton);

void UpdatePad();

#endif 

