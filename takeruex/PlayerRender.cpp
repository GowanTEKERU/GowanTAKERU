#include"PlayerRender.h"
#include"PlayerControl.h"
#include"MainRender.h"
#include"FileManagement.h"
#include"DirectXGraphics.h"
#include"CommonControl.h"

void PlayerRender() {

	Player* player = GetplayerData();

	if (player->beActive) {
		IDirect3DDevice9* pD3Device = GetGraphicsDevice();
		LPDIRECT3DTEXTURE9* pTexture = GetTexture();

		CUSTOMVERTEX Player[] = {
			{ -PLAYERSIZEPNGWIDTH / 2,-PLAYERSIZEPNGHEIGHT / 2,0.5f,1.0f, 0xFFFFFFFF,0.0f,0.0f },
			{ PLAYERSIZEPNGWIDTH / 2,-PLAYERSIZEPNGHEIGHT / 2,0.5f,1.0f,0xFFFFFFFF,PLAYERSIZEPNGWIDTH / 1024.0f - 1 / 1024.0f,0.0f },
			{ PLAYERSIZEPNGWIDTH / 2,PLAYERSIZEPNGHEIGHT / 2,0.5f,1.0f,0xFFFFFFFF,PLAYERSIZEPNGWIDTH / 1024.0f - 1 / 1024.0f,PLAYERSIZEPNGHEIGHT / 1024.0f },
			{ -PLAYERSIZEPNGWIDTH / 2,PLAYERSIZEPNGHEIGHT / 2,0.5f,1.0f,0xFFFFFFFF,0.0f,PLAYERSIZEPNGHEIGHT / 1024.0f }
		};

		CUSTOMVERTEX CurrentDrawVertex[4];
		for (int i = 0; i < 4; i++) {
			CurrentDrawVertex[i] = Player[i];

			if (player->beLeft) {
				CurrentDrawVertex[i].x += player->WindowPos.x - 14.0f;
				CurrentDrawVertex[i].y += player->WindowPos.y - 6.0f;
			}
			else {
				CurrentDrawVertex[i].x += player->WindowPos.x + 14.0f;
				CurrentDrawVertex[i].y += player->WindowPos.y - 6.0f;
			}
			
			int trimX = player->currentAnimState % 10;
			int trimY = player->currentAnimState / 10;

			//runswing���̗�O�����i�摜�̏ꏊ�ɂ����́j
			if ((RUNDOWNSWING1 <= player->currentAnimState) && (player->currentAnimState <= RUNUPSWING6)) {
				CurrentDrawVertex[i].tu += PLAYERSIZEPNGWIDTH * trimY / 1024.f;
				CurrentDrawVertex[i].tv += PLAYERSIZEPNGHEIGHT * trimX / 1024.f;
			}
			//�����łȂ��Ȃ�
			else {

				CurrentDrawVertex[i].tu += PLAYERSIZEPNGWIDTH * trimX / 1024.f;
				CurrentDrawVertex[i].tv += PLAYERSIZEPNGHEIGHT * trimY / 1024.f;

			}
		}

		if (player->beLeft) {
			TurnVertex_tu(CurrentDrawVertex);
		}

		static int frcntInvincible = 0;
		if (player->beInvincible) {
			frcntInvincible++;
		}
		else {
			frcntInvincible = 0;
		}
		if (!player->beInvincible || (frcntInvincible % 18) < 9) {
			// �e�N�X�`�����X�e�[�W�Ɋ��蓖�Ă�
			pD3Device->SetTexture(0, pTexture[PLAYER_TEX]);
			// �`��
			pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, CurrentDrawVertex, sizeof(CUSTOMVERTEX));
		}
	}
}

