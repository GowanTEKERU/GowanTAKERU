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
#include "MapRender.h"

EnemyMapDate g_EnemyMapDate;

EnemyMapDate* GetEnemyMapDate() {
	return &g_EnemyMapDate;
}

Enemy g_enemy[ENEMYNUMBER];
struct EnemyMapNum {//CSV�̍��W�Ɣԍ������锠
	int NumX;
	int NumY;

};

Enemy* GetenemyData() {
		return g_enemy;
	}

//�v���g�^�C�v�Q
void EnemyBulettCreate(int enemyNum);
void EnemyPursuit(int enemyNum);
void EnemyArrangement(EnemyMapNum enemyMapNum[]);

//void EnemyCSVInit() {
//	g_EnemyMapDate.MaxDate = 0;
//	g_EnemyMapDate.HasKeyDate = 0;
//
//	STAGE_ID stage_ID = GetStage_ID();
//	int MaxX = GetStageXYMAX(stage_ID, X);
//	int MaxY = GetStageXYMAX(stage_ID, Y);
//	int* enemyArrangement = (int*)malloc(sizeof(int)*MaxX*MaxY);
//
//	switch (stage_ID) {
//	case STAGE_1:
//		CSVLoad("CSV/mainscene/stage1_gimmick.csv", enemyArrangement, MaxY, MaxX);//CSV�Ăяo��
//		break;
//	}
//
//	int enemyMaxCount = 0;
//	int enemyHasKyeCount = 0;
//
//	for (int i = 0; i < MaxY; i++) {
//		for (int j = 0; j < MaxX; j++) {
//			switch (enemyArrangement[j + i*MaxX]) {
//			case WALKINGENEMY_HAS_KEY_2:
//			case FLYINGENEMY_HAS_KEY1:
//			case FLYINGENEMY_HAS_KEY2:
//				enemyHasKyeCount;
//			case WALKINGENEMY_1:
//			case FLYINGENEMY1:
//			case FIXEDBATTERY1:
//				enemyMaxCount++;
//				break;
//			default:
//				break;
//			}
//		}
//		g_EnemyMapDate.MaxDate = enemyMaxCount;
//		g_EnemyMapDate.HasKeyDate = enemyHasKyeCount;
//	}
//
//	free();
//
//
//}

void EnemyInit() {

	EnemyMapNum enemyMapNum[ENEMYNUMBER];
	EnemyArrangement(enemyMapNum);
	for (int i = 0; i < ENEMYNUMBER; i++) {
		g_enemy[i].WorldPos.x = enemyMapNum[i].NumX*TIPSIZE;//���[���h���W
		g_enemy[i].WorldPos.y = enemyMapNum[i].NumY*TIPSIZE;
		g_enemy[i].WindowPos.x = 0;
		g_enemy[i].WindowPos.y = 0;
		g_enemy[i].Atk = 20;//�U����
		g_enemy[i].Hp = 1;//�̗�
		g_enemy[i].bulletFrameCount = 0;
		g_enemy[i].beDead = false;//����ł��邩
		g_enemy[i].beActive = false;//��������
		g_enemy[i].beLeft = false;//���i�E�j�ǂ����������Ă邩

	}

}

void EnemyControl() {

	D3DXVECTOR2* basepoint = GetBasePoint();
	for (int i = 0; i < ENEMYNUMBER; i++) {
		if (g_enemy[i].beDead == false) {
			//�E�B���h�E�̊O�i���E�j120�s�N�Z������`��J�n�̃t���O�𗧂Ă�
			if (g_enemy[i].WorldPos.x < basepoint->x + DISPLAY_WIDTH / 2 + 120 && g_enemy[i].WorldPos.x > basepoint->x - DISPLAY_WIDTH / 2 - 120) {
				g_enemy[i].beActive = true;
			}
			if (g_enemy[i].beActive == true && g_enemy[i].beDead == false) {
				//�G�l�~�[�ƃx�[�X�|�C���g�Ƃ�world,X���W�̋����𒲂ׂ�
				float EnemyWorldDistanceX = g_enemy[i].WorldPos.x - basepoint->x;
				//�G�l�~�[�ƃx�[�X�|�C���g�Ƃ�world,Y���W�̋����𒲂ׂ�
				float EnemyWorldDistanceY = g_enemy[i].WorldPos.y - basepoint->y;
				//�G�l�~�[��window,X���W�𒲂ׂ�
				g_enemy[i].WindowPos.x = DISPLAY_WIDTH / 2 + EnemyWorldDistanceX;
				//�G�l�~�[��window,Y���W�𒲂ׂ�
				g_enemy[i].WindowPos.y = DISPLAY_HEIGHT / 2 + EnemyWorldDistanceY;
				//EnemyGravity(i);
				EnemyPursuit(i);
				g_enemy[i].bulletFrameCount++;
				if (g_enemy[i].bulletFrameCount == g_enemy[i].firingInterval) {//�G�l�~�[���Ɏ����Ă���͔��ˊ��o�ɂȂ��������
					EnemyBulettCreate(i);
					g_enemy[i].bulletFrameCount = 0;
				}
			}
		}
	}
}


void EnemyPursuit(int enemyNum) {
	Player* player = GetplayerData();
		switch (g_enemy[enemyNum].enemyKind) {
		case WALKINGENEMY_1:
		case WALKINGENEMY_HAS_KEY_2:
			if (g_enemy[enemyNum].bulletFrameCount < g_enemy[enemyNum].firingInterval - 5) {//�e���˃t���[�����-5�t���[�������������璆�ɓ���
				//�G�l�~�[��X���W���v���C���[��X���W��菬����������
				if (player->WindowPos.x < g_enemy[enemyNum].WindowPos.x) {
					//+�����ɃG�l�~�[�𓮂���
					g_enemy[enemyNum].MovementX -= g_enemy[enemyNum].Speed;
				}
				//�G�l�~�[��X���W���v���C���[��X���W���傫��������
				else if (player->WindowPos.x > g_enemy[enemyNum].WindowPos.x) {
					//-�����ɃG�l�~�[�𓮂���
					g_enemy[enemyNum].MovementX += g_enemy[enemyNum].Speed;
				}
			}
			if (g_enemy[enemyNum].bulletFrameCount >= g_enemy[enemyNum].firingInterval - 5) {//���˃t���[����-5�t���[���ȏ゠��Β��ɓ���
				g_enemy[enemyNum].MovementX = 0;
				g_enemy[enemyNum].MovementY = 0;
			}
			g_enemy[enemyNum].MovementY += GRAVITY;

			break;
		case FLYINGENEMY1:
		case FLYINGENEMY_HAS_KEY1:
		case FLYINGENEMY_HAS_KEY2:
			if (g_enemy[enemyNum].bulletFrameCount < g_enemy[enemyNum].firingInterval - 5) {//�e���˃t���[�����-5�t���[�������������璆�ɓ���
				//�G�l�~�[��X���W���v���C���[��X���W+200�̈ʒu���傫��������
				if (player->WindowPos.x + 200 < g_enemy[enemyNum].WindowPos.x) {
					//+�����ɃG�l�~�[�𓮂���
					g_enemy[enemyNum].MovementX -= g_enemy[enemyNum].Speed;
				}
				//�G�l�~�[��X���W���v���C���[��X���W-200�̈ʒu��菬����������
				else if (player->WindowPos.x - 200 > g_enemy[enemyNum].WindowPos.x) {
					//+�����ɃG�l�~�[�𓮂���
					g_enemy[enemyNum].MovementX += g_enemy[enemyNum].Speed;
				}
			}
			
			if (g_enemy[enemyNum].bulletFrameCount >= g_enemy[enemyNum].firingInterval - 5) {//���˃t���[����-5�t���[���ȏ゠��Β��ɓ���
				g_enemy[enemyNum].MovementX = 0;
				g_enemy[enemyNum].MovementY = 0;
			}

			break;
		}

	
}




void EnemyBulettCreate(int enemyNum) {
	Bullet* bullt= GetBullet();

		static int bulletRest = 0;//�e�̌���������}��ϐ�
		BulletCreate(bulletRest, enemyNum, BULLET01);
		bulletRest++;

		if (bulletRest == BULLETNUMBER ) {//�e�̑��U�����Ȃ��Ȃ����珉����
			bulletRest = 0;
		}

}



void EnemyArrangement(EnemyMapNum enemyMapNum[]) {//CSV����G�l�~�[�̍��W�Ǝ�ނ����炤

	STAGE_ID stage_ID = GetStage_ID();
	int MaxX = GetStageXYMAX(stage_ID, X);
	int MaxY = GetStageXYMAX(stage_ID, Y);
	int* enemyArrangement = (int*)malloc(sizeof(int)*MaxX*MaxY);

	switch (stage_ID) {
	case STAGE_1:
		CSVLoad("CSV/mainscene/stage1_gimmick.csv", enemyArrangement, MaxY, MaxX);//CSV�Ăяo��
		break;
	}

	int enemycount = 0;

	for (int i = 0; i < MaxY;i++) {
		for (int j = 0; j < MaxX; j++) {
			switch (enemyArrangement[j + i*MaxX]) {//��������G�̃f�[�^����ꍞ��
			case WALKINGENEMY_HAS_KEY_2:
				g_enemy[enemycount].enemyKind = WALKINGENEMY_HAS_KEY_2;
			case WALKINGENEMY_1:
				enemyMapNum[enemycount].NumX = j;
				enemyMapNum[enemycount].NumY = i;
				if (g_enemy[enemycount].enemyKind != WALKINGENEMY_HAS_KEY_2) {
					g_enemy[enemycount].enemyKind = WALKINGENEMY_1;
				}
				g_enemy[enemycount].Speed = 1;
				g_enemy[enemycount].firingInterval = 200;
				g_enemy[enemycount].size = 32;
				enemycount++;
				break;

			case FLYINGENEMY_HAS_KEY1:
				g_enemy[enemycount].enemyKind = FLYINGENEMY_HAS_KEY1;
			case FLYINGENEMY_HAS_KEY2:
				if (g_enemy[enemycount].enemyKind != FLYINGENEMY_HAS_KEY1){
					g_enemy[enemycount].enemyKind = FLYINGENEMY_HAS_KEY2;
				}
			case FLYINGENEMY1:
				enemyMapNum[enemycount].NumX = j;
				enemyMapNum[enemycount].NumY = i;
				if (g_enemy[enemycount].enemyKind != FLYINGENEMY_HAS_KEY1 || g_enemy[enemycount].enemyKind != FLYINGENEMY_HAS_KEY2) {
					g_enemy[enemycount].enemyKind = FLYINGENEMY1;
				}
				g_enemy[enemycount].Speed = 2;
				g_enemy[enemycount].firingInterval = 250;
				g_enemy[enemycount].size = 32;
				enemycount++;
				break;
			case FIXEDBATTERY1:
				enemyMapNum[enemycount].NumX = j;
				enemyMapNum[enemycount].NumY = i;
				g_enemy[enemycount].Speed = 0;
				g_enemy[enemycount].enemyKind = FIXEDBATTERY1;
				g_enemy[enemycount].firingInterval = 150;
				g_enemy[enemycount].size = 32 ;

			default:
				break;
			}
		}

	}

	free(enemyArrangement);

}


//}

void MoveEnemy() {
	for (int i = 0; i < g_EnemyMapDate.MaxDate; i++) {
		if (g_enemy[i].beActive == true && g_enemy[i].beDead == false) {//�f�X�A�A�N�e�B�u�`�F�b�N
			//�e�G�l�~�[�̍��W�ɓ����l�𑫂�
			g_enemy[i].WorldPos.x += g_enemy[i].MovementX;
			g_enemy[i].WorldPos.y += g_enemy[i].MovementY;
			g_enemy[i].WindowPos.x += g_enemy[i].MovementX;
			g_enemy[i].WindowPos.y += g_enemy[i].MovementY;

			//Movement�̏�����
			g_enemy[i].MovementX = 0;
			g_enemy[i].MovementY = 0;
		}
		
	 }
}