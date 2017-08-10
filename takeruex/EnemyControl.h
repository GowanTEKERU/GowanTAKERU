#ifndef ENEMYCONTROL_H
#define ENEMYCONTROL_H
#include<d3dx9.h> 
#define ENEMYNUMBER 10//�G�l�~�[�̐�
//#define GRAVITY 1//�G�l�~�[�ɂ�����d��



enum ENEMYKIND { 
	WALKINGENEMY_1=21,//�n��G
	WALKINGENEMY_2,
	WALKINGENEMY_3,
	WALKINGENEMY_4,
	WALKINGENEMY_5,
	WALKINGENEMY_HAS_KEY_1,
	WALKINGENEMY_HAS_KEY_2,
	WALKINGENEMY_HAS_KEY_3,
	FixedBattery1=31,//�Œ�C��
	FLYINGENEMY1,//�󒆓G
	FLYINGENEMY2,
	FLYINGENEMY3,
	FLYINGENEMY4,
	FLYINGENEMY5,
	FLYINGENEMY_HAS_KEY1,
	FLYINGENEMY_HAS_KEY2,
	FLYINGENEMY_HAS_KEY3,
	FixedBattery2,
};
/*�G�l�~�[�̎��

*/



struct Enemy { 
	D3DXVECTOR2 WindowPos;
	D3DXVECTOR2 WorldPos;
	ENEMYKIND enemyKind;//�G�l�~�[�̎��
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


};

////�G�l�~�[�f�[�^
Enemy* GetenemyData();
void EnemyInit();
void EnemyControl();
void MoveEnemy();

#endif
