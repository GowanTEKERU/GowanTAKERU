#ifndef BOSS2CONTROL_H
#define BOSS2CONTROL_H

#include<d3dx9.h>

#define BOSS2WIDTH 168
#define BOSS2HEIGHT 197

enum BOSS2STATE {
	UDMOVE,GOLEFT,GOPOSB
};

struct Boss2Data {
	D3DXVECTOR2 WorldPos;
	D3DXVECTOR2 WindowPos;
	BOSS2STATE boss2State;//���[�g���򂵂��ʒu���o���Ă���
	float MovementX, MovementY;
	int Hp;
	int Atk;
	bool UporDown_UP;
	bool hasDamage;//�_���[�W��^����ꂽ���ǂ����̃t���O
	bool isLeft;//����true�ō�����
	bool isDead;//����
	bool isActive;//�`��A�N�e�B�u���ǂ���
	bool isExistence;//���݂��Ă��邩�ǂ���
	int lastbullet;//�O�ɑł��������ǂꂩ�L������
};




//�v���g�^�C�v�Q
void Boss2Init();
void Boss2Control();
void MoveBoss2();
Boss2Data* GetBoss2Data();//�{�X�Q�̃f�[�^

#endif