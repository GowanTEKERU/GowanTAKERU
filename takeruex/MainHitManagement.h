#ifndef MAINHITMANAGEMENT_H
#define MAINHITMANAGEMENT_H

#include<d3dx9.h>

void HitManage();

//円と円のあたり判定
bool CircleHit(float cx1, float cy1, float r1, float cx2, float cy2, float r2);

//矩形と矩形のあたり判定
bool SquareHit(D3DXVECTOR2* pPos1, float width1, float height1, D3DXVECTOR2* pPos2, float width2, float height2);
#endif
