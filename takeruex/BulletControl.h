#ifndef BULLETCONTROL
#define BULLETCONTROL

#include<d3dx9.h>

#define BULLETNUMBER 60

enum BULLETKIND{//	���ˉ�		�X�s�[�h		�З�
	BULLETNORMAL1,//	5				5			10
	BULLETNORMAL2,//	4				7			10
	BULLETNORMAL3,//	5				7			7
	BULLETNORMAL4,//
	BULLETNORMAL5,//
	BULLETTARGET1,//	1				6			10
	BULLETTARGET2,//	3				6			10
	BULLETTARGET3,//	5				6			10
	BULLETTARGET4,//	3				8			10
	BULLETTARGET5,//	3				5			15
	BULLETTARGET6,//
	NONREFLECTTARGET1,//3				5			7
	NONREFLECTTARGET2,//3				5			25
	HOMING		  //	1				5			10
};

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
	Bullet* next;
	Bullet* previous;
};

Bullet* GetBullet();

//���̂�����bullet��T���ł��܂�
//Bullet* pFirstBullet = GetFirstBulletAddress();
//for (Bullet* pSearchBullet = pFirstBullet->next; pSearchBullet != NULL; pSearchBullet = pSearchBullet->next)
Bullet* GetFirstBulletAddress();

//�w�肳�ꂽ�n�_�ɒe�𐶐����܂�
//������ ���[���h�|�W�V�����̔��˒n�_
//������ ��������e�̎��
//��O���� �e�Ɋp�x��������܂�
void BulletCreate(const D3DXVECTOR2& launchingSite, BULLETKIND bulletKind, float plusDeg = 0.0f);

//�p�x����movement���Z�b�g���܂�
void SetBulletMovement(Bullet* pBullet);

//�w�肳�ꂽ�e�������܂��i�O����Ȃ���free���܂��j
//�n���ꂽ�A�h���X�͈�O�̃A�h���X�ɕύX���܂�
//������ ���������e�̃A�h���X�̃A�h���X
void DeleteBullet(Bullet** DeletionBullet);

//���ׂĂ̒e��free���܂�
void DeleteALLBullet();

void BulletControl();

void BulletInit();

void MoveBullet();


#endif
