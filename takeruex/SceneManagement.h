#ifndef SCENEMANAGEMENT_H
#define SCENEMANAGEMENT_H

#include<d3dx9.h>

enum SCENE_ID {
	MAINSCENE,
	TITLESCENE,
	GAMEOVER,
	GAMECLEAR
};

//�V�[���𕪂��Ă����B�`��R���g���[�����Ă�ł܂��B
//�������[�������[�������[�X������Ă܂�
void SceneManage();

#endif