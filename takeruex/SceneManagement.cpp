#include "SceneManagement.h"
#include"BlackOutRender.h"
#include"MainScene.h"
#include"TitleScene.h"
#include"GameOver.h"

static SCENE_ID g_currentScene_ID = TITLESCENE;
static SCENE_ID g_nextScene_ID = TITLESCENE;

SCENE_ID GetCurrentScene_ID() {
	return g_currentScene_ID;
}

void SceneManage() {

	//Run�n�̊֐��̓}�C�t���[���Ă΂��̂�blackout���̏㏑���̖h�~
	SCENE_ID tmpScene_ID;

	BlackOutData* blackOutData = GetBlackOutData();

	bool releaseState = false;
	if (blackOutData->BlackOutNextState == BLACKOUT) {
		releaseState = true;
		//�������ǃ��������[�N�̉���B����v����
		blackOutData->BlackOutNextState = NON;
	}

	switch (g_currentScene_ID) {
	case TITLESCENE:
		tmpScene_ID = RunTitleScene(releaseState);
		if (tmpScene_ID != TITLESCENE) {
			g_nextScene_ID = tmpScene_ID;
			blackOutData->BlackOutflg = true;
		}
		break;

	case MAINSCENE:
		tmpScene_ID = RunMainScene(releaseState);
		if (tmpScene_ID != MAINSCENE) {
			g_nextScene_ID = tmpScene_ID;
			blackOutData->BlackOutflg = true;
		}
		break;

	case GAMEOVERSCENE:
		tmpScene_ID = RunGameOverScene(releaseState);
		if (tmpScene_ID != GAMEOVERSCENE) {
			g_nextScene_ID = tmpScene_ID;
			blackOutData->BlackOutflg = true;
		}
		break;
	}
	
	if (releaseState) {
		g_currentScene_ID = g_nextScene_ID;
	}

}
