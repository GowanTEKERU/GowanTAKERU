#include"MainControl.h"
#include"PlayerControl.h"
#include"EnemyControl.h"
#include"BulletControl.h"
#include"MapControl.h"
#include"MainHitManagement.h"
#include"MoveManagement.h"
#include"StageGimmick.h"
#include"BlackOutRender.h"
#include"Boss1Control.h"
#include"Boss2Control.h"
#include"Boss3Control.h"
#include"Boss4Control.h"
#include<time.h>
#include"CommonControl.h"


void MainControl(/*RENDER_STATE stageStartState*/) {

	UpdatePad();

	PlayerControl();
	if (GetGoNextStageWait() == WAITING) {
		EnemyControl();
	}
	Boss1Control();
	Boss2Control();
	Boss3Control();
	Boss4Control();
	BulletControl();
	if (GetGoNextStageWait() == WAITING) {
		HitManage();
	}
	StageGimmickManage();
	MoveManage();
}

RENDER_STATE GetGoNextStageWait() {
	Boss1Data* pBoss1 = GetBoss1Data();
	Boss2Data* pBoss2 = GetBoss2Data();
	Boss3Data* pBoss3 = GetBoss3Data();
	Boss4Data* pBoss4 = GetBoss4Data();

	static RENDER_STATE goNextStageWait = WAITING;
	if ((pBoss1->isDead && !pBoss1->goNextStage)|| 
		(pBoss2->isDead && !pBoss2->goNextStage)||
		(pBoss3->isDead && !pBoss3->goNextStage) ||
		(pBoss4->isDead && !pBoss4->goNextStage)) {

		if (goNextStageWait == WAITING) {
			goNextStageWait = STARTUP;
		}
		else {
			goNextStageWait = RUNNING;
		}
	}
	else {
		goNextStageWait = WAITING;
	}

	return goNextStageWait;
}

double Calculate_rad(float x1, float y1, float x2, float y2) {

	double rad= 0 ;

	double lengthX = x2 - x1;
	double lengthY = y2 - y1;

	if (0 < lengthX) {
		if (lengthY < 0) {

			rad = atan(lengthY / lengthX);

		}
		else {

			rad = atan(lengthY / lengthX) + (2 * D3DX_PI);

		}
	}
	else if (lengthX < 0) {

		rad = atan(lengthY / lengthX) + D3DX_PI;

	}
	else if (lengthX == 0) {
		if (0 < lengthY) {

			rad = 3 / 2 * D3DX_PI;

		}
		else {

			rad = D3DX_PI / 2;

		}
	}

	rad = (2 * D3DX_PI) - rad;

	return rad;
}

float Calculate_distance(float x1, float y1, float x2, float y2) {

	return (float)sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

//-----------------------------------
//ランダム生成関数
//-----------------------------------
//min<=random<=max
int Random(int min, int max) {
	static bool seedrandom = false;

	if (seedrandom == false) {
		srand((unsigned int)time(NULL));
		seedrandom = true;
	}

	return min + rand() % (max + 1);
}

//struct VertexInfo {
//	D3DXVECTOR2 Pos;
//	MapNumXY mapNum;
//};
//
//void DataUpdate(VertexInfo* vertexInfo, D3DXVECTOR2& currentPos, float width, float height);
//
//void PreventIntoPos(D3DXVECTOR2& oldPos, D3DXVECTOR2* currentPos,float width,float height) {
//
//	VertexInfo vertex[4];
//
//	DataUpdate(vertex, *currentPos, width, height);
//
//	D3DXVECTOR2 frDiff;
//	frDiff.x = currentPos->x - oldPos.x;
//	frDiff.y = currentPos->x - oldPos.x;
//
//	//?個にまたがっている(境界線の個数）
//	int widthSizeNum = width / TIPSIZE;
//	int heightSizeNum = height / TIPSIZE;
//
//	if (frDiff.x < 0) {
//		if (frDiff.y < 0) {
//			//左上に向かって動いている
//
//			D3DXVECTOR2 tmpPos = vertex[0].Pos;
//
//			//側面だけを見ます
//			//上の面が当たっているとき
//			for (int i = 0; i < widthSizeNum + 1; i++) {
//				tmpPos.x += TIPSIZE*i;
//				if (MapKindSpecifyForPos(&tmpPos) != NOTHING) {
//
//					float diffY = (vertex[0].mapNum.NumY*TIPSIZE) - vertex[0].Pos.y;
//
//					float diffX = frDiff.x;
//					diffX *= diffY / frDiff.y;
//
//					currentPos->y += diffY;
//					currentPos->x += diffX;
//					break;
//				}
//			}
//			DataUpdate(vertex, *currentPos, width, height);
//			tmpPos.x = vertex[0].Pos.x;
//			//左の面が当たっているとき
//			for (int i = 0; i < heightSizeNum; i++) {
//				tmpPos.y += TIPSIZE*i;
//				if (MapKindSpecifyForPos(&tmpPos) != NOTHING) {
//
//					float diffX = (vertex[0].mapNum.NumX*TIPSIZE) - vertex[0].Pos.x;
//
//					float diffY = frDiff.y;
//					diffY *= diffX / frDiff.x;
//
//					currentPos->y += diffY;
//					currentPos->x += diffX;
//					break;
//				}
//			}
//			DataUpdate(vertex, *currentPos, width, height);
//		}
//		else if (0 < frDiff.y) {
//			//左下に向かって動いている
//
//			D3DXVECTOR2 tmpPos = vertex[3].Pos;
//
//			//側面だけを見ます
//			//左の面が当たっているとき
//			for (int i = 0; i < heightSizeNum; i++) {
//				tmpPos.y -= TIPSIZE*i;
//				if (MapKindSpecifyForPos(&tmpPos) != NOTHING) {
//
//					float diffX = (vertex[3].mapNum.NumX*TIPSIZE) - vertex[3].Pos.x;
//
//					float diffY = frDiff.y;
//					diffY *= diffX / frDiff.x;
//
//					currentPos->y += diffY;
//					currentPos->x += diffX;
//					break;
//				}
//			}
//			DataUpdate(vertex, *currentPos, width, height);
//			tmpPos.x = vertex[3].Pos.x;
//			//下の面が当たっているとき
//			for (int i = 0; i < widthSizeNum + 1; i++) {
//				tmpPos.x += TIPSIZE*i;
//				if (MapKindSpecifyForPos(&tmpPos) != NOTHING) {
//
//					float diffY = vertex[3].Pos.y - (vertex[3].mapNum.NumY*TIPSIZE);
//
//					float diffX = frDiff.x;
//					diffX *= diffY / frDiff.y;
//
//					currentPos->y += diffY;
//					currentPos->x += diffX;
//					break;
//				}
//			}
//
//			DataUpdate(vertex, *currentPos, width, height);
//		}
//		else if (frDiff.y == 0) {
//			//左に向かって動いている	
//			D3DXVECTOR2 tmpPos = vertex[0].Pos;
//
//			//左の面が当たっているとき
//			for (int i = 0; i < heightSizeNum; i++) {
//				tmpPos.y += TIPSIZE*i;
//				if (MapKindSpecifyForPos(&tmpPos) != NOTHING) {
//
//					float diffX = (vertex[0].mapNum.NumX*TIPSIZE) - vertex[0].Pos.x;
//
//					float diffY = frDiff.y;
//					diffY *= diffX / frDiff.x;
//
//					currentPos->y += diffY;
//					currentPos->x += diffX;
//					break;
//				}
//			}
//		}
//	}
//	else if (0 < frDiff.x) {
//		if (frDiff.y < 0) {
//
//		}
//		else if (0 < frDiff.y) {
//
//		}
//		else if (frDiff.y == 0) {
//
//		}
//	}
//	else if (frDiff.x == 0) {
//		if (frDiff.y < 0) {
//
//		}
//		else if (0 < frDiff.y) {
//
//		}
//		else if (frDiff.y == 0) {
//
//		}
//	}
//}
//
//void DataUpdate(VertexInfo* vertexInfo, D3DXVECTOR2& currentPos, float width, float height){
//
//	vertexInfo[1].Pos.x = vertexInfo[2].Pos.x = currentPos.x + width / 2;
//	vertexInfo[0].Pos.x = vertexInfo[3].Pos.x = currentPos.x - width / 2;
//	vertexInfo[0].Pos.y = vertexInfo[1].Pos.y = currentPos.y - height / 2;
//	vertexInfo[3].Pos.y = vertexInfo[2].Pos.y = currentPos.y + height / 2;
//
//
//	MapchipNumberSpecify(&vertexInfo[0].mapNum, &vertexInfo[0].Pos);
//	MapchipNumberSpecify(&vertexInfo[1].mapNum, &vertexInfo[1].Pos);
//	MapchipNumberSpecify(&vertexInfo[2].mapNum, &vertexInfo[2].Pos);
//	MapchipNumberSpecify(&vertexInfo[3].mapNum, &vertexInfo[3].Pos);
//}