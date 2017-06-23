#include"EnemyControl.h"
#include"MapRender.h"
#include"MapControl.h"
#include"CommonRender.h"
#include"CommonControl.h"
#include"MainControl.h"
#include"PlayerRender.h"
#include"PlayerControl.h"
#include "BulletControl.h"

Enemy g_enemy[ENEMYNUMBER];

Enemy* GetenemyData() {
		return g_enemy;
	}

void EnemyBulettCreate();

void EnemyInit() {
	g_enemy[0].WorldPos.x=600;//���[���h���W
	g_enemy[0].WorldPos.y = 702;
	g_enemy[0].WindowPos.x = 0;
	g_enemy[0].WindowPos.y = 0;
	g_enemy[0].Atk=2;//�U����
	g_enemy[0].Hp=1;//�̗�
	g_enemy[0].beDead=false;//����ł��邩
	g_enemy[0].beActive=false;//��������
	g_enemy[0].beLeft = false;//���i�E�j�ǂ����������Ă邩

}

void EnemyMove(int enemyNum) {
	Player* player = GetplayerData();

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
}

void EnemyControl() {  

	D3DXVECTOR2* basepoint = GetBasePoint();
	for (int i = 0; i < ENEMYNUMBER ; i++) {
		//�E�B���h�E�̊O�i���E�j120�s�N�Z������`��J�n�̃t���O�𗧂Ă�
		if (g_enemy[i].WorldPos.x < basepoint->x + DISPLAY_WIDTH / 2 + 120 && g_enemy[i].WorldPos.x > basepoint->x - DISPLAY_WIDTH / 2 - 120) {
			g_enemy[i].beActive = true;
		}

		EnemyMove(i);

		//�G�l�~�[�ƃx�[�X�|�C���g�Ƃ�world,X���W�̋����𒲂ׂ�
		float EnemyWorldDistanceX = g_enemy[i].WorldPos.x - basepoint->x;
		//�G�l�~�[�ƃx�[�X�|�C���g�Ƃ�world,Y���W�̋����𒲂ׂ�
		float EnemyWorldDistanceY = g_enemy[i].WorldPos.y - basepoint->y;
		//�G�l�~�[��window,X���W�𒲂ׂ�
		g_enemy[i].WindowPos.x = DISPLAY_WIDTH / 2 + EnemyWorldDistanceX;
		//�G�l�~�[��window,Y���W�𒲂ׂ�
		g_enemy[i].WindowPos.y = DISPLAY_HEIGHT / 2 + EnemyWorldDistanceY;

		EnemyBulettCreate();

	}
}

void EnemyBulettCreate() {

	Bullet* bullt= GetBullet();

	static int FrameCount = 0;
	FrameCount++;

	if (FrameCount == 300) {//5�b�i300�t���[���j�Ɉ�����͂�

		static int bulletRest = 0;//�e�̌���������}��ϐ�
		BulletCreate(bulletRest,bullet01);
		bulletRest++;

		if (bulletRest == BULLETNUMBER) {//�e�̑��U�����Ȃ��Ȃ����珉����
			bulletRest = 0;
		}

		FrameCount = 0;
	}
}
