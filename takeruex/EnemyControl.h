#ifndef ENEMYCONTROL_H
#define ENEMYCONTROL_H
#include<d3dx9.h> 
#define ENEMYGRAVITY 3//�G�l�~�[�ɂ�����d��

struct Enemy { 
	D3DXVECTOR2 WindowPos;
	D3DXVECTOR2 WorldPos;
	D3DXVECTOR2 EnemyBasePoint;
	int  enemyKind;//�G�l�~�[�̎��
	float Speed;
	float MovementX;//�G�l�~�[��1�t���[��������̈ړ���
	float MovementY;
	int Atk;
	int Hp;
	float bulletFrameCount;//�e�����t���O�𗧂Ă邽�߂̃t���[����}���Ă���
	float firingInterval;//���ˊ��o
	bool beDead;//����ł��邩
	bool beActive;//��������
	bool beLeft;//���i�E�j�ǂ��������Ă邩
	//float Height;//�摜�̻��ލ���
	//float Width;//�摜�T�C�Y�̕�


};

////�G�l�~�[�f�[�^
int GetEnemyMax();
Enemy* GetEnemyData();
void EnemyInit();
void EnemyControl();
void MoveEnemy();
void FreeEnemyData();

#endif
