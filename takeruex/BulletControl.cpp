#include "BulletControl.h"
#include"BulletRender.h"
#include"PlayerControl.h"
#include"EnemyControl.h"

static Bullet bullet[BULLETNUMBER];

void BulletInit() {
	for (int i = 0; i < BULLETNUMBER; i++) {
		bullet->beActive = false;
		bullet->BulletKind = bullet01;
		bullet->Atk = 10;
		bullet->rad = 0;
		bullet->radius = BULLETSIZE / 2;
		bullet->reflect_cnt = 0;
		bullet->reflect_max = 3;
		bullet->save_playercoordinateX = 0;
		bullet->save_playercoordinateY = 0;
		bullet->wasReflect = false;


	}
}

//void BulletMoveNomal() {
//
//	for (int i = 0; i < AmmoNumber; i++) {
//
//		if (bullet[i].berender == true) {
//
//			//�v���C���[�߂����āi��{����j
//			if (bullet[i].wasReflect == false) {
//
//				//���̎��̃v���C���[���W�L���B�v���C���[�̍��W�͐������珉���l���Ŕ���
//				if (bullet[ammovalue_flg].save_playercoordinateX == -1.0f) {
//					bullet[ammovalue_flg].save_playercoordinateX = g_player.cx;
//					bullet[ammovalue_flg].save_playercoordinateY = g_player.cy;
//				}
//
//				double rad = Calculate_rad(
//					bullet[ammovalue_flg].cx,
//					bullet[ammovalue_flg].cy,
//					bullet[ammovalue_flg].save_playercoordinateX,
//					bullet[ammovalue_flg].save_playercoordinateY
//				);
//				bullet[i].cx += Ammo_MOVESPEED*cos(rad);
//				bullet[i].cy += Ammo_MOVESPEED*sin(rad);
//			}
//
//		}
//	}
//}
//
//void BulletMoveReflectToPlayer() {
//
//	for (int i = 0; i < AmmoNumber; i++) {
//
//		if (bullet[i].beActive == true) {
//			//�e���ꂽ�Ƃ�
//			if (bullet[i].wasReflect == true) {
//				bullet[i].cx += -Ammo_MOVESPEED*cos(g_enemyAmmo[i].rad);
//				bullet[i].cy += Ammo_MOVESPEED*sin(g_enemyAmmo[i].rad);
//			}
//		}
//	}
//}

void BulletControl() {

}