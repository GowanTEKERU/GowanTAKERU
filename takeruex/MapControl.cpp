#include"MapControl.h"
#include"MapRender.h"
#include"PlayerControl.h"

void MapComtrol() {

	int* map = GetMapchipData();
	Player* player = GetplayerData();

	if (9980 < player->WorldPos.x) {
		for (int i = 17; i < 24; i++) {
			for (int j = 288; j < 291; j++) {
				*(map + j + i*STAGE1MAPCHIPNUM_WIDTH) = FLOOR;
			}
		}
	}
}

void MapchipNumberSpecify(MapNumXY* pMapNumXY,D3DXVECTOR2* pWorldPos) {
	pMapNumXY->NumX = (pWorldPos->x / TIPSIZE);
	pMapNumXY->NumY = (pWorldPos->y / TIPSIZE);
}

void PosSpecifyForMapchipNumber(D3DXVECTOR2* pWorldPos, MapNumXY* pMapNumXY) {
	pWorldPos->x = pMapNumXY->NumX*TIPSIZE;
	pWorldPos->y = pMapNumXY->NumY*TIPSIZE;
}

int MapKindSpecify(MapNumXY* pMapNumXY) {
	int* map = GetMapchipData();

	//アクセス違反を防ぐ
	if (pMapNumXY->NumX < 0 || STAGE1MAPCHIPNUM_WIDTH < pMapNumXY->NumX) {
		pMapNumXY->NumX = 0;
		pMapNumXY->NumY = 0;
	}
	if (pMapNumXY->NumY < 0 || STAGE1MAPCHIPNUM_HEIGHT < pMapNumXY->NumY) {
		pMapNumXY->NumX = 0;
		pMapNumXY->NumY = 0;
	}

	int tmp = *(map + ((pMapNumXY->NumY)*STAGE1MAPCHIPNUM_WIDTH + pMapNumXY->NumX));
	return tmp;
}

int MapKindSpecify_Plus1(MapNumXY* pMapNumXY, Direction direction) {

	int* map = GetMapchipData();
	int tmp;

	//アクセス違反を防ぐ
	if (pMapNumXY->NumX < 0 || STAGE1MAPCHIPNUM_WIDTH < pMapNumXY->NumX) {
		pMapNumXY->NumX = 0;
		pMapNumXY->NumY = 0;
	}
	if (pMapNumXY->NumY < 0 || STAGE1MAPCHIPNUM_HEIGHT < pMapNumXY->NumY) {
		pMapNumXY->NumX = 0;
		pMapNumXY->NumY = 0;
	}

	switch (direction) {

	case UP:
		tmp = *(map+(pMapNumXY->NumX + STAGE1MAPCHIPNUM_WIDTH*(pMapNumXY->NumY - 1)));
		break;

	case RIGHTUP:
		tmp = *(map + ((pMapNumXY->NumX + 1) + STAGE1MAPCHIPNUM_WIDTH*(pMapNumXY->NumY - 1)));
		break;

	case RIGHT:
		tmp = *(map + ((pMapNumXY->NumX + 1) + STAGE1MAPCHIPNUM_WIDTH*pMapNumXY->NumY));
		break;

	case RIGHTDOWN:
		tmp = *(map + ((pMapNumXY->NumX + 1) + STAGE1MAPCHIPNUM_WIDTH*(pMapNumXY->NumY + 1)));
		break;

	case DOWN:
		tmp = *(map + (pMapNumXY->NumX + STAGE1MAPCHIPNUM_WIDTH*(pMapNumXY->NumY + 1)));
		break;

	case LEFTDOWN:
		tmp = *(map + ((pMapNumXY->NumX - 1) + STAGE1MAPCHIPNUM_WIDTH*(pMapNumXY->NumY + 1)));
		break;

	case LEFT:
		tmp = *(map + ((pMapNumXY->NumX - 1) + STAGE1MAPCHIPNUM_WIDTH*pMapNumXY->NumY));
		break;

	case LEFTUP:
		tmp = *(map + ((pMapNumXY->NumX - 1) + STAGE1MAPCHIPNUM_WIDTH*(pMapNumXY->NumY - 1)));
		break;
	}

	return tmp;
}

int MapKindSpecifyForPos(D3DXVECTOR2* pWorldPos) {
	MapNumXY MapNumXY;
	MapNumXY.NumX = (pWorldPos->x / TIPSIZE);
	MapNumXY.NumY = (pWorldPos->y / TIPSIZE);
	return MapKindSpecify(&MapNumXY);
}

int CalculateNumInRange(float l) {
	return (int)l / TIPSIZE ;
}