#include"MoveManagement.h"
#include"BulletControl.h"
#include"PlayerControl.h"
#include"EnemyControl.h"
#include"Boss1Control.h"

void MoveManage() {
	MovePlayer();
	MoveBullet();
	//MoveEnemy();
	MoveBoss1();
}