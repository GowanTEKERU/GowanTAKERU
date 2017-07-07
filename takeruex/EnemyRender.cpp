#include"EnemyRender.h"
#include"EnemyControl.h"
#include"MainRender.h"
#include"FileManagement.h"
#include"DirectXGraphics.h"

void EnemyRender() {

	IDirect3DDevice9* pD3Device = GetGraphicsDevice();
	LPDIRECT3DTEXTURE9* pTexture = GetTexture();

	Enemy* enemy = GetenemyData();

	CUSTOMVERTEX Enemy[] = {
		{-ENEMYRESIZEWIDTH / 2, -ENEMYRESIZEHEIGHT / 2, 0.5f,1.0f,0xFFFFFFFF,0.0f,0.0f },
		{ ENEMYRESIZEWIDTH / 2, -ENEMYRESIZEHEIGHT / 2, 0.5f,1.0f,0xFFFFFFFF,1.0f,0.0f },
		{ ENEMYRESIZEWIDTH / 2,  ENEMYRESIZEHEIGHT / 2, 0.5f,1.0f,0xFFFFFFFF,1.0f,1.0f },
		{-ENEMYRESIZEWIDTH / 2,  ENEMYRESIZEHEIGHT / 2, 0.5f,1.0f,0xFFFFFFFF,0.0f,1.0f }
	};


	for (int i = 0; i < ENEMYNUMBER; i++) {
	if (enemy[i].beDead == false && enemy[i].beActive == true)
	{
			CUSTOMVERTEX DrawVertex[4];
			for (int j = 0; j < 4; j++) {
				DrawVertex[j] = Enemy[j];
				DrawVertex[j].x += enemy[i].WindowPos.x;
				DrawVertex[j].y += enemy[i].WindowPos.y;
			}
			// �e�N�X�`�����X�e�[�W�Ɋ��蓖�Ă�
			pD3Device->SetTexture(0, pTexture[ENEMY01_TEX]);
			// �`��
			pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, DrawVertex, sizeof(CUSTOMVERTEX));
		}
	}
}