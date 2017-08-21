#ifndef BOSS4CONTROL_H
#define BOSS4CONTROL_H

#include<d3dx9.h>

enum BOSS4STATE {

};

struct Boss4Data {
	D3DXVECTOR2 WolrdPos;
	D3DXVECTOR2 WindowPos;
	BOSS4STATE Boss3State;
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

Boss4Data* GetBoss4Data();

#endif
