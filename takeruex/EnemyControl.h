#ifndef ENEMYCONTROL_H
#define ENEMYCONTROL_H
#include<d3dx9.h> 
#define MOVE_SUPEED 3.0f//�G�l�~�[�̃X�s�[�h
#define ENEMYNUMBER 3//�G�l�~�[�̐�
#define GRAVITY 1//�G�l�~�[�ɂ�����d��



enum EnemyKind { enemyKind01 = 1,enemyKind02 = 2 ,enemyKind03 = 3 };


/*�G�̎��
kind01���ʏ�n��MOB
kind02=�ʏ��MOB
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
	bool beDead;//����ł��邩
	bool beActive;//��������
	bool beLeft;//���i�E�j�ǂ����������Ă邩

};

////�G�l�~�[�f�[�^
Enemy* GetenemyData();
void EnemyInit();
void EnemyControl();
void MoveEnemy(int enemyNum);

#endif
