#ifndef BOSS3CONTROL_H
#define BOSS3CONTROL_H

#include<d3dx9.h>

enum BOSS3STATE {
	
};

struct Boss3Data {
	D3DXVECTOR2 WolrdPos;
	D3DXVECTOR2 WindowPos;
	BOSS3STATE Boss3State;
	float MovementX, MovementY;
	float a;//, ga;//�����x�A�d�͉����x
	int Hp;
	int Atk;
	//bool isJumping;
	bool isLeft;
	bool isDead;
	bool isActive;
	bool isExistence;//���݂��Ă��邩�ǂ���
};

Boss3Data* GetBoss3Data();

#endif