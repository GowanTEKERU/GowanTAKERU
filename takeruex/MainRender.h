#ifndef MAINRENDER_H
#define MAINRENDER_H

#include"CommonRender.h"

#define ENEMYPNGSIZE 1024.0f

enum MAINSCENE_TEXTURE
{
	BACKGROUND1_TEX,
	PLAYER_TEX,
	BULLET_TEX,
	MAP_TEX,
	ENEMY_TEX,
	HPUI_TEX,
	HPUIIN_TEX,
	RETRYICON_TEX,
	FONT_TEX,
	MAINSCENE_TEXMAX
};

void MainRender();

//�摜�̍��E�𔽓]�����܂�
//������ ���]������S���_�̐擪�A�h���X
void TurnVertex_tu(CUSTOMVERTEX* vertex);

//�摜��؂���܂�
//������ �؂����Ăق���vertex[4]�̐擪�A�h���X
//������ ���̃I�u�W�F�N�g�̉摜��̂����W
//��O���� ���̃I�u�W�F�N�g�̉摜��̂����W
//��l���� ���̃I�u�W�F�N�g�̕�
//��܈��� ���̃I�u�W�F�N�g�̍���
//��Z���� �摜�S�̂̕�
//�掵���� �摜�S�̂̍���
void TrimingVertex(CUSTOMVERTEX* vertex, float leftTopTu, float leftTopTv, float width, float height, float pngWidth, float pngHeight);
#endif
