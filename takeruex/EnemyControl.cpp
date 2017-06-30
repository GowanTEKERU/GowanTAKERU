#include"EnemyControl.h"
#include"MapRender.h"
#include"MapControl.h"
#include"CommonRender.h"
#include"CommonControl.h"
#include"MainControl.h"
#include"PlayerRender.h"
#include"PlayerControl.h"
#include "BulletControl.h"
#include "FileManagement.h"

Enemy g_enemy[ENEMYNUMBER];
struct EnemyMapNum {//CSV�̍��W�Ɣԍ������锠
	int NumX;
	int NumY;
	EnemyKind enemyKind;

};



Enemy* GetenemyData() {
		return g_enemy;
	}
//�v���g�^�C�v�Q
void EnemyBulettCreate(int enemyNum);
void EnemyMove(int enemyNuintq);
void EnemyArrangement(EnemyMapNum enemyMapNum[]);
void EnemyGravity(int enemyNum);

void EnemyInit() {
	EnemyMapNum enemyMapNum[ENEMYNUMBER];
	EnemyArrangement(enemyMapNum);
	for (int i = 0; i < ENEMYNUMBER; i++) {
		g_enemy[i].WorldPos.x = enemyMapNum[i].NumX*TIPSIZE;//���[���h���W
		g_enemy[i].WorldPos.y = enemyMapNum[i].NumY*TIPSIZE;
		g_enemy[i].enemyKind = enemyMapNum[i].enemyKind;
		g_enemy[i].WindowPos.x = 0;
		g_enemy[i].WindowPos.y = 0;
		g_enemy[i].Atk = 2;//�U����
		g_enemy[i].Hp = 1;//�̗�
		g_enemy[i].bulletFreamCount = 0;
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
				EnemyGravity(i);
				EnemyMove(i);
				g_enemy[i].bulletFreamCount++;
				if (g_enemy[i].bulletFreamCount == 300) {//300�t���[����1�����͂�
					EnemyBulettCreate(i);
					g_enemy[i].bulletFreamCount = 0;
				}
			}
		}
	}
}


void EnemyMove(int enemyNum) {
	Player* player = GetplayerData(); 
	switch (g_enemy[enemyNum].enemyKind) {
		case enemyKind01:
		//�G�l�~�[��X���W���v���C���[��X���W��菬����������
		if (player->WindowPos.x < g_enemy[enemyNum].WindowPos.x) {
			//+�����ɃG�l�~�[�𓮂���
			g_enemy[enemyNum].WorldPos.x -= MOVE_SUPEED;
		}
		//�G�l�~�[��X���W���v���C���[��X���W���傫��������
		else if (player->WindowPos.x > g_enemy[enemyNum].WindowPos.x) {
			//-�����ɃG�l�~�[�𓮂���
			g_enemy[enemyNum].WorldPos.x += MOVE_SUPEED;
		}
			
			break;
		case enemyKind02:
			//�G�l�~�[��X���W���v���C���[��X���W+200�̈ʒu���傫��������
			if (player->WindowPos.x + 200  < g_enemy[enemyNum].WindowPos.x) {
				//+�����ɃG�l�~�[�𓮂���
				g_enemy[enemyNum].WorldPos.x -= MOVE_SUPEED;
			}
			//�G�l�~�[��X���W���v���C���[��X���W-200�̈ʒu��菬����������
			else if (player->WindowPos.x - 200> g_enemy[enemyNum].WindowPos.x) {
				//+�����ɃG�l�~�[�𓮂���
				g_enemy[enemyNum].WorldPos.x += MOVE_SUPEED;
			}

			break;
	}

	}




void EnemyBulettCreate(int enemyNum) {
	Bullet* bullt= GetBullet();

		static int bulletRest = 0;//�e�̌���������}��ϐ�
		BulletCreate(bulletRest, enemyNum, bullet01);
		bulletRest++;

		if (bulletRest == BULLETNUMBER) {//�e�̑��U�����Ȃ��Ȃ����珉����
			bulletRest = 0;
		}

}



void EnemyArrangement(EnemyMapNum enemyMapNum[]) {//CSV����G�l�~�[�̍��W�Ǝ�ނ����炤

	int enemyArrangement[MAPCHIPNUM_HEIGHT*MAPCHIPNUM_WIDTH];
	CSVLoad("CSV/mainscene/enemyArrangement.csv", enemyArrangement, MAPCHIPNUM_HEIGHT, MAPCHIPNUM_WIDTH);//CSV�Ăяo��

	int count = 0;

	for (int i = 0; i < MAPCHIPNUM_HEIGHT;i++) {
		for (int j = 0; j < MAPCHIPNUM_WIDTH; j++) {
			switch (enemyArrangement[j+i*MAPCHIPNUM_WIDTH]) {//��������G�̃f�[�^����ꍞ��
			case enemyKind01:
				enemyMapNum[count].NumX = j;
				enemyMapNum[count].NumY = i;
				enemyMapNum[count].enemyKind = enemyKind01;
				count++;
				break;

			case enemyKind02:
				enemyMapNum[count].NumX = j;
				enemyMapNum[count].NumY = i;
				enemyMapNum[count].enemyKind = enemyKind02;
				count++;
				break;

			default:
				break;
			}
		}

	}


}

void EnemyGravity(int enemyNum) {//�n�����߂̃G�l�~�[�ɏd�͂�������
		switch (g_enemy[enemyNum].enemyKind) {
		case enemyKind01:
			g_enemy[enemyNum].WorldPos.y += GRAVITY;
			break;
		
		default:
			break;


		}
	
}

//float EnemyMoveSpeed(int enemyNum) {
//	switch (g_enemy[enemyNum].enemyKind) {
//	case enemyKind01:
//
//	}
//}