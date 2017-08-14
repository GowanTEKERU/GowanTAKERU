#include"Boss1.h"
#include"FileManagement.h"
#include"MapRender.h"
#include"PlayerControl.h"
#include"CommonRender.h"
#include"MainControl.h"
#include"BulletControl.h"

//�v���g�^�C�v�Q
BOSS1STATE DecidedBoss1State(float range, int bulletNum);
float CalculateNORMALSHOTDecidedValue(int bulletNum, float range);
float CalculateDUALSHOTDecidedValue(int bulletNum, float range);
float CalculateLARIATDecidedValue(float range);

Boss1Data g_Boss1;

Boss1Data* GetBoss1Data() {
	return &g_Boss1;
}

void Boss1Init() {

	STAGE_ID stage_ID = GetStage_ID();
	int MaxX = GetStageXYMAX(stage_ID, X);
	int MaxY = GetStageXYMAX(stage_ID, Y);
	int* gimmickData = (int*)malloc(sizeof(int)*MaxX*MaxY);

	switch (stage_ID) {
	case STAGE_1:
		CSVLoad("CSV/mainscene/stage1_gimmick.csv", gimmickData, MaxY, MaxX);//CSV�Ăяo��
		break;
	}

	for (int i = 0; i < MaxY; i++) {
		for (int j = 0; j < MaxX; j++) {
			if (gimmickData[j + i*MaxX] == BOSS_Stage1) {
				g_Boss1.isExistence = true;
				g_Boss1.WolrdPos.x = TIPSIZE*j;
				g_Boss1.WolrdPos.y = TIPSIZE*i;
				goto BREAK;
			}
		}
	}

BREAK:
	if (g_Boss1.isExistence) {
		g_Boss1.Boss1State = NON;
		g_Boss1.MovementX = g_Boss1.MovementY = 0;
		g_Boss1.a = g_Boss1.ga = 0;
		g_Boss1.Hp = 70;
		g_Boss1.saveShotFrmcnt = 0;
		g_Boss1.saveActionCntForNORMALSHOT = 0;
		g_Boss1.saveActionCntForDUALSHOT = 0;
		g_Boss1.saveDUALSHOTActionCntForLARIAT = 0;
		g_Boss1.isJumping = false;
		g_Boss1.isLeft = true;
		g_Boss1.isDead = true;
		g_Boss1.isActive = false;
	}

	free(gimmickData);
}

void Boss1Control() {
	
	if (g_Boss1.isExistence) {

		//������Ԃ��`�F�b�N
		D3DXVECTOR2 BasePoint0 = D3DXVECTOR2(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
		D3DXVECTOR2* basePoint = GetBasePoint();
		g_Boss1.WindowPos.x = g_Boss1.WolrdPos.x - (basePoint->x - BasePoint0.x);
		g_Boss1.WindowPos.y = g_Boss1.WolrdPos.y - (basePoint->y - BasePoint0.y);
		if (-(2 * TIPSIZE) < g_Boss1.WindowPos.x && g_Boss1.WindowPos.x < DISPLAY_WIDTH + (2 * TIPSIZE) &&
			-(2 * TIPSIZE) < g_Boss1.WindowPos.y && g_Boss1.WindowPos.y < DISPLAY_HEIGHT + (2 * TIPSIZE)) {
			g_Boss1.isActive = true;
		}
		else {
			g_Boss1.isActive = false;
		}

		//������Ԃł���
		if (g_Boss1.isActive) {

			//�m�o����
			Player* pPlayer = GetplayerData();
			Bullet* pBullet = GetBullet();

			float range = Calculate_distance(g_Boss1.WolrdPos.x, g_Boss1.WolrdPos.y, pPlayer->WorldPos.x, pPlayer->WorldPos.y);
			if (range < 0) {
				range *= -1;
			}
			
			int bulletNum = 0;

			for (int i = 0; i < BULLETNUMBER; i++) {
				if (pBullet[i].beActive) {
					bulletNum++;
				}
			}

			//�ӎv����
			g_Boss1.Boss1State = DecidedBoss1State(range, bulletNum);

			//�s��
			switch (g_Boss1.Boss1State) {
			case NORMALSHOT:

			}
		}
		
	}
}


BOSS1STATE DecidedBoss1State(float range, int bulletNum) {

	float DecidedValue[BOSS1STATE_MAX];

	DecidedValue[NORMALSHOT] = CalculateNORMALSHOTDecidedValue(bulletNum, range);

	DecidedValue[DUALSHOT]= CalculateDUALSHOTDecidedValue(bulletNum, range);

	DecidedValue[LARIAT]= CalculateLARIATDecidedValue(range);

	DecidedValue[NON] = ((100.0f - DecidedValue[NORMALSHOT]) + (100.0f - DecidedValue[NORMALSHOT]) + (100.0f - DecidedValue[LARIAT])) / 3;

	//�ł��傫���l������
	float* Max = &DecidedValue[NON];
	for (int i = 0; i < BOSS1STATE_MAX; i++) {
		if (*Max < DecidedValue[i]) {
			Max = &DecidedValue[i];
		}
	}

	BOSS1STATE boss1State = NON;
	if (Max == &DecidedValue[NON]) {
		boss1State = NON;
	}
	else if (Max == &DecidedValue[NORMALSHOT]) {
		boss1State = NORMALSHOT;
	}
	else if (Max == &DecidedValue[DUALSHOT]) {
		boss1State = DUALSHOT;
	}
	else if (Max == &DecidedValue[LARIAT]) {
		boss1State = LARIAT;
	}

	return boss1State;
}


float CalculateNORMALSHOTDecidedValue(int bulletNum, float range) {

	//�e�̔��ˊԊu�ɂ�锻��l�̌v�Z
	float decidedValue1 = (5.0f / 9.0f * g_Boss1.saveShotFrmcnt) - 100.0f;

	//��ʏ�̒e�̐��ɂ�锻��l�̌v�Z
	float decidedValue2 = -(bulletNum / 10.0f) + 100.0f;

	//�v���C���[�Ƃ̋����ɂ�锻��l�̌v�Z
	float decidedValue3 = (range - 700.0f) / 4900.0f + 100.0f;

	//�O���NORMALSHOT����̃A�N�V�������ɂ�锻��l�̌v�Z
	float decidedValue4 = 100.0f / (g_Boss1.saveActionCntForNORMALSHOT + 1.0f);

	//���ϒl�ɂ���ӂȒl�̌���
	float decidedValue = (decidedValue1 + decidedValue2 + decidedValue3 + decidedValue4) / 4;

	return decidedValue;
}


float CalculateDUALSHOTDecidedValue(int bulletNum, float range) {

	//�e�̔��ˊԊu�ɂ�锻��l�̌v�Z
	float decidedValue1 = (5.0f / 6.0f * g_Boss1.saveShotFrmcnt) - 200.0f;

	//��ʏ�̒e�̐��ɂ�锻��l�̌v�Z
	float decidedValue2 = -(bulletNum / 10.0f) + 100.0f;

	//�v���C���[�Ƃ̋����ɂ�锻��l�̌v�Z
	float decidedValue3 = (range - 600.0f) / 3600.0f + 100.0f;

	//�O���DUALSHOT����̃A�N�V�������ɂ�锻��l�̌v�Z
	float decidedValue4 = 100.0f / (g_Boss1.saveActionCntForDUALSHOT + 1.5f);

	//���ϒl�ɂ���ӂȒl�̌���
	float decidedValue = (decidedValue1 + decidedValue2 + decidedValue3 + decidedValue4) / 4;

	return decidedValue;
}

float CalculateLARIATDecidedValue(float range) {

	//���g�̗̑͂ɂ�锻��l�̌v�Z
	float decidedValue1 = -((float)pow((double)g_Boss1.Hp, 2) / 100.0f) + 100.0f;

	//�v���C���[�Ƃ̋����ɂ�锻��l�̌v�Z
	float decidedValue2 = -((float)pow((double)range, 2) / 16384.0f) + 100.0f;

	//�O���LARIAT�����DUALSHOT���ɂ�锻��l�̌v�Z
	float decidedValue3 = (20.0f*g_Boss1.saveDUALSHOTActionCntForLARIAT) - 100.0f;

	//���ϒl�ɂ���ӂȒl�̌���
	float decidedValue = (decidedValue1 + decidedValue2 + decidedValue3) / 3;

	return decidedValue;
}