#ifndef ENEMYCONTROL_H
#define ENEMYCONTROL_H
#include"BulletControl.h"
#include<d3dx9.h> 

#define ENEMY_KIND_MAX 31

#define ENEMYGRAVITY 3//�G�l�~�[�ɂ�����d��

#define INTMAX 2147483647

enum enemyRushDistance {
	RushDistance =300//�ːi����
};

struct Enemy { 
	D3DXVECTOR2 WindowPos;
	D3DXVECTOR2 WorldPos;
	D3DXVECTOR2 EnemyBasePoint;
	D3DXVECTOR2 FrontWorldPos;
	int BulletKind;
	int  enemyKind;//�G�l�~�[�̎��
	float Speed;
	float MovementX;//�G�l�~�[��1�t���[��������̈ړ���
	float MovementY;
	int Atk;
	int Hp;
	int bulletFrameCount;//�e�����t���O�𗧂Ă邽�߂̃t���[����}���Ă���
	int firingInterval;//���ˊ��o
	float BulletDeg;
	bool beDead;//����ł��邩
	bool beActive;//��������
	bool beLeft;//���i�E�j�ǂ��������Ă邩
	float Height;//�摜�̻��ލ���
	float Width;//�摜�T�C�Y�̕�
	float tu, tv;
	bool Rush;//�ːi�̃t���O

};

struct EditableEnemyData {
	int BulletKind;
	float BulletDeg;
	float ShotInterval;//���ˊԊu�i�b���j
	float Speed;
	float tu, tv, Width, Height;
	int	Hp;
	int Atk;
	
};

void LeadEnemyData();

////�G�l�~�[�f�[�^
int GetEnemyMax();
Enemy* GetEnemyData();
void EnemyInit();
void EnemyControl();
void MoveEnemy();
void FreeEnemyData();

#endif
