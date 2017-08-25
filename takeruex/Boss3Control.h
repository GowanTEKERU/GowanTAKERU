#ifndef BOSS3CONTROL_H
#define BOSS3CONTROL_H

#include<d3dx9.h>

//�V�[���h���܂߂��傫��
#define BOSS3OBJWIDTH		240.0f
#define BOSS3OBJHEIGHT		256.0f

//�{�X�R�{�̂̑傫��
#define BOSS3WIDTH			174.0f
#define BOSS3HEIGHT			220.0f
#define BOSS3MAXSPEED		0.5f

#define BOSS3SHIELD1WIDTH	22.0f
#define BOSS3SHIELD1HEIGHT	200.0f
#define BOSS3SHIELD2WIDTH	24.0f
#define BOSS3SHIELD2HEIGHT	180.0f
#define BOSS3SHIELD3WIDTH	24.0f
#define BOSS3SHIELD3HEIGHT	120.0f

enum BOSS3STATE {
	BOSS3_NON,SHOTNORMALBULLET,SHOTPOWERBULLET,
};

struct Boss3Data {
	D3DXVECTOR2 WolrdPos;
	D3DXVECTOR2 WindowPos;
	BOSS3STATE Boss3State;
	float MovementX, MovementY;
	int Hp;
	int Atk;
	bool isLeft;
	bool isDead;
	bool isActive;
	bool isExistence;//���݂��Ă��邩�ǂ���
};

Boss3Data* GetBoss3Data();

void Boss3Init();

void Boss3Control();

void MoveBoss3();

#endif