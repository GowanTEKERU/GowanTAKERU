#include"Boss2Control.h"
#include"FileManagement.h"
#include"MapRender.h"
#include"PlayerControl.h"
#include"CommonRender.h"
#include"MainControl.h"
#include"BulletControl.h"
#include"MapControl.h"


Boss2Data g_Boss2;

Boss2Data* GetBoss2Data() {
	return &g_Boss2;
}


void Boss2Init() {
	g_Boss2.isExistence = false;

	STAGE_ID stage_ID = GetStage_ID();
	int MaxX = GetStageXYMAX(stage_ID, X);
	int MaxY = GetStageXYMAX(stage_ID, Y);
	int* gimmickData = (int*)malloc(sizeof(int)*MaxX*MaxY);

	switch (stage_ID) {
	case STAGE_2:

		CSVLoad("CSV/mainscene/stage2_gimmick.csv", gimmickData, MaxY, MaxX);//CSV�Ăяo��

		for (int i = 0; i < MaxY; i++) {
			for (int j = 0; j < MaxX; j++) {
				if (gimmickData[j + i*MaxX] == BOSS_STAGE2) {
					g_Boss2.isExistence = true;
					g_Boss2.WorldPos.x = TIPSIZE*j;
					g_Boss2.WorldPos.y = TIPSIZE*i;
					goto BREAK;
				}
			}
		}
		break;


	case STAGE_5:

		CSVLoad("CSV/mainscene/stage5_gimmick.csv", gimmickData, MaxY, MaxX);//CSV�Ăяo��

		for (int i = 0; i < MaxY; i++) {
			for (int j = 0; j < MaxX; j++) {
				if (gimmickData[j + i*MaxX] == BOSS_STAGE2) {
					g_Boss2.isExistence = true;
					g_Boss2.WorldPos.x = TIPSIZE*j;
					g_Boss2.WorldPos.y = TIPSIZE*i;
					goto BREAK;
				}
			}
		}
		break;
	}
BREAK:
	if (g_Boss2.isExistence) {
		g_Boss2.MovementX = g_Boss2.MovementY = 0;
		g_Boss2.Hp = 70;
		g_Boss2.Atk = 20;
		g_Boss2.isLeft = true;
		g_Boss2.isDead = false;
		g_Boss2.isActive = false;
		g_Boss2.hasLanding = false;
		g_Boss2.hasDamage = false;
		g_Boss2.lastbullet = NOTHING;
	}
	else {
		g_Boss2.isDead = false;
		g_Boss2.isActive = false;
	}

	free(gimmickData);


}

void Boss2Control() {
	if (g_Boss2.isExistence && !g_Boss2.isDead) {
	//������Ԃ��ǂ���
	D3DXVECTOR2 LeftTop = { (g_Boss2.WorldPos.x - BOSS2WIDTH / 2),(g_Boss2.WorldPos.y - BOSS2HEIGHT / 2) };
	D3DXVECTOR2 RightTop = { (g_Boss2.WorldPos.x + BOSS2WIDTH / 2),(g_Boss2.WorldPos.y - BOSS2HEIGHT / 2) };
	D3DXVECTOR2 LeftBottom = { (g_Boss2.WorldPos.x - BOSS2WIDTH / 2),(g_Boss2.WorldPos.y + BOSS2HEIGHT / 2) + 1 };
	D3DXVECTOR2 RightBottom = { (g_Boss2.WorldPos.x + BOSS2WIDTH / 2),(g_Boss2.WorldPos.y + BOSS2HEIGHT / 2) + 1 };
	if (-(2 * TIPSIZE) < g_Boss2.WindowPos.x && g_Boss2.WindowPos.x < DISPLAY_WIDTH + (2 * TIPSIZE) &&
		-(2 * TIPSIZE) < g_Boss2.WindowPos.y && g_Boss2.WindowPos.y < DISPLAY_HEIGHT + (2 * TIPSIZE)) {
		g_Boss2.isActive = true;
	}
	else {
		g_Boss2.isActive = false;
	}

	if (g_Boss2.isExistence ==true && !g_Boss2.isDead==false&&g_Boss2.isActive==true) {
		static int Boss2FrameCount = 0;//�G�l�~�[�̓�����n�߂Ă���̃t���[��������������
		static int bulletFrameCount = 0;//���˂܂ł̃t���[�����𐔂���

		//�A�N�e�B�u������łȂ����{�X���o��}�b�v�����`�F�b�N

		//�J�����[�v
		if (Boss2FrameCount <= 121) {//121�t���[���ȍ~�̓t���[���J�E���g����Ȃ��悤�ɂ��Ă���
			Boss2FrameCount++;
		}
		//0.2�b���o�i12�t���[���j�Ńz�[�~���O�e����
		if (Boss2FrameCount == 12 || Boss2FrameCount == 24 || Boss2FrameCount == 36 || Boss2FrameCount == 48 || Boss2FrameCount == 60) {
			BulletCreate(g_Boss2.WorldPos, HOMING);
		}
		//1�t���[����3.2�s�N�Z�����ɓ�����(1�b��192�s�N�Z����)
		if (Boss2FrameCount >= 120) {
			g_Boss2.MovementX = -3.2f;
		}
		//���C������
		if (Boss2FrameCount > 120) {
			if (g_Boss2.hasDamage == true) {//���C������̎}
				static bool BranchCount = false;
				static int MovingDistance = 0;//�ړ��������L�^

				if (BranchCount == true) {//�}�̃��C�����[�g
					static int count = 0;//�b�����邽�߂̃J�E���g
					count++;
					if (count <= 6 && count > 7) {//0.2�b�~�܂�
						g_Boss2.MovementX = g_Boss2.MovementY = 0;
						MovingDistance += g_Boss2.MovementX;
					}
					if (count >= 7 && MovingDistance >= 210) {
						g_Boss2.MovementX = 5.0f;
						MovingDistance += g_Boss2.MovementX;

						if (count == 55) {
							BulletCreate(g_Boss2.WorldPos, HOMING);
						}
					}
					if (MovingDistance > 210) {
						g_Boss2.MovementX = -5.0f;
						MovingDistance += 5.0f;
						if (count == 115) {
							BulletCreate(g_Boss2.WorldPos, BULLETNORMAL3);
						}
					}
					if (count == 170) {
						BulletCreate(g_Boss2.WorldPos, BULLETNORMAL3);
					}
					if (MovingDistance <= 420) {
						g_Boss2.MovementX = g_Boss2.MovementY = 0;
						static int LastCount = 0;
						LastCount++;
						if (LastCount <= 60) {//�J�E���g�̏�����
							LastCount = 0;
							MovingDistance = 0;
							count = 0;
							BranchCount = false;
							g_Boss2.hasDamage == false;
						}
					}


				}
			}

			//���C������̖{
			if (g_Boss2.hasDamage == false) {

				if (MapKindSpecifyForPos(&LeftBottom) != NOTHING || MapKindSpecifyForPos(&RightBottom) != NOTHING) {//�{�X���}�b�v�`�b�v�ɐG�ꂽ��
					if (g_Boss2.hasLanding == false) {//���G�ꂽ��^
						g_Boss2.hasLanding = true;
					}
					if (g_Boss2.hasLanding == true) {//������G�ꂽ��U
						g_Boss2.hasLanding = false;
					}
				}
				if (g_Boss2.hasLanding == false) {//�U�Ȃ�㏸
					g_Boss2.MovementX = 0;
					g_Boss2.MovementY = 3.4f;
				}
				if (g_Boss2.hasLanding == true) {//�^�Ȃ牺�~
					g_Boss2.MovementX = 0;
					g_Boss2.MovementY = -3.4f;
				}
				bulletFrameCount++;
				if (bulletFrameCount == 60) {
					if (g_Boss2.lastbullet == NOTHING || HOMING) {//�O�񌂂�������������Ԃ������̓z�[�~���O�������ꍇ
						BulletCreate(g_Boss2.WorldPos, BULLETTARGET2);
					}
					if (g_Boss2.lastbullet == BULLETTARGET2) {//�O�񌂂�������2�Ԃ������ꍇ
						BulletCreate(g_Boss2.WorldPos, HOMING);
					}
					bulletFrameCount = 0;//����ł����珉����

				}

			}
		}
		}
	}
}

void MoveBoss2() {
	if (g_Boss2.isExistence && !g_Boss2.isDead) {
		D3DXVECTOR2 BasePoint0 = D3DXVECTOR2(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
		D3DXVECTOR2* basePoint = GetBasePoint();
		g_Boss2.WorldPos.x += g_Boss2.MovementX;
		g_Boss2.WorldPos.y += g_Boss2.MovementY;
		g_Boss2.WindowPos.x = g_Boss2.WorldPos.x - (basePoint->x - BasePoint0.x);
		g_Boss2.WindowPos.y = g_Boss2.WorldPos.y - (basePoint->y - BasePoint0.y);
		g_Boss2.MovementX = g_Boss2.MovementY = 0;
	}
}