#ifndef ENEMYCONTROL_H
#define ENEMYCONTROL_H
#include<d3dx9.h> 
#define ENEMYNUMBER 10//�G�l�~�[�̐�
//#define GRAVITY 1//�G�l�~�[�ɂ�����d��



enum EnemyKind {Flyingenemy = 5 ,Flyingenemy_Kye01=6,Flyingenemy_Kye02=7, Walkingenemy=9, Walkingenemy_Kye02=8};
/*�G�l�~�[�̎��
�󒆌^
Flyingenemy  �m�[�}���󒆌^
Flyingenemy_Kye01 �L�[�P�Ԏ����̋󒆌^
Flyingenemy_Kye02 �L�[2�Ԏ����̋󒆌^
�n��^
Walkingenemy �m�[�}���n��^
Walkingenemy_Kye02 �L�[2�Ԏ����̒n��^
*/



struct Enemy { 
	D3DXVECTOR2 WindowPos;
	D3DXVECTOR2 WorldPos;
	EnemyKind enemyKind;//�G�l�~�[�̎��
	float Speed;
	float MovementX;//�G�l�~�[��1�t���[��������̈ړ���
	float MovementY;
	int Atk;
	int Hp;
	int bulletFreamCount;//�e�����t���O�𗧂Ă邽�߂̃t���[����}���Ă���
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
