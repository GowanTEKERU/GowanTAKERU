#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include<d3dx9.h>

//pTexture�g�������l������
LPDIRECT3DTEXTURE9* GetTexture();

//texture�������[�X
void TextureFree();

//mainscene�̃e�L�X�`����ǂݍ���ł܂�
void MainSceneLoad();
void CSVLoad(char* mapdata, int* map, int height, int width);

#endif
