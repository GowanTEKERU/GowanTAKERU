#include"EnemyControl.h"
#include"MapRender.h"
#include"MapControl.h"
#include"CommonRender.h"
#include"CommonControl.h"
#include"MainControl.h"
#include"PlayerRender.h"
#include"PlayerControl.h"

Enemy g_enemy[ENEMYNUMBER];

Enemy* GetenemyData() {
		return g_enemy;
	}

void EnemyInit() {


}

void EnemyMove(int enemyNum) {
	Player* player = GetplayerData();

	//�G�l�~�[��X���W���v���C���[��X���W��菬����������
	if (player->WindowPos.x < g_enemy[enemyNum].WindowPos.x) {
		//+�����ɃG�l�~�[�𓮂���
		g_enemy[enemyNum].WindowPos.x += MOVE_SUPEED;
	}
	//�G�l�~�[��X���W���v���C���[��X���W���傫��������
	else if (player->WindowPos.x > g_enemy[enemyNum].WindowPos.x) {
		//-�����ɃG�l�~�[�𓮂���
		g_enemy[enemyNum].WindowPos.x -= MOVE_SUPEED;
	}
}
void EnemyControl() {  
		
	D3DXVECTOR2* basepoint = GetBasePoint();
	for (int i = 0; i < ENEMYNUMBER ; i++) {
		//�E�B���h�E�̊O�i���E�j120�s�N�Z������`��J�n�̃t���O�𗧂Ă�
		if (g_enemy[i].WorldPos.x < basepoint->x + DISPLAY_WIDTH / 2 + 120 || g_enemy[i].WorldPos.x > basepoint->x - DISPLAY_WIDTH / 2 + 120) {
			g_enemy[i].beActive = true;
		}

		//�G�l�~�[�ƃx�[�X�|�C���g�Ƃ�world,X���W�̋����𒲂ׂ�
		float EnemyWorldDistance = g_enemy[i].WorldPos.x - basepoint->x;
		//�G�l�~�[��window,X���W�𒲂ׂ�
		g_enemy[i].WindowPos.x = basepoint->x + DISPLAY_WIDTH / 2 + EnemyWorldDistance;



	}
}
