#ifndef DIRECTXGRAPHICS_H
#define DIRECTXGRAPHICS_H

#include<d3dx9.h>

//�O���t�B�b�N�f�o�C�X�g�������l����
IDirect3DDevice9* GetGraphicsDevice();

//�_�C���N�g�G�b�N�X�O���t�B�b�N�������֐�
void DXGraphicsInit(HWND hWnd, bool Window_mode);

//�`����@�ݒ�
void TextureInit();

//�f�o�C�X�A���Ԃ������[�X
void FreeDxGraphics();


#endif

