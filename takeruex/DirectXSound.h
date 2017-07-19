#ifndef DIRECTXSOUND_H
#define DIRECTXSOUND_H

#include<Windows.h>

enum SOUND_ID { SOUND01,SOUND02, SOUNDMAX };

//Directsound�̏��������s���܂�
//������ �E�B���h�E�̃n���h��
void DirectXSoundInit(HWND hWnd);

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
void ReleaseBuffer();

//�T�E���h�f�o�C�X�̃����[�X
void ReleaseSoundDevice();
#endif

