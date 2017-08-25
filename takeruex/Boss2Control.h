#ifndef BOSS2CONTROL_H
#define BOSS2CONTROL_H
#include<d3dx9.h>

struct Boss2Data {
	D3DXVECTOR2 WorldPos;
	D3DXVECTOR2 WindowPos;
	float MovementX, MovementY;
	int Hp;
	int saveShotFrmcnt;
	int saveActionCntForNORMALSHOT;
	int saveActionCntForDUALSHOT;
	int saveDUALSHOTActionCntForLARIAT;
	int Atk;
	bool isLeft;//����true�ō�����
	bool isDead;//����
	bool isActive;//�`��A�N�e�B�u���ǂ���
	bool isExistence;//���݂��Ă��邩�ǂ���
};




//�v���g�^�C�v�Q
void Boss2Init();
void Boss2Control();
void MoveBoss2();
Boss2Data* GetBoss2Data();//�{�X�Q�̃f�[�^

#endif