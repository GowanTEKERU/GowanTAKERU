#ifndef DIRECTXSOUND_H
#define DIRECTXSOUND_H

#include<Windows.h>

//enum MAINSCENESOUND_ID { MAINSCENE_BGM01, MAINSCENE_SE_ATTACK, MAINSCENE_SE_JUMP, MAINSCENE_SE_SWING, MAINSCENE_SOUNDMAX };
//enum TITLESCENESOUND_ID { TITLESCENE_BGM01, TITLESCENE_SOUNDMAX };
//enum GAMECLEARSCENESOUND_ID { GAMECLEAR_BGM01, GAMECLEAR_SOUNDMAX };
//enum GAMEOVERSCENESOUND_ID { GAMEOVERSCENE_BGM01, GAMEOVER_SOUNDMAX };

enum SOUND_ID {
	MAINSCENE_STAGEBGM01,
	MAINSCENE_STAGEBGM02,
	MAINSCENE_STAGEBGM03,
	MAINSCENE_STAGEBGM04,
	MAINSCENE_BOSSBGM01,
	MAINSCENE_BOSSBGM02,
	MAINSCENE_BOSSBGM03,
	MAINSCENE_SE_ATTACK,
	MAINSCENE_SE_JUMP,
	MAINSCENE_SE_SWING,
	TITLESCENE_BGM01,
	GAMECLEAR_BGM01,
	GAMEOVERSCENE_BGM01,
	SOUND_MAX
};

//Directsound�̏��������s���܂�
//������ �E�B���h�E�̃n���h��
void DirectXSoundInit(HWND hWnd);

//buffer�𓮓I�Ɋm�ۂ��܂�
void SetBuffer(int num);

//���I�Ɋm�ۂ������̊J��
void FreeBuffer();

//�o�b�t�@��wave�t�@�C������쐬���܂��B�o�b�t�@�̓O���[�o���ł��B
//������ wave�t�@�C���ւ̃p�X
//������ ���ʂ��邽�߂�ID�ienum)
//�߂�l ������true,���s��false
bool CreateBufferForWave(char* soundfile, int soundID);

//�T�E���h���Đ����܂�
//������ ���ʂ��邽�߂�ID�ienum)
//������ ���[�v����Ȃ�true,���Ȃ��Ȃ�false
void PlayBackSound(int soundID, bool loop, LONG volume);

// �T�E���h���~���܂�
//������ ���ʂ��邽�߂�ID�ienum)
void StopSound(int soundID);

//�o�b�t�@�̃����[�X
void ReleaseBuffer(int soundMax);

//�T�E���h�f�o�C�X�̃����[�X
void ReleaseSoundDevice();

#endif

