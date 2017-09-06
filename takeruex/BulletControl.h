#ifndef BULLETCONTROL
#define BULLETCONTROL

#include<d3dx9.h>

#define BULLETNUMBER 60

enum BULLETKIND{
	BULLETNORMAL1,
	BULLETNORMAL2,
	BULLETNORMAL3,
	BULLETNORMAL4,
	BULLETNORMAL5,
	BULLETNORMAL6,
	BULLETNORMAL7,
	BULLETNORMAL8,
	BULLETNORMAL9,
	BULLETNORMAL10,
	BULLETTARGET1,
	BULLETTARGET2,
	BULLETTARGET3,
	BULLETTARGET4,
	BULLETTARGET5,
	BULLETTARGET6,
	BULLETTARGET7,
	BULLETTARGET8,
	BULLETTARGET9,
	BULLETTARGET10,
	NONREFLECTNORMAL1,
	NONREFLECTNORMAL2,
	NONREFLECTNORMAL3,
	NONREFLECTNORMAL4,
	NONREFLECTNORMAL5,
	NONREFLECTNORMAL6,
	NONREFLECTNORMAL7,
	NONREFLECTNORMAL8,
	NONREFLECTNORMAL9,
	NONREFLECTNORMAL10,
	NONREFLECTTARGET1,
	NONREFLECTTARGET2,
	NONREFLECTTARGET3,
	NONREFLECTTARGET4,
	NONREFLECTTARGET5,
	NONREFLECTTARGET6,
	NONREFLECTTARGET7,
	NONREFLECTTARGET8,
	NONREFLECTTARGET9,
	NONREFLECTTARGET10,
	HOMING1,
	HOMING2,
	HOMING3,
	HOMING4,
	HOMING5,
	HOMING6,
	HOMING7,
	HOMING8,
	HOMING9,
	HOMING10,
	BULLET_MAX
};

struct Bullet {
	int BulletKind;
	D3DXVECTOR2 WindowPos;
	D3DXVECTOR2 WorldPos;
	D3DXVECTOR2 SaveCoordinate;
	float MovementX;
	float MovementY;
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

struct EditableBulletData {
	int Atk;
	int ReflectMax;
	float Speed;
	float Size;
	float tu, tv;
};

void LoadBulletData();

EditableBulletData* GetEditableBulletData();

//���̂�����bullet��T���ł��܂�
//Bullet* pFirstBullet = GetFirstBulletAddress();
//for (Bullet* pSearchBullet = pFirstBullet->next; pSearchBullet != NULL; pSearchBullet = pSearchBullet->next)
Bullet* GetFirstBulletAddress();

//�w�肳�ꂽ�n�_�ɒe�𐶐����܂�
//������ ���[���h�|�W�V�����̔��˒n�_
//������ ��������e�̎��
//��O���� �e�Ɋp�x��������܂�
void BulletCreate(const D3DXVECTOR2& launchingSite, int bulletKind, float plusDeg = 0.0f);

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
