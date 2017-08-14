#ifndef ENEMYCONTROL_H
#define ENEMYCONTROL_H
#include<d3dx9.h> 
#define ENEMYNUMBER 10//�G�l�~�[�̐�
//#define GRAVITY 1//�G�l�~�[�ɂ�����d��






struct Enemy { 
	D3DXVECTOR2 WindowPos;
	D3DXVECTOR2 WorldPos;
	int  enemyKind;//�G�l�~�[�̎��
	float Speed;
	float MovementX;//�G�l�~�[��1�t���[��������̈ړ���
	float MovementY;
	int Atk;
	int Hp;
	int bulletFrameCount;//�e�����t���O�𗧂Ă邽�߂̃t���[����}���Ă���
	int firingInterval;//���ˊ��o
	bool beDead;//����ł��邩
	bool beActive;//��������
	bool beLeft;//���i�E�j�ǂ����������Ă邩
	int size;


};

////�G�l�~�[�f�[�^
Enemy* GetenemyData();
void EnemyInit();
void EnemyControl();
void MoveEnemy();

#endif
