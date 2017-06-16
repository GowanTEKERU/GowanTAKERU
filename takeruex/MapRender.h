#ifndef MAPRENDER_H
#define MAPRENDER_H

#include<d3dx9.h>

//------------------------�d�v-------------------------------------
//�}�b�v�`�b�v�̂O�O�Ԗ�(����)�͂O�ł��肢���܂�
//------------------------------------------------------------------

//�}�b�v�`�b�v�S�̂̌��ł�
#define MAPCHIPNUM_HEIGHT 50
#define MAPCHIPNUM_WIDTH 70

//�`�悷��}�b�v�`�b�v�̌��ł�
#define RENDERMAPCHIPNUM_HEIGHT 25
#define RENDERMAPCHIPNUM_WIDTH 44

//�}�b�v�`�b�v�̃T�C�Y�ł�
#define TIPSIZE 32 

enum MapKind { NOTHING, FLOOR, START};

int* GetMapchipData();
void MapRender();

#endif
