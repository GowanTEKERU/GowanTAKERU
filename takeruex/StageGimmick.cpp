#include"StageGimmick.h"
#include"StageSelect.h"
#include"PlayerControl.h"
#include"FileManagement.h"
#include"MapRender.h"
#include"CommonRender.h"
#include"MapControl.h"
#include"BulletControl.h"
#include"EnemyControl.h"

#define KEYNUM_WALKINGENEMY_HAS_KEY_1_FLG	0x0001
#define KEYNUM_WALKINGENEMY_HAS_KEY_2_FLG	0x0002
#define KEYNUM_WALKINGENEMY_HAS_KEY_3_FLG	0x0004
#define KEYNUM_FLYINGENEMY_HAS_KEY1_FLG		0x0008
#define KEYNUM_FLYINGENEMY_HAS_KEY2_FLG		0x0010
#define KEYNUM_FLYINGENEMY_HAS_KEY3_FLG		0x0020

//プロトタイプ宣言
void OpenGate(int mapKind);

enum KEYNUM_KIND {
	KEYNUM_WALKINGENEMY_HAS_KEY_1,
	KEYNUM_WALKINGENEMY_HAS_KEY_2,
	KEYNUM_WALKINGENEMY_HAS_KEY_3,
	KEYNUM_FLYINGENEMY_HAS_KEY1,
	KEYNUM_FLYINGENEMY_HAS_KEY2,
	KEYNUM_FLYINGENEMY_HAS_KEY3,
	KEYNUM_KIND_MAX
};

int g_GateKeyNum[KEYNUM_KIND_MAX] = { 0 };


void StageGimmickInit() {

	for (int i = 0; i < KEYNUM_KIND_MAX; i++) {
		g_GateKeyNum[i] = 0;
	}
	
	//それぞれの敵のカギ持ちを数え、設定する
	Enemy* pEnemy = GetEnemyData();
	int enemyMax = GetEnemyMax();
	for (int i = 0; i < enemyMax; i++) {
		switch (pEnemy[i].enemyKind) {

		case WALKINGENEMY_HAS_KEY_1:
			g_GateKeyNum[KEYNUM_WALKINGENEMY_HAS_KEY_1]++;
			break;

		case WALKINGENEMY_HAS_KEY_2:
			g_GateKeyNum[KEYNUM_WALKINGENEMY_HAS_KEY_2]++;
			break;

		case WALKINGENEMY_HAS_KEY_3:
			g_GateKeyNum[KEYNUM_WALKINGENEMY_HAS_KEY_3]++;
			break;

		case FLYINGENEMY_HAS_KEY1:
			g_GateKeyNum[KEYNUM_FLYINGENEMY_HAS_KEY1]++;
			break;

		case FLYINGENEMY_HAS_KEY2:
			g_GateKeyNum[KEYNUM_FLYINGENEMY_HAS_KEY2]++;
			break;

		case FLYINGENEMY_HAS_KEY3:
			g_GateKeyNum[KEYNUM_FLYINGENEMY_HAS_KEY3]++;
			break;
		}
	}
}

void StageGimmickManage() {

	Enemy* pEnemy = GetEnemyData();

	int gateKeyNumCnt[KEYNUM_KIND_MAX] = { 0 };

	//敵の死んでいる鍵持ちの数を数える
	int enemyMax = GetEnemyMax();
	for (int i = 0; i < enemyMax; i++) {

		if (pEnemy[i].beDead) {
			switch (pEnemy[i].enemyKind)
			{
			case WALKINGENEMY_HAS_KEY_1:
				gateKeyNumCnt[KEYNUM_WALKINGENEMY_HAS_KEY_1]++;
				break;

			case WALKINGENEMY_HAS_KEY_2:
				gateKeyNumCnt[KEYNUM_WALKINGENEMY_HAS_KEY_2]++;
				break;

			case WALKINGENEMY_HAS_KEY_3:
				gateKeyNumCnt[KEYNUM_WALKINGENEMY_HAS_KEY_3]++;
				break;

			case FLYINGENEMY_HAS_KEY1:
				gateKeyNumCnt[KEYNUM_FLYINGENEMY_HAS_KEY1]++;
				break;

			case FLYINGENEMY_HAS_KEY2:
				gateKeyNumCnt[KEYNUM_FLYINGENEMY_HAS_KEY2]++;
				break;

			case FLYINGENEMY_HAS_KEY3:
				gateKeyNumCnt[KEYNUM_FLYINGENEMY_HAS_KEY3]++;
				break;
			}
		}
	}

	int gateflg = 0;

	//それぞれの設定された鍵持ちの数と死んでいる鍵持ちの数が一緒か調べ、同じならフラグを立てる
	for (int i = 0; i < KEYNUM_KIND_MAX; i++) {
		if (gateKeyNumCnt[i] == g_GateKeyNum[i]) {
			switch (i) {
			case KEYNUM_WALKINGENEMY_HAS_KEY_1:
				gateflg | KEYNUM_WALKINGENEMY_HAS_KEY_1_FLG;
				break;
			case KEYNUM_WALKINGENEMY_HAS_KEY_2:
				gateflg | KEYNUM_WALKINGENEMY_HAS_KEY_2_FLG;
				break;
			case KEYNUM_WALKINGENEMY_HAS_KEY_3:
				gateflg | KEYNUM_WALKINGENEMY_HAS_KEY_3_FLG;
				break;
			case KEYNUM_FLYINGENEMY_HAS_KEY1:
				gateflg | KEYNUM_FLYINGENEMY_HAS_KEY1_FLG;
				break;
			case KEYNUM_FLYINGENEMY_HAS_KEY2:
				gateflg | KEYNUM_FLYINGENEMY_HAS_KEY2_FLG;
				break;
			case KEYNUM_FLYINGENEMY_HAS_KEY3:
				gateflg | KEYNUM_FLYINGENEMY_HAS_KEY3_FLG;
				break;
			}
		}
	}

	//リンクさせる
	if (gateflg & KEYNUM_WALKINGENEMY_HAS_KEY_1_FLG) {
		OpenGate(SHUTTER_1);
	}
	if ((gateflg & KEYNUM_WALKINGENEMY_HAS_KEY_2_FLG) && (gateflg & KEYNUM_FLYINGENEMY_HAS_KEY2_FLG)) {
		OpenGate(SHUTTER_2);
	}
}


void OpenGate(int mapKind) {

	STAGE_ID stage_ID = GetStage_ID();
	STAGEXYMAX maxX = GetStageXYMAX(stage_ID, X);
	STAGEXYMAX maxY = GetStageXYMAX(stage_ID, Y);
	int* pGimmickData = (int*)malloc(sizeof(int)*maxX*maxY);

	CSVLoad("CSV/mainscene/stage1_gimmick.csv", pGimmickData, maxY, maxX);

	int* pMapData = GetMapData();

	for (int i = 0; i < maxY; i++) {
		for (int j = 0; j < maxX; j++) {
			if (*(pGimmickData + (i*maxX + j)) == mapKind) {
				*(pMapData + (i*maxX + j)) = NOTHING;
			}

		}
	}
}

//チェックポイントは必ず二つ
void ComeBackCheckPoint() {

	STAGE_ID stage_ID = GetStage_ID();
	STAGEXYMAX maxX = GetStageXYMAX(stage_ID, X);
	STAGEXYMAX maxY = GetStageXYMAX(stage_ID, Y);
	int* gimmickData = (int*)malloc(sizeof(int)*maxX*maxY);

	CSVLoad("CSV/mainscene/stage1_gimmick.csv", gimmickData, maxY, maxX);

	D3DXVECTOR2 pos[3];
	MapNumXY mapXY[3];
	for (int i = 0; i < maxY; i++) {
		for (int j = 0; j < maxX; j++) {
			if ((*(gimmickData + (i*maxX + j)) == CHECKPOINT_2)) {
				mapXY[2] = { j,i };
				PosSpecifyForMapchipNumber(&pos[2], &mapXY[2]);
			}
			if ((*(gimmickData + (i*maxX + j)) == CHECKPOINT_1)) {
				mapXY[1] = { j,i };
				PosSpecifyForMapchipNumber(&pos[1], &mapXY[1]);
			}
			if ((*(gimmickData + (i*maxX + j)) == START)) {
				mapXY[0] = { j,i };
				PosSpecifyForMapchipNumber(&pos[0], &mapXY[0]);
			}
		}
	}
	free(gimmickData);

	Player* player = GetplayerData();
	D3DXVECTOR2* basePoint = GetBasePoint();
	if (pos[2].x < player->WorldPos.x) {
		player->WorldPos = pos[2];
		mapXY[2].NumY -= 5;
		PosSpecifyForMapchipNumber(basePoint, &mapXY[2]);
	}
	else if (pos[1].x < player->WorldPos.x) {
		player->WorldPos = pos[1];
		mapXY[1].NumY -= 5;
		PosSpecifyForMapchipNumber(basePoint, &mapXY[1]);
	}
	else {
		player->WorldPos = pos[0];
		mapXY[0].NumY -= 5;
		PosSpecifyForMapchipNumber(basePoint, &mapXY[0]);
	}
	
	D3DXVECTOR2 BasePoint0 = D3DXVECTOR2(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
	player->WindowPos.x = player->WorldPos.x - (basePoint->x - BasePoint0.x);
	player->WindowPos.y = player->WorldPos.y - (basePoint->y - BasePoint0.y);

	EnemyInit();
	BulletInit();

	int* mapdata = GetMapData();
	CSVLoad("CSV/mainscene/stage1_map.csv", mapdata, maxY, maxX);
}