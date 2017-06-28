#ifndef ENEMYCONTROL_H
#define ENEMYCONTROL_H

#include<d3dx9.h>
#define MOVE_SUPEED 3.0f
#define ENEMYNUMBER 2



struct Enemy { 
	D3DXVECTOR2 WindowPos;
	D3DXVECTOR2 WorldPos;
	int Atk;
	int Hp;
	int Kind;
	bool beDead;//����ł��邩
	bool beActive;//��������
	bool beLeft;//���i�E�j�ǂ����������Ă邩

};

////�G�l�~�[�f�[�^
Enemy* GetenemyData();
void EnemyInit();
void EnemyControl();

#endif
