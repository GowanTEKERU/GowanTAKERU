#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include<d3dx9.h>
#include"StageSelect.h"

enum STAGEXYMAX {
	STAGE1_XMAX,
	STAGE1_YMAX,
	STAGE2_XMAX,
	STAGE2_YMAX,
	STAGE3_XMAX,
	STAGE3_YMAX
};

enum X_OR_Y {
	X, Y
};


//pTexture�g�������l������
LPDIRECT3DTEXTURE9* GetTexture();

//texture�������[�X
void TextureFree();

int* GetMapData();

//mainscene�̃e�L�X�`���ƃ}�b�v�̓ǂݍ���
//Relese���s���Ă�������
void MainSceneLoad(STAGE_ID stage_ID);
void ReleseMapData();

void CSVLoad(char* mapdata, int* map, int height, int width);

void StageMapNumMaxInit();

STAGEXYMAX GetStageXYMAX(STAGE_ID stage_ID, X_OR_Y XOrY);

#endif
