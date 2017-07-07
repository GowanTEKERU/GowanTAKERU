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
//void EnemyGravity(int enemyNum);

void EnemyInit() {
	EnemyMapNum enemyMapNum[ENEMYNUMBER];
	EnemyArrangement(enemyMapNum);
	for (int i = 0; i < ENEMYNUMBER; i++) {
		g_enemy[i].WorldPos.x = enemyMapNum[i].NumX*TIPSIZE;//���[���h���W
		g_enemy[i].WorldPos.y = enemyMapNum[i].NumY*TIPSIZE;
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
				//EnemyGravity(i);
				EnemyPursuit(i);
				g_enemy[i].bulletFreamCount++;
				if (g_enemy[i].bulletFreamCount == g_enemy[i].firingInterval) {//�G�l�~�[���Ɏ����Ă���͔��ˊ��o�ɂȂ��������
					EnemyBulettCreate(i);
					g_enemy[i].bulletFreamCount = 0;
				}
			}
		}
	}
}


void EnemyPursuit(int enemyNum) {
	Player* player = GetplayerData();
		switch (g_enemy[enemyNum].enemyKind) {
		case Walkingenemy:
		case Walkingenemy_Kye02:
			if (g_enemy[enemyNum].bulletFreamCount < g_enemy[enemyNum].firingInterval - 5) {//�e���˃t���[�����-5�t���[�������������璆�ɓ���
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
			if (g_enemy[enemyNum].bulletFreamCount >= g_enemy[enemyNum].firingInterval - 5) {//���˃t���[����-5�t���[���ȏ゠��Β��ɓ���
				g_enemy[enemyNum].MovementX = 0;
				g_enemy[enemyNum].MovementY = 0;
			}


			break;
		case Flyingenemy:
		case Flyingenemy_Kye01:
		case Flyingenemy_Kye02:
			if (g_enemy[enemyNum].bulletFreamCount < g_enemy[enemyNum].firingInterval - 5) {//�e���˃t���[�����-5�t���[�������������璆�ɓ���
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
			D3DXVECTOR2 tmpPos = g_enemy[enemyNum].WorldPos;
			if (g_enemy[enemyNum].MovementX < 0) {
				tmpPos.x += -ENEMYRESIZEWIDTH / 2;
				if (MapKindSpecifyForPos(&tmpPos) != NOTHING)
				{
					g_enemy[enemyNum].MovementX = 0;
				}
			}
			if (g_enemy[enemyNum].MovementX > 0) {
				tmpPos.x += ENEMYRESIZEWIDTH / 2;
				if (MapKindSpecifyForPos(&tmpPos) != NOTHING)
				{
					g_enemy[enemyNum].MovementX = 0;
				}
			}
			if (g_enemy[enemyNum].bulletFreamCount >= g_enemy[enemyNum].firingInterval - 5) {//���˃t���[����-5�t���[���ȏ゠��Β��ɓ���
				g_enemy[enemyNum].MovementX = 0;
				g_enemy[enemyNum].MovementY = 0;
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
	CSVLoad("CSV/mainscene/stage1_gimmick.csv", enemyArrangement, MAPCHIPNUM_HEIGHT, MAPCHIPNUM_WIDTH);//CSV�Ăяo��

	int count = 0;

	for (int i = 0; i < MAPCHIPNUM_HEIGHT;i++) {
		for (int j = 0; j < MAPCHIPNUM_WIDTH; j++) {
			switch (enemyArrangement[j + i*MAPCHIPNUM_WIDTH]) {//��������G�̃f�[�^����ꍞ��
			case Walkingenemy_Kye02:
				g_enemy[count].enemyKind = Walkingenemy_Kye02;
			case Walkingenemy:
				enemyMapNum[count].NumX = j;
				enemyMapNum[count].NumY = i;
				if (g_enemy[count].enemyKind != Walkingenemy_Kye02) {
					g_enemy[count].enemyKind = Walkingenemy;
				}
				g_enemy[count].Speed = 1;
				g_enemy[count].firingInterval = 200;
				count++;
				break;

			case Flyingenemy_Kye01:
				g_enemy[count].enemyKind = Flyingenemy_Kye01;
			case Flyingenemy_Kye02:
				if (g_enemy[count].enemyKind != Flyingenemy_Kye01){
					g_enemy[count].enemyKind = Flyingenemy_Kye02;
				}
			case Flyingenemy:
				enemyMapNum[count].NumX = j;
				enemyMapNum[count].NumY = i;
				if (g_enemy[count].enemyKind != Flyingenemy_Kye01|| g_enemy[count].enemyKind != Flyingenemy_Kye02) {
					g_enemy[count].enemyKind = Flyingenemy;
				}
				g_enemy[count].Speed = 2;
				g_enemy[count].firingInterval = 250;
				count++;
				break;

			default:
				break;
			}
		}

	}


}

//void EnemyGravity(int enemyNum) {//�n�����߂̃G�l�~�[�ɏd�͂�������
//		switch (g_enemy[enemyNum].enemyKind) {
//		case enemyKind01:
//			g_enemy[enemyNum].MovementY += GRAVITY;
//			break;
//		
//		default:
//			break;
//
//		}
//	
//}

void MoveEnemy() {
	for (int i = 0; i < ENEMYNUMBER; i++) {
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