#include"MapRender.h"
#include"CommonRender.h"
#include"DirectXGraphics.h"
#include"FileManagement.h"
#include"MainRender.h"
#include"MapControl.h"
#include"PlayerControl.h"

static int g_map[MAPCHIPNUM_HEIGHT*MAPCHIPNUM_WIDTH];

int* GetMapchipData() {
	return g_map;
}

void MapRender() {

	D3DXVECTOR2* BasePoint = GetBasePoint();

	IDirect3DDevice9* pD3Device = GetGraphicsDevice();
	LPDIRECT3DTEXTURE9* pTexture = GetTexture();

	CUSTOMVERTEX map[] = {
		{ 0,0,0.5f,1.0f, 0xFFFFFFFF,0.0f,0.0f },
		{ TIPSIZE,0,0.5f,1.0f,0xFFFFFFFF,1.0f,0.0f },
		{ TIPSIZE,TIPSIZE,0.5f,1.0f,0xFFFFFFFF,1.0f,1.0f },
		{ 0,TIPSIZE,0.5f,1.0f,0xFFFFFFFF,0.0f,1.0f }
	};

	//basepoint�̏����ʒu
	//playercontrol.cpp�ƍ��킹�Ă�������
	D3DXVECTOR2 BasePoint0 = D3DXVECTOR2(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);

	//�����ʒu����̍���
	float differenceX = BasePoint->x - BasePoint0.x;
	float differenceY = BasePoint->y - BasePoint0.y;

	//�`��͈̗͂v�f�ԍ����w��
	MapNumXY RendArrayIndexLeftUp;
	MapNumXY RendArrayIndexRightDown;
	MapNumXY RendArrayIndex;

	MapchipNumberSpecify(&RendArrayIndex, BasePoint);

	RendArrayIndexLeftUp.NumX = RendArrayIndex.NumX - RENDERMAPCHIPNUM_WIDTH / 2;
	RendArrayIndexLeftUp.NumY = RendArrayIndex.NumY - RENDERMAPCHIPNUM_HEIGHT / 2;
	RendArrayIndexRightDown.NumX = RendArrayIndex.NumX + RENDERMAPCHIPNUM_WIDTH / 2;
	RendArrayIndexRightDown.NumY = RendArrayIndex.NumY + RENDERMAPCHIPNUM_HEIGHT / 2;

	//�`��pvertex
	CUSTOMVERTEX drawMapVertex[4];

	for (int i = 0; i < MAPCHIPNUM_HEIGHT; i++) {
		for (int j = 0; j < MAPCHIPNUM_WIDTH; j++) {

			if (i == 4 && j == 17) {
				int a = 5;
			}
			if (i == 6 && j == 17) {
				int a;
			}

			//���̃}�b�v�`�b�v��`�悷��̂��𔻒�
			if     (RendArrayIndexLeftUp.NumY < i && i < RendArrayIndexRightDown.NumY ) {
				if (RendArrayIndexLeftUp.NumX < j && j < RendArrayIndexRightDown.NumX) {

					//�`�悷��ꏊ��ݒ�
					for (int k = 0; k < 4; k++) {
						drawMapVertex[k] = map[k];
						drawMapVertex[k].x += -differenceX + TIPSIZE*j;
						drawMapVertex[k].y += -differenceY + TIPSIZE*i;
					}


					switch (g_map[j + i*MAPCHIPNUM_WIDTH]) {

					case nothing:
						break;

					case yuka:
						// �e�N�X�`�����X�e�[�W�Ɋ��蓖�Ă�
						pD3Device->SetTexture(0, pTexture[MAP_TEX]);
						// �`��
						pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, drawMapVertex, sizeof(CUSTOMVERTEX));
						break;
					}
				}
			}
		}
	}

}