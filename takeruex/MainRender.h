#ifndef MAINRENDER_H
#define MAINRENDER_H

#include"CommonRender.h"
#include"MainControl.h"

#define ENEMYPNGSIZE 1024.0f
#define BOSSMAXFRCNT 180
#define BOSSNEXTSTAGEWAIT 300

enum MAINSCENE_TEXTURE
{
	STAGE_1_BACKGROUND_TEX,
	STAGE_2_BACKGROUND_TEX,
	STAGE_3_BACKGROUND_TEX,
	STAGE_4_BACKGROUND_TEX,
	STAGE_5_BACKGROUND_TEX,
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

void MainRender(RENDER_STATE stageStartState);

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
