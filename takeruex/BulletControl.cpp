#include "BulletControl.h"
#include"PlayerControl.h"
#include"EnemyControl.h"
#include"MainControl.h"
#include"MapControl.h"
#include"CommonRender.h"

static Bullet g_bullet[BULLETNUMBER];
static Bullet g_firstBullet;

Bullet* GetBullet() {
	return g_bullet;
}

Bullet* GetFirstBulletAddress() {
	return &g_firstBullet;
}

void BulletInit() {

	g_firstBullet.next = NULL;
	g_firstBullet.previous = &g_firstBullet;

}

void BulletCreate(const D3DXVECTOR2& launchingSite, BULLETKIND bulletKind) {

	//�Ō���̒e�̎��̂̃A�h���X�܂ňړ�
	Bullet* pSearchBullet = &g_firstBullet;
	while (1) {
		if (pSearchBullet->next == NULL) {
			break;
		}
		pSearchBullet = pSearchBullet->next;
	}

	//bullet�𐶐�
	Bullet* newBullet = (Bullet*)malloc(sizeof(Bullet));

	//�A��
	pSearchBullet->next = newBullet;
	newBullet->previous = pSearchBullet;

	//������
	newBullet->next = NULL;
	newBullet->BulletKind = bulletKind;
	newBullet->WorldPos = launchingSite;
	D3DXVECTOR2 BasePoint0 = D3DXVECTOR2(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
	D3DXVECTOR2* pBasePoint = GetBasePoint();
	newBullet->WindowPos.x = newBullet->WorldPos.x - (pBasePoint->x - BasePoint0.x);
	newBullet->WindowPos.y = newBullet->WorldPos.y - (pBasePoint->y - BasePoint0.y);
	newBullet->wasReflect = false;
	newBullet->MovementX = newBullet->MovementY = 0;
	newBullet->ReflectCnt = 0;

	Player* pPlayer = GetplayerData();

	switch (bulletKind) {

	case BULLET01:
		newBullet->Speed = 6.0f;
		newBullet->Atk = 10;
		newBullet->Size = 22;
		newBullet->ReflectMax = 3;
		newBullet->SaveCoordinate = pPlayer->WindowPos;
		newBullet->Rad = Calculate_rad(
			newBullet->WindowPos.x,
			newBullet->WindowPos.y,
			newBullet->SaveCoordinate.x,
			newBullet->SaveCoordinate.y
		);
		break;
	case HOMING:
		newBullet->Speed = 6.0f;
		newBullet->Atk = 10;
		newBullet->Size = 22;
		newBullet->ReflectMax = 3;
		newBullet->SaveCoordinate = pPlayer->WindowPos;
		newBullet->Rad = Calculate_rad(
			newBullet->WindowPos.x,
			newBullet->WindowPos.y,
			newBullet->SaveCoordinate.x,
			newBullet->SaveCoordinate.y
		);
		break;

	case NONREFLECT:
		newBullet->Speed = 6.0f;
		newBullet->Atk = 10;
		newBullet->Size = 22;
		newBullet->ReflectMax = 1;
		newBullet->SaveCoordinate = pPlayer->WindowPos;
		newBullet->Rad = Calculate_rad(
			newBullet->WindowPos.x,
			newBullet->WindowPos.y,
			newBullet->SaveCoordinate.x,
			newBullet->SaveCoordinate.y
		);
	}
}

void BulletControl() {

	Player* player = GetplayerData();

	for (Bullet* pSearchBullet = g_firstBullet.next; pSearchBullet != NULL; pSearchBullet = pSearchBullet->next) {

		//��ʊO�ŏ�����
		if (pSearchBullet->WindowPos.x < -64 || DISPLAY_WIDTH + 64 < pSearchBullet->WindowPos.x) {
			DeleteBullet(&pSearchBullet);
			continue;
		}
		if (pSearchBullet->WindowPos.y < -64 || DISPLAY_HEIGHT + 64 < pSearchBullet->WindowPos.y) {
			DeleteBullet(&pSearchBullet);
			continue;
		}

		if (pSearchBullet->BulletKind == HOMING) {
			if (!pSearchBullet->wasReflect) {
				pSearchBullet->SaveCoordinate = player->WindowPos;
				pSearchBullet->Rad = Calculate_rad(
					pSearchBullet->WindowPos.x,
					pSearchBullet->WindowPos.y,
					pSearchBullet->SaveCoordinate.x,
					pSearchBullet->SaveCoordinate.y
				);
			}
		}

		SetBulletMovement(pSearchBullet);
	}
}

void MoveBullet() {
	D3DXVECTOR2 BasePoint0 = D3DXVECTOR2(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);
	D3DXVECTOR2* basePoint = GetBasePoint();
	for (Bullet* pSearchBullet = g_firstBullet.next; pSearchBullet != NULL; pSearchBullet = pSearchBullet->next) {
		
		pSearchBullet->WorldPos.x += pSearchBullet->MovementX;
		pSearchBullet->WorldPos.y += pSearchBullet->MovementY;
		pSearchBullet->WindowPos.x = pSearchBullet->WorldPos.x - (basePoint->x - BasePoint0.x);
		pSearchBullet->WindowPos.y = pSearchBullet->WorldPos.y - (basePoint->y - BasePoint0.y);
		pSearchBullet->MovementX = pSearchBullet->MovementY = 0;
		}
	}

void SetBulletMovement(Bullet* pBullet) {
	pBullet->MovementX = pBullet->Speed*cos(pBullet->Rad);
	pBullet->MovementY = -(pBullet->Speed*sin(pBullet->Rad));
}

void DeleteBullet(Bullet** DeletionBullet) {
	Bullet* pre = (*DeletionBullet)->previous;
	((*DeletionBullet)->previous)->next = (*DeletionBullet)->next;
	if ((*DeletionBullet)->next != NULL) {
		((*DeletionBullet)->next)->previous = (*DeletionBullet)->previous;

	}
	free(*DeletionBullet);
	*DeletionBullet = pre;
}

void DeleteALLBullet() {

	Bullet* pSearchBullet = &g_firstBullet;
	while (1) {

		//�Ō���̎�
		if (pSearchBullet->next == NULL) {

			//g_firstBullet��malloc����Ȃ�����J�����Ȃ��Ă���
			if (pSearchBullet != &g_firstBullet) {
				free(pSearchBullet);
				break;
			}
		}

		pSearchBullet = pSearchBullet->next;
		free(pSearchBullet->previous);
	}
}