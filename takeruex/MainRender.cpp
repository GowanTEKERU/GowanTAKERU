#include"MainRender.h"
#include"DirectXGraphics.h"
#include"CommonRender.h"
#include"BackGroundRender.h"
#include"MapRender.h"
#include"PlayerRender.h"
#include"BulletRender.h"
#include"EnemyRender.h"
#include"UIRender.h"
#include"BlackOutRender.h"
#include"Boss1Render.h"
#include"Boss2Render.h"
#include"Boss3Render.h"
#include"Boss4Render.h"

void MainRender() {

	IDirect3DDevice9* pD3Device = GetGraphicsDevice();

	//-----------------------------------------------------
	//�V�[���`��
	//-----------------------------------------------------
	pD3Device->Clear(0, NULL,
		D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0xff, 0xff, 0xff),
		1.0, 0);

	pD3Device->BeginScene();

	BackgroundRender();
	MapRender();
	EnemyRender();
	Boss1Render();
	//Boss2Render();
	Boss3Render();
	Boss4Render();
	BulletRender();
	PlayerRender();
	UIRender();

	BlackOutData* blackOutData = GetBlackOutData();
	if (blackOutData->BlackOutflg) {
		BlackOutRender();
	}

	pD3Device->EndScene();
	pD3Device->Present(NULL, NULL, NULL, NULL);
}

void TurnVertex_tu(CUSTOMVERTEX* vertex) {

	CUSTOMVERTEX tmpVertex;

	tmpVertex.tu = vertex[0].tu;
	vertex[0].tu = vertex[1].tu;
	vertex[1].tu = tmpVertex.tu;

	tmpVertex.tu = vertex[3].tu;
	vertex[3].tu = vertex[2].tu;
	vertex[2].tu = tmpVertex.tu;

}

void TrimingVertex(CUSTOMVERTEX* vertex, float leftTopTu, float leftTopTv, float width, float height,float pngWidth,float pngHeight) {
	vertex[0].tu = leftTopTu / pngWidth;
	vertex[0].tv = leftTopTv / pngHeight;

	vertex[1].tu = (leftTopTu + width) / pngWidth;
	vertex[1].tv = leftTopTv / pngHeight;

	vertex[2].tu = (leftTopTu + width) / pngWidth;
	vertex[2].tv = (leftTopTv + height) / pngHeight;

	vertex[3].tu = leftTopTu / pngWidth;
	vertex[3].tv = (leftTopTv + height) / pngHeight;

}