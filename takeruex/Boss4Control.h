#ifndef BOSS4CONTROL_H
#define BOSS4CONTROL_H

#include<d3dx9.h>

#define BOSS4WIDTH 114
#define BOSS4HEIGHT 152

enum BOSS4JUMPSTATE {
	GROUND,JUMP,LEFTJUMP,LEFTHIGHJUMP,RIGHTJUMP,RIGHTHIGHJUMP,POSB_RJUMP,POSB_LJUMP
};

struct Boss4Data {
	D3DXVECTOR2 WolrdPos;
	D3DXVECTOR2 WindowPos;
	BOSS4JUMPSTATE Boss4JumpState;
	float MovementX, MovementY;
	float ga;//重力加速度
	int Hp;
	int Atk;
	int FrCnt;
	int JumpFrCnt;
	bool isJumping;
	bool isLeft;
	bool isDead;
	bool isActive;
	bool isExistence;//存在しているかどうか
};

Boss4Data* GetBoss4Data();

void Boss4Init();

void Boss4Control();

void MoveBoss4();

#endif
