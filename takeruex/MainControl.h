#ifndef MAINCONTROL_H
#define MAINCONTROL_H

#include<d3dx9.h>
#define GRAVITY 0.3f

void MainControl();

//�p�x�����߂܂�
double Calculate_rad(float x1, float y1, float x2, float y2);

//void PreventIntoPos(D3DXVECTOR2& oldPos, D3DXVECTOR2* currentPos, float width, float height);

#endif
