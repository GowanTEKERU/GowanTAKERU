#ifndef MAPCONTROL_H
#define MAPCONTROL_H

#include<d3dx9.h>
#include"MapRender.h"

enum Direction{UP,RIGHTUP,RIGHT,RIGHTDOWN,DOWN,LEFTDOWN,LEFT,LEFTUP};

struct MapNumXY {
	int NumX, NumY;
};

//�������[�[�[�[���̍\���̂�X�̃}�b�v�`�b�v�ԍ��AY�̃}�b�v�`�b�v�ԍ���Ԃ��Ă���܂�
//�������[�[�[�[���[���h���W�����Ă�������
void MapchipNumberSpecify(MapNumXY* pMapNumXY, D3DXVECTOR2* pWorldPos);

//�}�b�v�`�b�v�̔ԍ��������
//���W��Ԃ��Ă���܂�
void PosSpecifyForMapchipNumber(D3DXVECTOR2* pWorldPos, MapNumXY* pMapNumXY);

int MapKindSpecify(MapNumXY* pMapNumXY);

int MapKindSpecify_Plus1(MapNumXY* pMapNumXY, Direction direction);

#endif 

