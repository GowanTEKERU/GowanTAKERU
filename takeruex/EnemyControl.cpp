#include"EnemyControl.h"
#include"EnemyRender.h"
#include"MapRender.h"
#include"MapControl.h"
#include"CommonRender.h"
#include"CommonControl.h"
#include"MainControl.h"
#include"PlayerRender.h"
#include"PlayerControl.h"
#include "BulletControl.h"
#include "FileManagement.h"

//�v���g�^�C�v�Q
void SetEnemyData(int maxX, int maxY, int* pGimmickData);
void EnemyPursuit(int enemyNum);

Enemy* g_pEnemy;//

int g_EnemyMaxCount = 0;

Enemy* GetEnemyData() {//
	return g_pEnemy;
}

void FreeEnemyData() {
	free(g_pEnemy);
}

int GetEnemyMax() {
	return g_EnemyMaxCount;
}

void CountEnemy(int maxX,int maxY,int* pGimmickData) {

	g_EnemyMaxCount = 0;

	for (int i = 0; i < maxY; i++) {
		for (int j = 0; j < maxX; j++) {

			switch (pGimmickData[j + i*maxX]) {
			case WALKINGENEMY_1:
			case WALKINGENEMY_2:
			case WALKINGENEMY_3:
			case WALKINGENEMY_4:
			case WALKINGENEMY_5:
			case WALKINGENEMY_HAS_KEY_1:
			case WALKINGENEMY_HAS_KEY_2:
			case WALKINGENEMY_HAS_KEY_3:
			case FLYINGENEMY1:
			case FLYINGENEMY2:
			case FLYINGENEMY3:
			case FLYINGENEMY4:
			case FLYINGENEMY5:
			case FLYINGENEMY_HAS_KEY1:
			case FLYINGENEMY_HAS_KEY2:
			case FLYINGENEMY_HAS_KEY3:
			case FIXEDBATTERY1:
			case FIXEDBATTERY2:
				g_EnemyMaxCount++;
				break;
			}
		}
	}
	g_EnemyMaxCount++;
}

void EnemyInit() {

	STAGE_ID stage_ID = GetStage_ID();
	int maxX = GetStageXYMAX(stage_ID, X);
	int maxY = GetStageXYMAX(stage_ID, Y);
	int* pGimmickData = (int*)malloc(sizeof(int)*maxX*maxY);
	switch (stage_ID) {
	case STAGE_1:
		CSVLoad("CSV/mainscene/stage1_gimmick.csv", pGimmickData, maxY, maxX);
		break;

	case STAGE_2:
		CSVLoad("CSV/mainscene/stage2_gimmick.csv", pGimmickData, maxY, maxX);
		break;

	case STAGE_3:
		CSVLoad("CSV/mainscene/stage3_gimmick.csv", pGimmickData, maxY, maxX);
		break;

	case STAGE_4:
		CSVLoad("CSV/mainscene/stage4_gimmick.csv", pGimmickData, maxY, maxX);
		break;
	}

	CountEnemy(maxX, maxY, pGimmickData);

	//g_pEnemy�𖂃��b�N
	g_pEnemy = (Enemy*)malloc(sizeof(Enemy)*g_EnemyMaxCount);

	SetEnemyData(maxX, maxY, pGimmickData);
	free(pGimmickData);
}

void EnemyControl() {

	D3DXVECTOR2* basepoint = GetBasePoint();
	D3DXVECTOR2 BasePoint0 = D3DXVECTOR2(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);

	int enemyMax = GetEnemyMax();
	for (int i = 0; i < enemyMax; i++) {
		if (g_pEnemy[i].beDead == false) {

			g_pEnemy[i].WindowPos.x = g_pEnemy[i].WorldPos.x - (basepoint->x - BasePoint0.x);
			g_pEnemy[i].WindowPos.y = g_pEnemy[i].WorldPos.y - (basepoint->y - BasePoint0.y);

			//�E�B���h�E�̊O�i���E�j120�s�N�Z������`��J�n�̃t���O�𗧂Ă�
			if (-(2 * TIPSIZE) < g_pEnemy[i].WindowPos.x && g_pEnemy[i].WindowPos.x < DISPLAY_WIDTH + (2 * TIPSIZE) &&
				-(2 * TIPSIZE) < g_pEnemy[i].WindowPos.y && g_pEnemy[i].WindowPos.y < DISPLAY_HEIGHT + (2 * TIPSIZE)) {
				g_pEnemy[i].beActive = true;
			}
			else {
				g_pEnemy[i].beActive = false;
			}

			if (g_pEnemy[i].beActive == true && g_pEnemy[i].beDead == false) {
				EnemyPursuit(i);
				g_pEnemy[i].bulletFrameCount++;
				if (g_pEnemy[i].bulletFrameCount == g_pEnemy[i].firingInterval) {//�G�l�~�[���Ɏ����Ă��锭�ˊ��o�ɂȂ��������
					if (g_pEnemy[i].enemyKind == FLYINGENEMY1) {//���˂݁[�J�C���h���Ƃɓ���Ƃ��낪�Ⴄ�i�łe���Ⴄ
						BulletCreate(g_pEnemy[i].WorldPos, BULLETTARGET1);
					}
					if (g_pEnemy[i].enemyKind == WALKINGENEMY_1 || WALKINGENEMY_2||WALKINGENEMY_6||
						FLYINGENEMY1||FLYINGENEMY4|| FIXEDBATTERY1) {
						BulletCreate(g_pEnemy[i].WorldPos, BULLETTARGET2);
					}
					if (g_pEnemy[i].enemyKind == FIXEDBATTERY2) {
						BulletCreate(g_pEnemy[i].WorldPos, BULLETTARGET3);
					}
					if (g_pEnemy[i].enemyKind == WALKINGENEMY_5) {
						BulletCreate(g_pEnemy[i].WorldPos, BULLETTARGET4);
					}
					if (g_pEnemy[i].enemyKind == WALKINGENEMY_3) {
						BulletCreate(g_pEnemy[i].WorldPos, HOMING);
					}
					if(g_pEnemy[i].bulletFrameCount == g_pEnemy[i].firingInterval+30) {
						g_pEnemy[i].bulletFrameCount = 0;
					}
				}
			}
		}
	}
}


void EnemyPursuit(int enemyNum) {
	Player* player = GetplayerData();
	D3DXVECTOR2* basepoint = GetBasePoint();
	switch (g_pEnemy[enemyNum].enemyKind) {
	case WALKINGENEMY_1:
	case WALKINGENEMY_6:
		if (g_pEnemy[enemyNum].WindowPos.x > basepoint->x) {
			g_pEnemy[enemyNum].beLeft = false;
		}
		if (g_pEnemy[enemyNum].WindowPos.x < basepoint->x) {
			g_pEnemy[enemyNum].beLeft = true;
		}

		if (g_pEnemy[enemyNum].bulletFrameCount < g_pEnemy[enemyNum].firingInterval - 30) {//�e���˃t���[�����-5�t���[�������������璆�ɓ���
																						  //�G�l�~�[��X���W���v���C���[��X���W��菬����������
			if (player->WindowPos.x < g_pEnemy[enemyNum].WindowPos.x) {
				//+�����ɃG�l�~�[�𓮂���
				g_pEnemy[enemyNum].MovementX = -g_pEnemy[enemyNum].Speed;
			}
			//�G�l�~�[��X���W���v���C���[��X���W���傫��������
			else if (player->WindowPos.x > g_pEnemy[enemyNum].WindowPos.x) {
				//-�����ɃG�l�~�[�𓮂���
				g_pEnemy[enemyNum].MovementX = g_pEnemy[enemyNum].Speed;
			}
		}
		if (g_pEnemy[enemyNum].bulletFrameCount >= g_pEnemy[enemyNum].firingInterval - 30) {//���˃t���[����-5�t���[���ȏ゠��Β��ɓ���
			g_pEnemy[enemyNum].MovementX = 0;
			g_pEnemy[enemyNum].MovementY = 0;
			if (g_pEnemy[enemyNum].bulletFrameCount == g_pEnemy[enemyNum].firingInterval+30) {
				g_pEnemy[enemyNum].bulletFrameCount = 0;
			}
		}
		g_pEnemy[enemyNum].MovementY = ENEMYGRAVITY;

		break;
	case WALKINGENEMY_2:
		if (g_pEnemy[enemyNum].WindowPos.x > basepoint->x) {
			g_pEnemy[enemyNum].beLeft = false;
		}
		if (g_pEnemy[enemyNum].WindowPos.x < basepoint->x) {
			g_pEnemy[enemyNum].beLeft = true;
		}
		g_pEnemy[enemyNum].MovementX = 0;
		g_pEnemy[enemyNum].MovementY = 0;
		break;
	case WALKINGENEMY_3:
		if (g_pEnemy[enemyNum].WindowPos.x > basepoint->x) {
			g_pEnemy[enemyNum].beLeft = false;
		}
		if (g_pEnemy[enemyNum].WindowPos.x < basepoint->x) {
			g_pEnemy[enemyNum].beLeft = true;
		}
		g_pEnemy[enemyNum].MovementX = 0;
		g_pEnemy[enemyNum].MovementY = 0;
		break;
	case WALKINGENEMY_4://�̓�����
		static bool attack;
		attack = false;
		g_pEnemy[enemyNum].beLeft = false;
		if (g_pEnemy[enemyNum].EnemyBasePoint.x-400 <= basepoint->x) {//PC���͈͓��ɓ�������t���O����
			attack = true;
		}
		if (g_pEnemy[enemyNum].WorldPos.x <= g_pEnemy[enemyNum].EnemyBasePoint.x - 400){//�͈͂ɓ���܂�OF
			 attack = false;
		}
		if (attack == true) {//�t���OON�Ȃ�SPEED---
			g_pEnemy[enemyNum].MovementX = -7;
			g_pEnemy[enemyNum].MovementY = 0;
		}
		if (g_pEnemy[enemyNum].WorldPos.x <= g_pEnemy[enemyNum].EnemyBasePoint.x-400) {//�G���ړ������������t���OOF
			attack == false;
		}
		if (attack == false) {
			g_pEnemy[enemyNum].MovementX = 0;
			g_pEnemy[enemyNum].MovementY = 0;
		}
		break;
	case WALKINGENEMY_5:
		if (g_pEnemy[enemyNum].WindowPos.x > basepoint->x) {
			g_pEnemy[enemyNum].beLeft = false;
		}
		if (g_pEnemy[enemyNum].WindowPos.x < basepoint->x) {
			g_pEnemy[enemyNum].beLeft = true;
		}
		g_pEnemy[enemyNum].MovementX = 0;
		g_pEnemy[enemyNum].MovementY = 0;
		break;
	case WALKINGENEMY_HAS_KEY_1:
		if (g_pEnemy[enemyNum].WindowPos.x > basepoint->x) {
			g_pEnemy[enemyNum].beLeft = false;
		}
		if (g_pEnemy[enemyNum].WindowPos.x < basepoint->x) {
			g_pEnemy[enemyNum].beLeft = true;
		}
		g_pEnemy[enemyNum].MovementX = 0;
		g_pEnemy[enemyNum].MovementY = 0;
		break;
	case WALKINGENEMY_HAS_KEY_2:
		if (g_pEnemy[enemyNum].WindowPos.x > basepoint->x) {
			g_pEnemy[enemyNum].beLeft = false;
		}
		if (g_pEnemy[enemyNum].WindowPos.x < basepoint->x) {
			g_pEnemy[enemyNum].beLeft = true;
		}

		if (g_pEnemy[enemyNum].bulletFrameCount < g_pEnemy[enemyNum].firingInterval - 30) {//�e���˃t���[�����-5�t���[�������������璆�ɓ���
																						  //�G�l�~�[��X���W���v���C���[��X���W��菬����������
			if (player->WindowPos.x < g_pEnemy[enemyNum].WindowPos.x) {
				//+�����ɃG�l�~�[�𓮂���
				g_pEnemy[enemyNum].MovementX = -g_pEnemy[enemyNum].Speed;
			}
			//�G�l�~�[��X���W���v���C���[��X���W���傫��������
			else if (player->WindowPos.x > g_pEnemy[enemyNum].WindowPos.x) {
				//-�����ɃG�l�~�[�𓮂���
				g_pEnemy[enemyNum].MovementX = g_pEnemy[enemyNum].Speed;
			}
		}
		if (g_pEnemy[enemyNum].bulletFrameCount >= g_pEnemy[enemyNum].firingInterval - 30) {//���˃t���[����-5�t���[���ȏ゠��Β��ɓ���
			g_pEnemy[enemyNum].MovementX = 0;
			g_pEnemy[enemyNum].MovementY = 0;
			if (g_pEnemy[enemyNum].bulletFrameCount == g_pEnemy[enemyNum].firingInterval+30) {
				g_pEnemy[enemyNum].bulletFrameCount = 0;
			}
		}
		g_pEnemy[enemyNum].MovementY = ENEMYGRAVITY;

		break;
	case WALKINGENEMY_HAS_KEY_3:
		break;
	case FLYINGENEMY1:
		if (g_pEnemy[enemyNum].bulletFrameCount < g_pEnemy[enemyNum].firingInterval - 30) {//�e���˃t���[�����-30�t���[�������������璆�ɓ���
																						  //�G�l�~�[��X���W���v���C���[��X���W+200�̈ʒu���傫��������
			if (player->WindowPos.x + 200 < g_pEnemy[enemyNum].WindowPos.x) {
				//+�����ɃG�l�~�[�𓮂���
				g_pEnemy[enemyNum].MovementX -= -g_pEnemy[enemyNum].Speed;
			}
			//�G�l�~�[��X���W���v���C���[��X���W-200�̈ʒu��菬����������
			if (player->WindowPos.x - 200 > g_pEnemy[enemyNum].WindowPos.x) {
				//+�����ɃG�l�~�[�𓮂���
				g_pEnemy[enemyNum].MovementX = g_pEnemy[enemyNum].Speed;
			}
		}

		if (g_pEnemy[enemyNum].bulletFrameCount >= g_pEnemy[enemyNum].firingInterval - 30){//���˃t���[����-30�t���[���ȏ゠��Β��ɓ���
			g_pEnemy[enemyNum].MovementX = 0;
			g_pEnemy[enemyNum].MovementY = 0;
			if (g_pEnemy[enemyNum].bulletFrameCount == g_pEnemy[enemyNum].firingInterval + 30) {
				g_pEnemy[enemyNum].bulletFrameCount = 0;
			}
		}
		break;
	case FLYINGENEMY2:
		if (g_pEnemy[enemyNum].WindowPos.x > basepoint->x) {
			g_pEnemy[enemyNum].beLeft = false;
		}
		if (g_pEnemy[enemyNum].WindowPos.x < basepoint->x) {
			g_pEnemy[enemyNum].beLeft = true;
		}
		g_pEnemy[enemyNum].MovementX = 0;
		g_pEnemy[enemyNum].MovementY = 0;
		break;
	case FLYINGENEMY3:
		break;//����
	case FLYINGENEMY4:
		if (g_pEnemy[enemyNum].bulletFrameCount < g_pEnemy[enemyNum].firingInterval - 30) {//�e���˃t���[�����-5�t���[�������������璆�ɓ���
																						   //�G�l�~�[��X���W���v���C���[��X���W+200�̈ʒu���傫��������
			if (player->WindowPos.x + 200 < g_pEnemy[enemyNum].WindowPos.x) {
				//+�����ɃG�l�~�[�𓮂���
				g_pEnemy[enemyNum].MovementX -= -g_pEnemy[enemyNum].Speed;
			}
			//�G�l�~�[��X���W���v���C���[��X���W-200�̈ʒu��菬����������
			if (player->WindowPos.x - 200 > g_pEnemy[enemyNum].WindowPos.x) {
				//+�����ɃG�l�~�[�𓮂���
				g_pEnemy[enemyNum].MovementX = g_pEnemy[enemyNum].Speed;
			}
		}

		if (g_pEnemy[enemyNum].bulletFrameCount >= g_pEnemy[enemyNum].firingInterval - 30) {//���˃t���[����-5�t���[���ȏ゠��Β��ɓ���
			g_pEnemy[enemyNum].MovementX = 0;
			g_pEnemy[enemyNum].MovementY = 0;
			if (g_pEnemy[enemyNum].bulletFrameCount == g_pEnemy[enemyNum].firingInterval + 30) {
				g_pEnemy[enemyNum].bulletFrameCount = 0;
			}
		}
		break;
	case FLYINGENEMY5:
		break;//����
	case FLYINGENEMY_HAS_KEY1:
		if (g_pEnemy[enemyNum].bulletFrameCount < g_pEnemy[enemyNum].firingInterval - 30) {//�e���˃t���[�����-30�t���[�������������璆�ɓ���
																						   //�G�l�~�[��X���W���v���C���[��X���W+200�̈ʒu���傫��������
			if (player->WindowPos.x + 200 < g_pEnemy[enemyNum].WindowPos.x) {
				//+�����ɃG�l�~�[�𓮂���
				g_pEnemy[enemyNum].MovementX -= -g_pEnemy[enemyNum].Speed;
			}
			//�G�l�~�[��X���W���v���C���[��X���W-200�̈ʒu��菬����������
			if (player->WindowPos.x - 200 > g_pEnemy[enemyNum].WindowPos.x) {
				//+�����ɃG�l�~�[�𓮂���
				g_pEnemy[enemyNum].MovementX = g_pEnemy[enemyNum].Speed;
			}
		}

		if (g_pEnemy[enemyNum].bulletFrameCount >= g_pEnemy[enemyNum].firingInterval - 30) {//���˃t���[����-30�t���[���ȏ゠��Β��ɓ���
			g_pEnemy[enemyNum].MovementX = 0;
			g_pEnemy[enemyNum].MovementY = 0;
			if (g_pEnemy[enemyNum].bulletFrameCount == g_pEnemy[enemyNum].firingInterval + 30) {
				g_pEnemy[enemyNum].bulletFrameCount = 0;
			}
		}
		break;
	case FLYINGENEMY_HAS_KEY2:
		break;
	case FLYINGENEMY_HAS_KEY3:
	case FIXEDBATTERY1:
	case FIXEDBATTERY2:
		g_pEnemy[enemyNum].beLeft = false;
		g_pEnemy[enemyNum].MovementX = 0;
		g_pEnemy[enemyNum].MovementY = 0;
		break;
	case SWITCH_1:
	case SWITCH_2:
	case SWITCH_3:
		g_pEnemy[enemyNum].beLeft = false;
		g_pEnemy[enemyNum].MovementX = 0;
		g_pEnemy[enemyNum].MovementY = 0;
		break;


	}


	
}

void MoveEnemy() {
	int enemyMax = GetEnemyMax();
	for (int i = 0; i < enemyMax; i++) {
		//�v���C���[�����E�ǂ����ɂ���̂����Č�����ς���
		if (g_pEnemy[i].beActive == true && g_pEnemy[i].beDead == false) {//�f�X�A�A�N�e�B�u�`�F�b�N
			//�e�G�l�~�[�̍��W�ɓ����l�𑫂�
			g_pEnemy[i].WorldPos.x += g_pEnemy[i].MovementX;
			g_pEnemy[i].WorldPos.y += g_pEnemy[i].MovementY;
			g_pEnemy[i].WindowPos.x += g_pEnemy[i].MovementX;
			g_pEnemy[i].WindowPos.y += g_pEnemy[i].MovementY;

			//Movement�̏�����
			g_pEnemy[i].MovementX = 0;
			g_pEnemy[i].MovementY = 0;
		}
		
	 }
}

void SetEnemyData(int maxX,int maxY, int* pGimmickData) {

	int enemyCount = 0;

	for (int i = 0; i < maxY; i++) {
		for (int j = 0; j < maxX; j++) {

			g_pEnemy[enemyCount].enemyKind = NOTHING;

			switch (pGimmickData[j + i*maxX]) {//��������G�̃f�[�^����ꍞ��

			case WALKINGENEMY_HAS_KEY_1:
				g_pEnemy[enemyCount].enemyKind = WALKINGENEMY_HAS_KEY_1;
				g_pEnemy[enemyCount].Speed = 1;
				g_pEnemy[enemyCount].firingInterval = 200;
				g_pEnemy[enemyCount].Height = 118.0f;
				g_pEnemy[enemyCount].Width = 68.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case WALKINGENEMY_HAS_KEY_2:
				g_pEnemy[enemyCount].enemyKind = WALKINGENEMY_HAS_KEY_2;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 200;
				g_pEnemy[enemyCount].Height = 118.0f;
				g_pEnemy[enemyCount].Width = 68.0f;
				g_pEnemy[enemyCount].Atk = 30;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case WALKINGENEMY_HAS_KEY_3://����
				g_pEnemy[enemyCount].enemyKind = WALKINGENEMY_HAS_KEY_3;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 200;
				g_pEnemy[enemyCount].Height = 118.0f;
				g_pEnemy[enemyCount].Width = 68.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case WALKINGENEMY_1:
				g_pEnemy[enemyCount].enemyKind = WALKINGENEMY_1;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 3*60;
				g_pEnemy[enemyCount].Height = 118.0f;
				g_pEnemy[enemyCount].Width = 68.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case WALKINGENEMY_2:
				g_pEnemy[enemyCount].enemyKind = WALKINGENEMY_2;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 5*60;
				g_pEnemy[enemyCount].Height = 118.0f;
				g_pEnemy[enemyCount].Width = 68.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case WALKINGENEMY_3:
				g_pEnemy[enemyCount].enemyKind = WALKINGENEMY_3;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 4*60;
				g_pEnemy[enemyCount].Height = 118.0f;
				g_pEnemy[enemyCount].Width = 68.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case WALKINGENEMY_4:
				g_pEnemy[enemyCount].enemyKind = WALKINGENEMY_4;
				g_pEnemy[enemyCount].Speed = 7;
				g_pEnemy[enemyCount].firingInterval = 4*60;
				g_pEnemy[enemyCount].Height = 118.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case WALKINGENEMY_5:
				g_pEnemy[enemyCount].enemyKind = WALKINGENEMY_5;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 4*60;
				g_pEnemy[enemyCount].Height = 118.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case WALKINGENEMY_6:
				g_pEnemy[enemyCount].enemyKind = WALKINGENEMY_6;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 4 * 60;
				g_pEnemy[enemyCount].Height = 118.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 20;
				break;

			case FLYINGENEMY_HAS_KEY1://����
				g_pEnemy[enemyCount].enemyKind = FLYINGENEMY_HAS_KEY1;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 200;
				g_pEnemy[enemyCount].Height = 88.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 1;
				break;

			case FLYINGENEMY_HAS_KEY2:
				g_pEnemy[enemyCount].enemyKind = FLYINGENEMY_HAS_KEY2;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 200;
				g_pEnemy[enemyCount].Height = 88.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case FLYINGENEMY_HAS_KEY3://����
				g_pEnemy[enemyCount].enemyKind = FLYINGENEMY_HAS_KEY3;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 200;
				g_pEnemy[enemyCount].Height = 88.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 1;
				break;

			case FLYINGENEMY1:
				g_pEnemy[enemyCount].enemyKind = FLYINGENEMY1;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 4*60;
				g_pEnemy[enemyCount].Height = 88.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case FLYINGENEMY2:
				g_pEnemy[enemyCount].enemyKind = FLYINGENEMY2;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 4*60;
				g_pEnemy[enemyCount].Height = 88.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 10;
				break;

			case FLYINGENEMY3://����
				g_pEnemy[enemyCount].enemyKind = FLYINGENEMY3;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 200;//?
				g_pEnemy[enemyCount].Height = 88.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 1;//?
				break;

			case FLYINGENEMY4:
				g_pEnemy[enemyCount].enemyKind = FLYINGENEMY4;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 4*60;
				g_pEnemy[enemyCount].Height = 88.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 20;
				break;

			case FLYINGENEMY5://����
				g_pEnemy[enemyCount].enemyKind = FLYINGENEMY5;
				g_pEnemy[enemyCount].Speed = 3;
				g_pEnemy[enemyCount].firingInterval = 200;//?
				g_pEnemy[enemyCount].Height = 88.0f;
				g_pEnemy[enemyCount].Width = 100.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 1;//?
				break;

			case FIXEDBATTERY1:
				g_pEnemy[enemyCount].enemyKind = FIXEDBATTERY1;
				g_pEnemy[enemyCount].Speed = 0;
				g_pEnemy[enemyCount].firingInterval = 4*60;
				g_pEnemy[enemyCount].Height = 60.0f;
				g_pEnemy[enemyCount].Width = 60.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 2147483647;
				break;

			case FIXEDBATTERY2:
				g_pEnemy[enemyCount].enemyKind = FIXEDBATTERY2;
				g_pEnemy[enemyCount].Speed = 0;
				g_pEnemy[enemyCount].firingInterval =  5*60;
				g_pEnemy[enemyCount].Height = 60.0f;
				g_pEnemy[enemyCount].Width = 60.0f;
				g_pEnemy[enemyCount].Atk = 20;
				g_pEnemy[enemyCount].Hp = 2147483647;
				break;

			case SWITCH_1:
				g_pEnemy[enemyCount].enemyKind = SWITCH_1;
				g_pEnemy[enemyCount].Speed = 0;
				g_pEnemy[enemyCount].firingInterval = 5 * 60;
				g_pEnemy[enemyCount].Height = 70.0f;
				g_pEnemy[enemyCount].Width = 38.0f;
				g_pEnemy[enemyCount].Atk = 0;
				g_pEnemy[enemyCount].Hp = 2147483647;
				break;

			case SWITCH_2:
				g_pEnemy[enemyCount].enemyKind = SWITCH_2;
				g_pEnemy[enemyCount].Speed = 0;
				g_pEnemy[enemyCount].firingInterval = 5 * 60;
				g_pEnemy[enemyCount].Height = 70.0f;
				g_pEnemy[enemyCount].Width = 38.0f;
				g_pEnemy[enemyCount].Atk = 0;
				g_pEnemy[enemyCount].Hp = 2147483647;
				break;

			case SWITCH_3:
				g_pEnemy[enemyCount].enemyKind = SWITCH_3;
				g_pEnemy[enemyCount].Speed = 0;
				g_pEnemy[enemyCount].firingInterval = 5 * 60;
				g_pEnemy[enemyCount].Height = 70.0f;
				g_pEnemy[enemyCount].Width = 38.0f;
				g_pEnemy[enemyCount].Atk = 0;
				g_pEnemy[enemyCount].Hp = 2147483647;
				break;
			}

			if (g_pEnemy[enemyCount].enemyKind != NOTHING) {
				g_pEnemy[enemyCount].WorldPos.x = j*TIPSIZE;
				g_pEnemy[enemyCount].WorldPos.y = i*TIPSIZE;
				g_pEnemy[enemyCount].WindowPos.x = 0;
				g_pEnemy[enemyCount].WindowPos.y = 0;
				g_pEnemy[enemyCount].MovementX = g_pEnemy[enemyCount].MovementY = 0;
				g_pEnemy[enemyCount].bulletFrameCount = 0;
				g_pEnemy[enemyCount].beDead = false;//����ł��邩
				g_pEnemy[enemyCount].beActive = false;//��������
				g_pEnemy[enemyCount].beLeft = false;//���i�E�j�ǂ����������Ă邩
				g_pEnemy[enemyCount].EnemyBasePoint.x = g_pEnemy[enemyCount].WorldPos.x;//�G�l�~�[�̏������W
				g_pEnemy[enemyCount].EnemyBasePoint.y = g_pEnemy[enemyCount].WorldPos.y;
				enemyCount++;

			}
		}
	}
}