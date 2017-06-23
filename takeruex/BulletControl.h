#ifndef BULLETCONTROL
#define BULLETCONTROL

#include<d3dx9.h>

#define BULLETNUMBER 30

enum BulletKind{bullet01};

struct Bullet {
	BulletKind BulletKind;
	D3DXVECTOR2 WindowPos;
	D3DXVECTOR2 WorldPos;
	D3DXVECTOR2 SaveCoordinate;
	float Size;
	float Speed;
	float Radius;//���a
	float Rad;//�p�x
	int Atk;
	int ReflectMax;
	int ReflectCnt;
	bool wasReflect;
	bool beActive;
};

Bullet* GetBullet();

void BulletCreate(int num, BulletKind C);

void BulletControl();

void BulletInit();


#endif
