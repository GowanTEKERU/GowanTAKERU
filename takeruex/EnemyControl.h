#ifndef ENEMYCONTROL_H
#define ENEMYCONTROL_H

#include<d3dx9.h>
#define MOVE_SUPEED 3.0f
#define ENEMYNUMBER 2



enum EnemyKind { enemyKind01 = 1 };

struct Enemy { 
	D3DXVECTOR2 WindowPos;
	D3DXVECTOR2 WorldPos;
	EnemyKind enemyKind;//�G�l�~�[�̎��
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

#endif
