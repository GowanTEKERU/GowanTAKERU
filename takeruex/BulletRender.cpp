#include"BulletRender.h"
#include"DirectXGraphics.h"
#include"CommonRender.h"
#include"FileManagement.h"

//void BulletRender() {
//
//	IDirect3DDevice9* pD3Device = GetGraphicsDevice();
//	LPDIRECT3DTEXTURE9* pTexture = GetTexture();
//
//			CUSTOMVERTEX Bullet[] = {
//				{ g_enemyBullet[i].cx - BULLETSIZE / 2,g_enemyBullet[i].cy - BULLETSIZE / 2,0.5f,1.0f,0xFFFFFFFF,0.0f,0.0f },
//				{ g_enemyBullet[i].cx + BULLETSIZE / 2,g_enemyBullet[i].cy - BULLETSIZE / 2,0.5f,1.0f,0xFFFFFFFF,1.0f,0.0f },
//				{ g_enemyBullet[i].cx + BULLETSIZE / 2,g_enemyBullet[i].cy + BULLETSIZE / 2,0.5f,1.0f,0xFFFFFFFF,1.0f,1.0f },
//				{ g_enemyBullet[i].cx - BULLETSIZE / 2,g_enemyBullet[i].cy + BULLETSIZE / 2,0.5f,1.0f,0xFFFFFFFF,0.0f,1.0f }
//			};
//
//			for (int i = 0; i < 4; i++) {
//
//
//			// �e�N�X�`�����X�e�[�W�Ɋ��蓖�Ă�
//			pD3Device->SetTexture(0, pTexture[BULLET01_TEX]);
//			// �`��
//			pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, DrawBullet, sizeof(CUSTOMVERTEX));
//		}
//	}
//}