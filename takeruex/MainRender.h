#ifndef MAINRENDER_H
#define MAINRENDER_H

#include"CommonRender.h"

enum MAINSCENE_TEXTURE
{
	BACKGROUND_TEX,
	PLAYER_TEX,
	BULLET01_TEX,
	BULLET02_TEX,
	MAP_TEX,
	ENEMY01_TEX,
	HPUI_TEX,
	HPUIIN_TEX,
	MAINSCENE_TEXMAX
};

void MainRender();

//�摜�̍��E�𔽓]�����܂�
//������ ���]������S���_�̐擪�A�h���X
void TurnVertex_tu(CUSTOMVERTEX* vertex);

#endif
