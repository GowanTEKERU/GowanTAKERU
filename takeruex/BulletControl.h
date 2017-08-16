#ifndef BULLETCONTROL
#define BULLETCONTROL

#include<d3dx9.h>

#define BULLETNUMBER 60

enum BULLETKIND{BULLET01, HOMING};

struct Bullet {
	BULLETKIND BulletKind;
	D3DXVECTOR2 WindowPos;
	D3DXVECTOR2 WorldPos;
	D3DXVECTOR2 SaveCoordinate;
	float MovementX;
	float MovementY;
	float Size;
	float Speed;
	//float Radius;//���a
	float Rad;//�p�x
	int Atk;
	int ReflectMax;
	int ReflectCnt;
	bool wasReflect;
	bool beActive;
	Bullet* next;
	Bullet* previous;
};

Bullet* GetBullet();

//���̂�����bullet��T���ł��܂�
//Bullet* pFirstBullet = GetFirstBulletAddress();
//for (Bullet* pSearchBullet = pFirstBullet->next; pSearchBullet != NULL; pSearchBullet = pSearchBullet->next)
Bullet* GetFirstBulletAddress();

//�w�肳�ꂽ�n�_�ɒe�𐶐����܂�
//������ ���˒n�_
//������ ��������e�̎��
void BulletCreate(const D3DXVECTOR2& launchingSite, BULLETKIND bulletKind);

//�p�x����movement���Z�b�g���܂�
void SetBulletMovement(Bullet* pBullet);

//�w�肳�ꂽ�e�������܂��i�O����Ȃ���free���܂��j
//�n���ꂽ�A�h���X�͈�O�̃A�h���X�ɕύX���܂�
//������ ���������e�̃A�h���X�̃A�h���X
void DeleteBullet(Bullet** DeletionBullet);

//���ׂĂ̒e��free���܂�
void DeleteALLBullet();

void BulletCreate(int bulletNum, int enemyNum, BULLETKIND bulletKind);

void BulletControl();

void BulletInit();

//bullet���������܂�
void DeactivateBullet(int num);

void MoveBullet();


#endif
