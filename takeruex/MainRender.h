#ifndef MAINRENDER_H
#define MAINRENDER_H

#include"CommonRender.h"

#define BOSSPNGSIZE 512.0f

enum MAINSCENE_TEXTURE
{
	BACKGROUND_TEX,
	PLAYER_TEX,
	BULLET_TEX,
	MAP_TEX,
	ENEMY01_TEX,
	BOSS_TEX,
	HPUI_TEX,
	HPUIIN_TEX,
	MAINSCENE_TEXMAX
};

void MainRender();

//�摜�̍��E�𔽓]�����܂�
//������ ���]������S���_�̐擪�A�h���X
void TurnVertex_tu(CUSTOMVERTEX* vertex);

#endif
