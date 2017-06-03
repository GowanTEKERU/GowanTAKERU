#include"Ammo.h"
#include "Control.h"

struct Ammo g_enemyAmmo;

void AmmoInit() {

	g_enemyAmmo.cx = 0;
	g_enemyAmmo.cy = 0;
	g_enemyAmmo.dmg = 20;
	g_enemyAmmo.rad = 0;
	g_enemyAmmo.radius = 15;
	g_enemyAmmo.reflect_cnt = 0;
	g_enemyAmmo.reflect_max = 3;
	g_enemyAmmo.wasReflect = false;

}

void Ammomove() {
	//�m�[�}��
	if (g_enemyAmmo.wasReflect == false) {

		g_enemyAmmo.cx += Ammo_MOVESPEED;
		g_enemyAmmo.cy += 0;
	}

	//�e���ꂽ�Ƃ�
	//if(�����蔻��){g_enemyAmmmo.wasReflect=true}
	if (g_enemyAmmo.wasReflect==true) {
		g_enemyAmmo.cx = Ammo_MOVESPEED*cos(g_enemyAmmo.rad);
		g_enemyAmmo.cy = Ammo_MOVESPEED*sin(g_enemyAmmo.rad);
	}
	
}

