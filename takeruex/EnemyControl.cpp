#include"EnemyControl.h"
#include"MapRender.h"
#include"MapControl.h"
#include"CommonRender.h"
#include"CommonControl.h"
#include"MainControl.h"
#include"PlayerRender.h"
#include"PlayerControl.h"

//
//Enemy g_enemy;
//
//
//void EnemyInit() {
//	g_enemy.WindowPos.x = g_enemy.WorldPos.x = 222;
//	g_enemy.WindowPos.y = g_enemy.WorldPos.y = 202;
//	g_enemy.dmg = 20;
//	g_enemy.bedead=false;
//	g_enemy.beActive=false;
//	g_enemy.beLeft=false;
//
//}
////Player* GetplayerData()
////D3DXVECTOR2* GetBasePoint()
//void EnemyMove() {
//	Player* player = GetplayerData();
//
//
//	//�G�l�~�[��X���W���v���C���[��X���W��菬����������
//	if (player->WindowPos.x < g_enemy.WindowPos.x) {
//		//+�����ɃG�l�~�[�𓮂���
//		g_enemy.WindowPos.x += MOVE_SUPEED;
//	}
//	//�G�l�~�[��X���W���v���C���[��X���W���傫��������
//	else if (player->WindowPos.x > g_enemy.WindowPos.x) {
//		//-�����ɃG�l�~�[�𓮂���
//		g_enemy.WindowPos.x -= MOVE_SUPEED;
//	}
//}
//
//	Enemy* GetenemyData() {
//		return &g_enemy;
//	}
//