#ifndef MAINCENE_H
#define MAINCENE_H

#include "SceneManagement.h"
#include"StageSelect.h"

void PlayBGM(STAGE_ID stage_ID, bool boss);
void StopBGM(STAGE_ID stage_ID, bool boss);

//�߂�l ���̃V�[����Ԃ��܂�
SCENE_ID RunMainScene(bool willbetrancefar);

#endif