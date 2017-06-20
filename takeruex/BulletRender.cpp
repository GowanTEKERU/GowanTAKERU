#include"BulletRender.h"
#include"BulletControl.h"
#include"DirectXGraphics.h"
#include"CommonRender.h"
#include"FileManagement.h"
#include"MainRender.h"

void BulletRender() {

	Bullet* bullet = GetBullet();

	IDirect3DDevice9* pD3Device = GetGraphicsDevice();
	LPDIRECT3DTEXTURE9* pTexture = GetTexture();

	for (int i = 0; i < BULLETNUMBER; i++) {

		CUSTOMVERTEX Bullet[] = {
			{-(bullet + i)->Size / 2,-(bullet + i)->Size / 2,0.5f,1.0f,0xFFFFFFFF,0.0f,0.0f },
			{ (bullet + i)->Size / 2,-(bullet + i)->Size / 2,0.5f,1.0f,0xFFFFFFFF,0.0f,0.0f },
			{ (bullet + i)->Size / 2, (bullet + i)->Size / 2,0.5f,1.0f,0xFFFFFFFF,0.0f,0.0f },
			{-(bullet + i)->Size / 2, (bullet + i)->Size / 2,0.5f,1.0f,0xFFFFFFFF,0.0f,0.0f }
		};

		CUSTOMVERTEX DrawVertex[4];
		for (int i = 0; i < 4; i++) {
			DrawVertex[i] = Bullet[i];
			DrawVertex[i].x += bullet->WindowPos.x;
			DrawVertex[i].y += bullet->WindowPos.y;
		}

			// �e�N�X�`�����X�e�[�W�Ɋ��蓖�Ă�
			pD3Device->SetTexture(0, pTexture[BULLET01_TEX]);
			// �`��
			pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, DrawVertex, sizeof(CUSTOMVERTEX));
		
	}
}