#ifndef MAPRENDER_H
#define MAPRENDER_H

#include<d3dx9.h>

//�`�悷��}�b�v�`�b�v�̌��ł�
#define RENDERSTAGE1MAPCHIPNUM_HEIGHT 25
#define RENDERSTAGE1MAPCHIPNUM_WIDTH 44

//�}�b�v�`�b�v�̃T�C�Y�ł�
#define TIPSIZE 32 

enum MapKind { NOTHING, FLOOR, NEEDLE };
enum GimmickKind{ START = 13 };

void MapRender();

#endif
