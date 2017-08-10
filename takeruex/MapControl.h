#ifndef MAPCONTROL_H
#define MAPCONTROL_H

#include<d3dx9.h>
#include"MapRender.h"

enum Direction { UP, RIGHTUP, RIGHT, RIGHTDOWN, DOWN, LEFTDOWN, LEFT, LEFTUP };

struct MapNumXY {
	int NumX, NumY;
};

//�������[�[�[�[MapNumXY�̍\���̂�X�̃}�b�v�`�b�v�ԍ��AY�̃}�b�v�`�b�v�ԍ���Ԃ��Ă���܂�
//�������[�[�[�[���[���h���W�����Ă�������
void MapchipNumberSpecify(MapNumXY* pMapNumXY, D3DXVECTOR2* pWorldPos);

//�������[�[�[�[���[���h���W��Ԃ��Ă���܂�
//�������[�[�[�[�}�b�v�`�b�v�̔ԍ�(MapNumXY)������Ă�������
void PosSpecifyForMapchipNumber(D3DXVECTOR2* pWorldPos, MapNumXY* pMapNumXY);

//�}�b�v�`�b�v�̔ԍ�(MapNumXY)������āA���̃}�b�v�`�b�v�̎�ނ�Ԃ��Ă���܂�
int MapKindSpecify(MapNumXY* pMapNumXY);

//���[���h���W�����āA�����̃}�b�v�`�b�v�̎�ނ�Ԃ��Ă���܂�
int MapKindSpecifyForPos(D3DXVECTOR2* pWorldPos);

//�������[�[�[�[�}�b�v�`�b�v�̔ԍ�(MapNumXY)�������
//�������[�[�[�[�����iDirection�j���w�肷��Ƃ��̕����̃}�b�v�`�b�v�̎�ނ�Ԃ��Ă���܂�
int MapKindSpecify_Plus1(MapNumXY* pMapNumXY, Direction direction);

int CalculateNumInRange(float l) ;

#endif 

